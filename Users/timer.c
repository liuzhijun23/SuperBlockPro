#include "timer.h"
#include "GlobalVar.h"

//延时函数初始化
//为确保准确度,请保证时钟频率最好为4的倍数,最低8Mhz
// clk:时钟频率(24/16/12/8等)

volatile u8 fac_us = 0; // us延时倍乘数

void TIM4_Config(void)
{
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 1000-1);
    /* Clear TIM4 update flag */
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    /* Enable update interrupt */
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

    /* enable interrupts */
    enableInterrupts();

    /* Enable TIM4 */
    TIM4_Cmd(ENABLE);
}

void delay_ms(u32 nms)
{
    TimingDelay = nms;
    while (TimingDelay != 0);
}

void TIM2_Config(void)
{
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_16,499);
    TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE, 250,TIM2_OCPOLARITY_LOW);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_ARRPreloadConfig(ENABLE);
    //TIM2_Cmd(ENABLE);
}