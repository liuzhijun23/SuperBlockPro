#include "timer.h"
#include "GlobalVar.h"
#include "apm32e030_tmr.h"
#include "apm32e030_rcm.h"

//延时函数初始化
//为确保准确度,请保证时钟频率最好为4的倍数,最低8Mhz
// clk:时钟频率(24/16/12/8等)

volatile u8 fac_us = 0; // us延时倍乘数


void TIM6_Config(void)
{
    TMR_TimeBase_T  timeBaseConfig;

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR6);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /* Set divider = 71.So TMR1 clock freq ~= 72/(71 + 1) = 1MHZ */
    timeBaseConfig.div = 71 ;
    /* Set counter = 0xffff */
    timeBaseConfig.period = 1000-1;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;

    TMR_ConfigTimeBase(TMR6, &timeBaseConfig);

    /* Enable update interrupt*/
    TMR_EnableInterrupt(TMR6, TMR_INT_UPDATE);
    NVIC_EnableIRQRequest(TMR6_IRQn, 2);

    /*  Enable TMR14  */
    TMR_Enable(TMR6);
}

void delay_ms(u32 nms)
{
    TimingDelay = nms;
    while (TimingDelay != 0);
}

//周期72M/36/250=8K
void TIM17_Config(void)
{
    TMR_TimeBase_T  timeBaseConfig;

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB1PeriphClock(RCM_APB2_PERIPH_TMR17);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /* Set divider = 71.So TMR1 clock freq ~= 72/(71 + 1) = 1MHZ */
    timeBaseConfig.div = 35 ;
    /* Set counter = 0xffff */
    timeBaseConfig.period = 250-1;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;

    TMR_ConfigTimeBase(TMR17, &timeBaseConfig);

    /* Enable update interrupt*/
    TMR_EnableInterrupt(TMR17, TMR_INT_UPDATE);
    NVIC_EnableIRQRequest(TMR17_IRQn, 2);

    /*  Enable TMR14  */
    TMR_Enable(TMR17);
}