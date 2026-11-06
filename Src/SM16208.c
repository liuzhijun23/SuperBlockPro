#include "SM16208.h"

uint8_t image_matrix[8] = { 0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C };
u8 key_arr[8];
u8 key_history[8][CONFIRM_NUM];
u8 key_filter[8];
static u8 board_pressed[8];
static volatile u8 board_frames;

//u8 image_arr[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//u8 image_arr[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

u8 image_arr[][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x00, 0x00, 0x3C, 0x24, 0x24, 0x24, 0x3C, 0x00 },//0
    { 0x00, 0x00, 0x10, 0x18, 0x10, 0x10, 0x38, 0x00 },//1
    { 0x00, 0x00, 0x3C, 0x20, 0x3C, 0x04, 0x3C, 0x00 },//2
    { 0x00, 0x00, 0x3C, 0x20, 0x3C, 0x20, 0x3C, 0x00 },//3
    { 0x00, 0x00, 0x24, 0x24, 0x3C, 0x20, 0x20, 0x00 },//4
    { 0x00, 0x00, 0x3C, 0x04, 0x3C, 0x20, 0x3C, 0x00 },//5
    { 0x00, 0x00, 0x3C, 0x04, 0x3C, 0x24, 0x3C, 0x00 },//6
    { 0x00, 0x00, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x00 },//7
    { 0x00, 0x00, 0x3C, 0x24, 0x3C, 0x24, 0x3C, 0x00 },//8
    { 0x00, 0x00, 0x3C, 0x24, 0x3C, 0x20, 0x3C, 0x00 },//9
    
};

u8 level_arr[][8] = {
    { 0x00, 0x0E, 0x06, 0x02, 0x60, 0x70, 0x20, 0x00 },//1
    { 0x00, 0x10, 0x38, 0x18, 0x00, 0x03, 0xF1, 0x83 },
    { 0x00, 0x00, 0x00, 0x00, 0x40, 0x50, 0x58, 0x7C },
    { 0x02, 0x07, 0x06, 0x00, 0x1C, 0x18, 0x38, 0x38,},
    { 0x00, 0x00, 0x00, 0x60, 0x70, 0x78, 0x60, 0x00 },
    { 0x00, 0x00, 0x00, 0x78, 0x78, 0x38, 0x00, 0x00 },//6
    { 0x00, 0x00, 0x70, 0x70, 0x78, 0x30, 0x00, 0x00 },//7
    { 0x0E, 0x1E, 0x0E, 0x02, 0x70, 0x70, 0x30, 0x38 },//8
    { 0x30, 0x3C, 0x1C, 0x1C, 0x00, 0x1C, 0x1C, 0x78 },//9
    { 0x00, 0x28, 0x3C, 0x3C, 0x00, 0x24, 0x3E, 0x3E },//10
};

const u16 level_count = sizeof(level_arr) / sizeof(level_arr[0]);


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

static uint8_t scan_row = 0;
static uint8_t scan_row_valid = 0;
static volatile uint8_t display_scan_en = 0;

/* 开启中断逐行扫描。调用后�?TIM16 中断�?1ms 刷新一�?*/
void Display_ScanStart(void)
{
    scan_row = 0;
    scan_row_valid = 0;
    board_frames = 0;
    display_scan_en = 1;
}

/* 停止扫描。开机动画等直接操作显示引脚的流程前调用 */
void Display_ScanStop(void)
{
    display_scan_en = 0;
    scan_row_valid = 0;
    board_frames = 0;
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_SET);
}

/*
 * �?1ms �?TIM16 中断调用一次，只处理一行，禁止在函数内使用 delay_ms()�? * 本次中断先读取已点亮�?1ms 的上一行按键，再输出并点亮当前行，
 * 由下一次中断间隔提供原来的 1ms 点亮时间�? 次中断完成一帧�? */
void display_matrix(u8* matrix)
{
    uint8_t row;
    u16 col_data;
    u16 rgbVal;
    uint16_t send_data;
    int i;

    if (!display_scan_en || matrix == NULL)
        return;

    row = scan_row;

    if (scan_row_valid)
    {
        uint8_t key_row = (row + 7u) & 0x07u;
        u8 *history = key_history[key_row];
        u8 all_high, all_low;
        key_arr[key_row] = ReadKeyData();
        history[2] = history[1];
        history[1] = history[0];
        history[0] = key_arr[key_row];
        all_high = history[0] & history[1] & history[2];
        all_low = (u8)~(history[0] | history[1] | history[2]);
        key_filter[key_row] = (key_filter[key_row] | all_high) & (u8)~all_low;

        /* Publish only after every row has been sampled. Keys are active-low. */
        if (row == 0u)
        {
            for (i = 0; i < 8; ++i)
                board_pressed[i] = (u8)~key_filter[i];
            if (board_frames < CONFIRM_NUM)
                ++board_frames;
        }
    }

    /* Read column data for the current row. */
    col_data = ((u16)matrix[row] << 6);

    if (ledColor == RED)
    {
        rgbVal = 0x01;
        if (row < 4)
            col_data |= rgbVal;
    }
    else if (ledColor == BLUE)
    {
        rgbVal = 1 << 5;
        if (row < 4)
            col_data |= rgbVal;
    }
    else if (ledColor == GREEN)
    {
        rgbVal = 1 << 1;
        if (row > 4)
            col_data |= rgbVal;
    }
    else if (ledColor == YELLOR)
    {
        rgbVal = (1 << 3) + (1 << 4);
        if (row > 4)
            col_data |= rgbVal;
    }

    if (row > 3)
    {
        col_data |= (MLED1 << 15) + (MLED2 << 14);
    }

    // 2. 串行发�?16 位数据给 SM16208（OUT0~OUT7 对应低字节）
    send_data = (uint16_t)col_data;
    for (i = 0; i < 16; i++)
    {
        if (send_data & 0x8000)
        {
            HAL_GPIO_WritePin(SDI_GPIO, SDI_PIN, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(SDI_GPIO, SDI_PIN, GPIO_PIN_RESET);
        }

        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_SET);
        asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_RESET);
        send_data <<= 1;
    }

    // 3. 产生锁存信号，更新列驱动
    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_SET);
    asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_RESET);

    /* Blank output while changing row. */
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_SET);

    // 5. 切换行选：通过 3 根线控制 SM5166 选通当前行
    HAL_GPIO_WritePin(A2_GPIO, A2_PIN, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A1_GPIO, A1_PIN, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A0_GPIO, A0_PIN, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // 6. 开启显示，保持到下一�?1ms 中断
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_RESET);

    scan_row_valid = 1;
    scan_row = (row + 1) & 0x07;
}

/* Copy a single completed board frame before the ISR can replace it. */
u8 Board_ReadPressed(u8 pressed[8])
{
    u32 primask = __get_PRIMASK();
    u8 ready;
    u8 i;
    __disable_irq();
    ready = (board_frames >= CONFIRM_NUM);
    if (ready)
        for (i = 0; i < 8; ++i)
            pressed[i] = board_pressed[i];
    __set_PRIMASK(primask);
    return ready;
}
