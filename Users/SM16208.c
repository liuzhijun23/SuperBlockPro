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