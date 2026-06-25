#include "GPIO.h"
#include "TM1650.h"
#include "timer.h"
#include "GlobalVar.h"

void MY_GPIO_Init(void)
{
    GPIO_Init(KEYL_GPIO, KEYL_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(KEYR_GPIO, KEYR_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(BEEP_GPIO, BEEP_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(UV_LED_GPIO, UV_LED_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(RELAY_GPIO, RELAY_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(PUMP_GPIO, PUMP_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(FAN_GPIO, FAN_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(FORCE_GPIO, FORCE_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(MODE_KEY_GPIO, MODE_KEY_PIN, GPIO_MODE_IN_PU_IT);
    GPIO_Init(CLOSE_DET_GPIO, CLOSE_DET_PIN, GPIO_MODE_IN_PU_NO_IT);
    PUMP_OFF();
    UV_LED_OFF();
    RELAY_OFF();
    FAN_OFF();
}

void exit_init(void)
{
    EXTI_DeInit();
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD,EXTI_SENSITIVITY_FALL_ONLY);
}

u8 KeyScan(void)
{
    static u8 key_up = 1;//按键按松开标志
    if( (KEYL_STATUS() == 0 || KEYR_STATUS() == 0))
	{
		delay_ms(20);//去抖动 
		key_up=0;
		if(KEYL_STATUS() == 0) return KEY_L;
		else if(KEYR_STATUS()==0)return KEY_R;
	}
    else if(KEYL_STATUS() && KEYR_STATUS())
        key_up=1; 	    
 	return 0;// 无按键按下
}

void SpeakerInit(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);

    TIM1_DeInit();

    TIM1_TimeBaseInit(15, TIM1_COUNTERMODE_UP, SPEAKER_ARR, 0);
    TIM1_OC2Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
                 0, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_RESET);
                 
    // 通道 3 配置 (PC3)
    TIM1_OC3Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
                 0, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_LOW, TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_RESET);

    TIM1_OC2PreloadConfig(ENABLE);
    TIM1_OC3PreloadConfig(ENABLE);
    TIM1_ARRPreloadConfig(ENABLE);

    TIM1_CtrlPWMOutputs(ENABLE);

    TIM1_Cmd(ENABLE);
}

void Set_Speaker_Duty(uint16_t duty_ch2, uint16_t duty_ch3)
{
    if (duty_ch2 > SPEAKER_ARR) duty_ch2 = SPEAKER_ARR;
    if (duty_ch3 > SPEAKER_ARR) duty_ch3 = SPEAKER_ARR;

    TIM1_SetCompare2(duty_ch2); // 修改 PC2 的占空比
    TIM1_SetCompare3(duty_ch3); // 修改 PC3 的占空比
}