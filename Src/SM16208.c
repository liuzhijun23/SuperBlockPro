#include "SM16208.h"
#include "timer.h"

uint8_t image_matrix[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
u8 key_arr[8];
u8 key_history[8][CONFIRM_NUM];
u8 key_filter[8];
u8 key_filter_pre[8];

//u8 image_arr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//u8 image_arr[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

u8 image_arr[][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x00, 0x00, 0x3C, 0x20, 0x3C, 0x04, 0x3C, 0x00 },
    { 0x00, 0x00, 0x3C, 0x24, 0x24, 0x24, 0x3C, 0x00 },
};
u8 level_arr[][8] = {
    { 0x00, 0x0E, 0x06, 0x02, 0x60, 0x70, 0x20, 0x00 },
    { 0x00, 0x00, 0x70, 0x30, 0x10, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x40, 0x50, 0x58, 0x7C },
    { 0x02, 0x07, 0x06, 0x00, 0x1C, 0x18, 0x38, 0x38,},
    { 0x00, 0x00, 0x00, 0x60, 0x70, 0x78, 0x60, 0x00 },
};


void SM16208_Init(void)
{
    GPIO_InitTypeDef g;

    g.Pin = SDI_PIN ;
	g.Speed = GPIO_SPEED_FREQ_HIGH;
	g.Mode = GPIO_MODE_OUTPUT_PP;
    g.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SDI_GPIO, &g);

    g.Pin = SCK_PIN ;
    HAL_GPIO_Init(SCK_GPIO, &g);

    g.Pin = LE_PIN ;
    HAL_GPIO_Init(LE_GPIO, &g);

    g.Pin = OE_PIN ;
    HAL_GPIO_Init(OE_GPIO, &g);

    g.Pin = A2_PIN ;
    HAL_GPIO_Init(A2_GPIO, &g);

    g.Pin = A1_PIN ;
    HAL_GPIO_Init(A1_GPIO, &g);

    g.Pin = A0_PIN ;
    HAL_GPIO_Init( A0_GPIO, &g);

    g.Pin = POWER_PIN ;
    HAL_GPIO_Init(POWER_GPIO, &g);

    SET_POWER_PIN(0);

    g.Pin = KEY0_PIN;
	g.Speed = GPIO_SPEED_FREQ_HIGH;
	g.Mode = GPIO_MODE_INPUT;
    g.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY0_GPIO, &g); 

    g.Pin = KEY1_PIN;  
    HAL_GPIO_Init(KEY1_GPIO, &g);   

    g.Pin = KEY2_PIN;  
    HAL_GPIO_Init(KEY2_GPIO, &g);  

    g.Pin = KEY3_PIN;  
    HAL_GPIO_Init(KEY3_GPIO, &g); 

    g.Pin = KEY4_PIN;  
    HAL_GPIO_Init(KEY4_GPIO, &g); 

    g.Pin = KEY5_PIN;  
    HAL_GPIO_Init(KEY5_GPIO, &g); 

    g.Pin = KEY6_PIN;  
    HAL_GPIO_Init(KEY6_GPIO, &g); 

    g.Pin = KEY7_PIN;  
    HAL_GPIO_Init(KEY7_GPIO, &g); 
}

u8 ReadKeyData(void)
{
    u8 data = 0;
    if(HAL_GPIO_ReadPin(KEY0_GPIO,KEY0_PIN))
        data |= 0x01;
    if(HAL_GPIO_ReadPin(KEY1_GPIO,KEY1_PIN) == 1)
        data |= 0x02;
    if(HAL_GPIO_ReadPin(KEY2_GPIO,KEY2_PIN) == 1)
        data |= 0x04;   
    if(HAL_GPIO_ReadPin(KEY3_GPIO,KEY3_PIN) == 1)
        data |= 0x08; 
    if(HAL_GPIO_ReadPin(KEY4_GPIO,KEY4_PIN) == 1)
        data |= 0x10;
    if(HAL_GPIO_ReadPin(KEY5_GPIO,KEY5_PIN) == 1)
        data |= 0x20;
    if(HAL_GPIO_ReadPin(KEY6_GPIO,KEY6_PIN) == 1)
        data |= 0x40;
    if(HAL_GPIO_ReadPin(KEY7_GPIO,KEY7_PIN) == 1)
        data |= 0x80;
    return data;
}

