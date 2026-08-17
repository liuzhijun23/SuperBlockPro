#include "SM16208.h"
#include "timer.h"
#include "apm32e030_gpio.h"

uint8_t image_matrix[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
u8 key_arr[8];
u8 key_history[8][CONFIRM_NUM];
u8 key_filter[8];
u8 key_filter_pre[8];

//u8 image_arr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//u8 image_arr[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
u8 image_arr[][8] = {
    { 0x00, 0x0E, 0x06, 0x02, 0x60, 0x70, 0x20, 0x00 },
    { 0x00, 0x00, 0x70, 0x30, 0x10, 0x00, 0x00, 0x00 },
};


void SM16208_Init(void)
{
    GPIO_Config_T g;

    g.pin = SDI_PIN;
    g.mode = GPIO_MODE_OUT;
    g.outtype = GPIO_OUT_TYPE_PP;
    g.speed = GPIO_SPEED_50MHz;
    g.pupd = GPIO_PUPD_NO;
    GPIO_Config(SDI_GPIO, &g);

    g.pin = SCK_PIN ;
    GPIO_Config(SCK_GPIO, &g);

    g.pin = LE_PIN ;
    GPIO_Config(LE_GPIO, &g);

    g.pin = OE_PIN ;
    GPIO_Config(OE_GPIO, &g);

    g.pin = A2_PIN ;
    GPIO_Config(A2_GPIO, &g);

    g.pin = A1_PIN ;
    GPIO_Config(A1_GPIO, &g);

    g.pin = A0_PIN ;
    GPIO_Config( A0_GPIO, &g);

    g.pin = POWER_PIN ;
    GPIO_Config(POWER_GPIO, &g);

    SET_POWER_PIN(1);

    g.pin = KEY0_PIN;
	g.speed = GPIO_SPEED_50MHz;
	g.mode = GPIO_MODE_IN;
    g.outtype = GPIO_OUT_TYPE_OD;
    g.pupd = GPIO_PUPD_NO;
	GPIO_Config(KEY0_GPIO, &g); 

    g.pin = KEY1_PIN;  
    GPIO_Config(KEY1_GPIO, &g);   

    g.pin = KEY2_PIN;  
    GPIO_Config(KEY2_GPIO, &g);  

    g.pin = KEY3_PIN;  
    GPIO_Config(KEY3_GPIO, &g); 

    g.pin = KEY4_PIN;  
    GPIO_Config(KEY4_GPIO, &g); 

    g.pin = KEY5_PIN;  
    GPIO_Config(KEY5_GPIO, &g); 

    g.pin = KEY6_PIN;  
    GPIO_Config(KEY6_GPIO, &g); 

    g.pin = KEY7_PIN;  
    GPIO_Config(KEY7_GPIO, &g); 
}

u8 ReadKeyData(void)
{
    u8 data = 0;
    if(GPIO_ReadInputBit(KEY0_GPIO,KEY0_PIN))
        data |= 0x01;
    if(GPIO_ReadInputBit(KEY1_GPIO,KEY1_PIN))
        data |= 0x02;
    if(GPIO_ReadInputBit(KEY2_GPIO,KEY2_PIN))
        data |= 0x04;   
    if(GPIO_ReadInputBit(KEY3_GPIO,KEY3_PIN))
        data |= 0x08; 
    if(GPIO_ReadInputBit(KEY4_GPIO,KEY4_PIN))
        data |= 0x10;
    if(GPIO_ReadInputBit(KEY5_GPIO,KEY5_PIN))
        data |= 0x20;
    if(GPIO_ReadInputBit(KEY6_GPIO,KEY6_PIN))
        data |= 0x40;
    if(GPIO_ReadInputBit(KEY7_GPIO,KEY7_PIN))
        data |= 0x80;
    return data;
}

void display_matrix(u8* matrix)
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
                GPIO_WriteBitValue(SDI_GPIO,SDI_PIN,Bit_SET);
            }
            else
            {
                GPIO_WriteBitValue(SDI_GPIO,SDI_PIN,BIT_RESET);
            }

            GPIO_WriteBitValue(SCK_GPIO,SCK_PIN,Bit_SET);
            GPIO_WriteBitValue(SCK_GPIO,SCK_PIN,BIT_RESET);
            send_data <<= 1;
        }
        
        // 3. 产生锁存信号，更新列驱动
        GPIO_WriteBitValue(LE_GPIO,LE_PIN,BIT_SET);
        GPIO_WriteBitValue(LE_GPIO,LE_PIN,BIT_RESET);
        
        // 4. 消影：关闭显示
        GPIO_WriteBitValue(OE_GPIO,OE_PIN,BIT_SET);
        
        // 5. 切换行选：通过 3 根线控制 SM5166 选通当前行
        if(row&0x04)
            GPIO_WriteBitValue(A2_GPIO,A2_PIN,BIT_SET);
        else
            GPIO_WriteBitValue(A2_GPIO,A2_PIN,BIT_RESET);

        if(row&0x02)
            GPIO_WriteBitValue(A1_GPIO,A1_PIN,BIT_SET);
        else
            GPIO_WriteBitValue(A1_GPIO,A1_PIN,BIT_RESET);

        if(row&0x01)
            GPIO_WriteBitValue(A0_GPIO,A0_PIN,BIT_SET);
        else
            GPIO_WriteBitValue(A0_GPIO,A0_PIN,BIT_RESET);
        
        // 6. 开启显示并延时
        GPIO_WriteBitValue(OE_GPIO,OE_PIN,BIT_RESET);

        delay_ms(1); // 每一行点亮 1 毫秒
       
        key_arr[row] = ReadKeyData();
        
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
        key_filter_pre[r] = key_filter[r]; 
        key_filter[r] = (key_filter[r] | all_ones) & (~all_zeros);

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
                
                // // 检测按下
                // if (press_events & mask) {
                //     on_key_pressed(r, c); // 触发按下回调
                // }
                
                // // 检测抬起
                // if (release_events & mask) {
                //     on_key_released(r, c); // 触发抬起回调
                // }
            }
        }
    }
}