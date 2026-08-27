#include "GPIO.h"
#include "timer.h"
#include "GlobalVar.h"

TIM_HandleTypeDef htim14;
TIM_HandleTypeDef htim3;
TIM_OC_InitTypeDef ocHandle;

void EnableAllGpio(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}


void SpeakerInit(void)
{
    __HAL_RCC_TIM14_CLK_ENABLE();

    GPIO_InitTypeDef g;
    g.Pin = GPIO_PIN_4;
    g.Mode = GPIO_MODE_AF_PP;
    g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_FREQ_HIGH;
    g.Alternate = GPIO_AF4_TIM14;   // 关键！AF0
    HAL_GPIO_Init(GPIOA, &g);

    htim14.Instance = TIM14;
    htim14.Init.Prescaler = 3;                 // 假设系统时钟 48MHz → 定时器时钟 1MHz
    htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim14.Init.Period = SPEAKER_ARR;                   // 1MHz / 1000 = 1kHz PWM 频率
    htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim14.Init.RepetitionCounter = 0;
    htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&htim14);

    ocHandle.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    ocHandle.Pulse=0;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    ocHandle.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&htim14,&ocHandle,TIM_CHANNEL_1);//配置TIM3通道3

    __HAL_RCC_TIM3_CLK_ENABLE();

    g.Pin = GPIO_PIN_6;
    g.Mode = GPIO_MODE_AF_PP;
    g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_FREQ_HIGH;
    g.Alternate = GPIO_AF1_TIM3;   // 关键！AF0
    HAL_GPIO_Init(GPIOA, &g);

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 3;                 // 假设系统时钟 48MHz → 定时器时钟 1MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = SPEAKER_ARR;                   // 1MHz / 1000 = 1kHz PWM 频率
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.RepetitionCounter = 0;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&htim3);

    ocHandle.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    ocHandle.Pulse=0;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    ocHandle.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&htim3,&ocHandle,TIM_CHANNEL_1);//配置TIM3通道3
}


void Set_Speaker_Duty(uint16_t duty_ch1, uint16_t duty_ch2)
{
    if (duty_ch1 > SPEAKER_ARR) duty_ch1 = SPEAKER_ARR;
    if (duty_ch2 > SPEAKER_ARR) duty_ch2 = SPEAKER_ARR;

    TIM14->CCR1 = duty_ch1;
    TIM3->CCR1 = duty_ch2;
}
