#include "SM16208.h"
#include "timer.h"

void SM16208_Init(void)
{
    GPIO_Init(SDI_GPIO, SDI_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SCK_GPIO, SCK_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(LE_GPIO, LE_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(OE_GPIO, OE_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(A2_GPIO, A2_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(A1_GPIO, A1_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(A0_GPIO, A0_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(POWER_GPIO, POWER_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);

    GPIO_WriteLow(POWER_GPIO,POWER_PIN);
}

uint8_t image_matrix[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
u8 key_arr[8];
u8 key_history[8][CONFIRM_NUM];
u8 key_filter[8];
u8 key_filter_pre[8];

void display_matrix(u16* matrix)
{
    for (uint8_t row = 0; row < 8; row++) 
    {
        
        // 1. 获取当前行的 8位 列数据
        u16 col_data = matrix[row]<<6;
        
        // 2. 串行发送 16 位数据给 SM16208（OUT0~OUT7 对应低字节）
        uint16_t send_data = (uint16_t)col_data; 
        for (int i = 0; i < 16; i++) 
        {
            if(send_data & 0x8000)
            {
                GPIO_WriteHigh(SDI_GPIO,SDI_PIN);
            }
            else
            {
                GPIO_WriteLow(SDI_GPIO,SDI_PIN);
            }
            GPIO_WriteHigh(SCK_GPIO,SCK_PIN);
            GPIO_WriteLow(SCK_GPIO,SCK_PIN);
            send_data <<= 1;
        }
        
        // 3. 产生锁存信号，更新列驱动
        GPIO_WriteHigh(LE_GPIO,LE_PIN);
        GPIO_WriteLow(LE_GPIO,LE_PIN);
        
        // 4. 消影：关闭显示
        GPIO_WriteHigh(OE_GPIO,OE_PIN);
        
        // 5. 切换行选：通过 3 根线控制 SM5166 选通当前行
        if(row&0x04)
            GPIO_WriteHigh(A2_GPIO,A2_PIN);
        else
            GPIO_WriteLow(A2_GPIO,A2_PIN);

        if(row&0x02)
            GPIO_WriteHigh(A1_GPIO,A1_PIN);
        else
            GPIO_WriteLow(A1_GPIO,A1_PIN);

        if(row&0x01)
            GPIO_WriteHigh(A0_GPIO,A0_PIN);
        else
            GPIO_WriteLow(A0_GPIO,A0_PIN);
        
        // 6. 开启显示并延时
        GPIO_WriteLow(OE_GPIO,OE_PIN);
        delay_ms(1); // 每一行点亮 1 毫秒

        key_arr[row] = (u8)(KEY_PORT->IDR & 0x00FF);
    }
}

void process_key_events() 
{
    for (uint8_t r = 0; r < 8; r++) 
    {
        // ------------------------------------------------------------
        // 步骤 1：滚动更新历史记录缓存（将最新的实时扫描数据推入）
        // ------------------------------------------------------------
        key_history[r][2] = key_history[r][1];
        key_history[r][1] = key_history[r][0];
        key_history[r][0] = key_arr[r]; // 塞入最新实时数据

        // ------------------------------------------------------------
        // 步骤 2：双边消抖判定（确保按下和抬起都必须连续3次一致）
        // ------------------------------------------------------------
        uint8_t all_ones  = key_history[r][0] & key_history[r][1] & key_history[r][2];
        uint8_t all_zeros = (~key_history[r][0]) & (~key_history[r][1]) & (~key_history[r][2]);
        
        // 备份当前状态为“上一次状态”，然后更新“当前状态”
        key_previous[r] = key_filter[r]; 
        key_debounced[r] = (key_filter[r] | all_ones) & (~all_zeros);

        // ------------------------------------------------------------
        // 步骤 3：核心——边沿检测（找出哪些键的电平发生了跳变）
        // ------------------------------------------------------------
        // 异或运算：只要当前状态和上次状态不一样，对应位就变成 1
        uint8_t changed_bits = key_filter[r] ^ key_filter_pre[r];

        if (changed_bits != 0) 
        {
            // 找出哪些位是从 0 变 1 (按下)
            uint8_t press_events = changed_bits & key_filter[r];
            
            // 找出哪些位是从 1 变 0 (抬起)
            uint8_t release_events = changed_bits & (~key_filter[r]);

            // ------------------------------------------------------------
            // 步骤 4：分发事件，遍历该行的 8 个通道
            // ------------------------------------------------------------
            for (uint8_t c = 0; c < 8; c++) 
            {
                uint8_t mask = (1 << c);
                
                // 检测按下
                if (press_events & mask) {
                    on_key_pressed(r, c); // 触发按下回调
                }
                
                // 检测抬起
                if (release_events & mask) {
                    on_key_released(r, c); // 触发抬起回调
                }
            }
        }
    }
}