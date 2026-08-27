#include "timer.h"
#include "GlobalVar.h"

//延时函数初始化
//为确保准确度,请保证时钟频率最好为4的倍数,最低8Mhz
// clk:时钟频率(24/16/12/8等)

volatile u8 fac_us = 0; // us延时倍乘数

TIM_HandleTypeDef TIM16_Handler;
TIM_HandleTypeDef TIM17_Handler;

void TIM16_Config(void)
{
    __HAL_RCC_TIM16_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM16_IRQn,2,1);
    HAL_NVIC_EnableIRQ(TIM16_IRQn);

    TIM16_Handler.Instance=TIM16;                          //通用定时器7
    TIM16_Handler.Init.Prescaler=63;                     //分频系数
    TIM16_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM16_Handler.Init.Period=1000-1;                        //自动装载值
    TIM16_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM16_Handler);
    HAL_TIM_Base_Start_IT(&TIM16_Handler); //使能定时器7和定时器7更新中断：TIM_IT_UPDATE  
}

void delay_ms(u32 nms)
{
    TimingDelay = nms;
    while (TimingDelay != 0);
}

//周期72M/36/250=8K
void TIM17_Config(void)
{
    __HAL_RCC_TIM17_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM17_IRQn,2,1);
    HAL_NVIC_EnableIRQ(TIM17_IRQn);

    TIM17_Handler.Instance=TIM17;                          //通用定时器7
    TIM17_Handler.Init.Prescaler=31;                     //分频系数
    TIM17_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM17_Handler.Init.Period=249;                        //自动装载值
    TIM17_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM17_Handler);
    //HAL_TIM_Base_Start_IT(&TIM17_Handler); //使能定时器7和定时器7更新中断：TIM_IT_UPDATE  
}