void display_matrix(u8* matrix)
{
    uint8_t row = 0;
    for (row = 0; row < 8; row++) 
    {
        
        // 1. 获取当前行的 8位 列数据
        u16 col_data = (matrix[row]<<6);

        // u16 rgbVal = RedUp+(GreenUp<<1)+(BlueUp<<2)+(RedDn<<3)+(GreenDn<<4)+(BlueDn<<5);
        // if(row<4)
        //    col_data |= rgbVal;

        u16 rgbVal;
        if(ledColor == RED)
        {
            rgbVal = 0x01;
            if(row < 4)
                col_data |= rgbVal;
        }
        else if(ledColor == BLUE)
        {
            rgbVal = 1<<5;
            if(row < 4)
                col_data |= rgbVal;
        }
        else if(ledColor == GREEN)
        {
            rgbVal = 1<<1;
            if(row>4)
                col_data |= rgbVal;
        }
        else if(ledColor == YELLOR)
        {
            rgbVal = (1<<3)+ (1<<4);
            if(row>4)
                col_data |= rgbVal;
        }
        
        // 2. 串行发送 16 位数据给 SM16208（OUT0~OUT7 对应低字节）
        uint16_t send_data = (uint16_t)col_data; 
        for (int i = 0; i < 16; i++) 
        {
            if(send_data & 0x8000)
            {
                HAL_GPIO_WritePin(SDI_GPIO,SDI_PIN,GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(SDI_GPIO,SDI_PIN,GPIO_PIN_RESET);
            }

            HAL_GPIO_WritePin(SCK_GPIO,SCK_PIN,GPIO_PIN_SET);
            asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
            HAL_GPIO_WritePin(SCK_GPIO,SCK_PIN,GPIO_PIN_RESET);
            send_data <<= 1;
        }
        
        // 3. 产生锁存信号，更新列驱动
        HAL_GPIO_WritePin(LE_GPIO,LE_PIN,GPIO_PIN_SET);
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        HAL_GPIO_WritePin(LE_GPIO,LE_PIN,GPIO_PIN_RESET);
        
        // 4. 消影：关闭显示
        HAL_GPIO_WritePin(OE_GPIO,OE_PIN,GPIO_PIN_SET);
        
        // 5. 切换行选：通过 3 根线控制 SM5166 选通当前行
        if(row&0x04)
            HAL_GPIO_WritePin(A2_GPIO,A2_PIN,GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(A2_GPIO,A2_PIN,GPIO_PIN_RESET);

        if(row&0x02)
            HAL_GPIO_WritePin(A1_GPIO,A1_PIN,GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(A1_GPIO,A1_PIN,GPIO_PIN_RESET);

        if(row&0x01)
            HAL_GPIO_WritePin(A0_GPIO,A0_PIN,GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(A0_GPIO,A0_PIN,GPIO_PIN_RESET);
        
        // 6. 开启显示并延时
        HAL_GPIO_WritePin(OE_GPIO,OE_PIN,GPIO_PIN_RESET);

        delay_ms(1); // 每一行点亮 1 毫秒
       
        key_arr[row] = ReadKeyData();
        
        process_key_events();

        if(pass_mission_flag == 0)
        {
            if(CompareArr(key_filter,matrix,8))
            {
                pass_mission_flag = 1;
                play_audio_flag = 1;
                show_flag = SHOW_PASS;
            }
        }
       
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


u8 CompareArr(u8* arr1,u8 *arr2,u8 len)
{
    u8 equalCnt = 0;
    for(int i=0;i<8;i++)
    {
        if(0xFF-key_arr[i] == arr2[i])
            equalCnt++;
    }
    if(equalCnt == 8)
    {
        return 1;
    }
    else
        return 0;
    
}