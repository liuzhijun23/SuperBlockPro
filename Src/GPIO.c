#include "GPIO.h"
#include "timer.h"
#include "GlobalVar.h"
#include "apm32e030_rcm.h"

void EnableAllGpio(void)
{
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
}

//PWM频率=72M/4/256=70.3kHz
void SpeakerInit(void)
{
    TMR_TimeBase_T  timeBaseConfig;
    TMR_OCConfig_T  occonfig;
    GPIO_Config_T   gpioconfig;
    /* Enable Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_TMR15);

    /*  Connect TMR1 to CH1 */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_PIN0);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_3, GPIO_AF_PIN0);
    gpioconfig.mode  = GPIO_MODE_AF;
    gpioconfig.outtype = GPIO_OUT_TYPE_PP;
    gpioconfig.pin   = GPIO_PIN_2|GPIO_PIN_3;
    gpioconfig.pupd  = GPIO_PUPD_NO;
    gpioconfig.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &gpioconfig);

    /* Set clockDivision = 1 */
    timeBaseConfig.clockDivision =  TMR_CKD_DIV1;
    /* Up-counter */
    timeBaseConfig.counterMode =  TMR_COUNTER_MODE_UP;
    /* Set divider = 71 .So TMR1 clock freq ~= 72/(71+1) = 1MHZ */
    timeBaseConfig.div = 3 ;
    /* Set counter = 999 */
    timeBaseConfig.period = SPEAKER_ARR;
    /* Repetition counter = 0x0 */
    timeBaseConfig.repetitionCounter =  0;
    TMR_ConfigTimeBase(TMR1, &timeBaseConfig);

    /* PWM1 mode */
    occonfig.OC_Mode =  TMR_OC_MODE_PWM1;
    /* Idle State is reset */
    occonfig.OC_Idlestate  = TMR_OCIDLESTATE_RESET;
    /* NIdle State is reset */
    occonfig.OC_NIdlestate = TMR_OCNIDLESTATE_RESET;
    /* Enable CH1N ouput */
    occonfig.OC_OutputNState =  TMR_OUTPUT_NSTATE_DISABLE;
    /* Enable CH1 ouput */
    occonfig.OC_OutputState  =  TMR_OUTPUT_STATE_ENABLE;
    /* CH1  polarity is high */
    occonfig.OC_Polarity  = TMR_OC_POLARITY_HIGH;
    /* CH1N polarity is high */
    occonfig.OC_NPolarity = TMR_OC_NPOLARITY_HIGH;
    /* Set compare value */
    occonfig.Pulse = 128;
    TMR_OC1Config(TMR15, &occonfig);

    occonfig.OC_Polarity  = TMR_OC_POLARITY_LOW;
    TMR_OC2Config(TMR15, &occonfig);

    /* Enable PWM output */
    TMR_EnablePWMOutputs(TMR15);
    /*  Enable TMR1  */
    TMR_Enable(TMR15);
}

void Set_Speaker_Duty(uint16_t duty_ch1, uint16_t duty_ch2)
{
    if (duty_ch1 > SPEAKER_ARR) duty_ch1 = SPEAKER_ARR;
    if (duty_ch2 > SPEAKER_ARR) duty_ch2 = SPEAKER_ARR;

    TMR15->CC1 = duty_ch1;
    TMR15->CC2 = duty_ch2;
}
