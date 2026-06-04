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

void KeyProcess(void)
{
    static u8 lastKey = 0;
    static u16 slowTimes = 0;
    u8 key = KeyScan();
    switch (key)
    {
    case KEY_NULL:
        break;
    case KEY_L:
        if (lastKey == key)
            slowTimes++;
        else
            slowTimes = 0;
        if (slowTimes < 5)
            delay_ms(200);
        if(slowTimes < 20)  
        {
            if(workTimeSetting > 1)
                workTimeSetting--;
        }  
        else if(slowTimes < 40)
        {
            if(workTimeSetting > 5)
                workTimeSetting -= 5;
        }  
        else if(workTimeSetting > 10)
        {
            workTimeSetting -= 10;    
        }
        TM1650_Show_Number(workTimeSetting);
        WriteTimeSetting(workTimeSetting);
        break;
    case KEY_R:
        if (lastKey == key)
            slowTimes++;
        else
            slowTimes = 0;
        if (slowTimes < 5)
            delay_ms(200);
        if(slowTimes < 20)  
        {
            workTimeSetting++;
        }  
        else if(slowTimes < 40)
        {
            workTimeSetting += 5;
        }  
        else 
        {
            workTimeSetting += 10;    
        }
        TM1650_Show_Number(workTimeSetting);
        WriteTimeSetting(workTimeSetting);
        break;
    default:
        break;
    }
    lastKey = key;
}