#ifndef _TIMER_H
#define _TIMER_H
#include "stm32g0xx.h"
#include "GlobalVar.h"


#define BEEP_ON()   TIM2_Cmd(ENABLE)
#define BEEP_OFF()  TIM2_Cmd(DISABLE)

extern TIM_HandleTypeDef TIM16_Handler;
extern TIM_HandleTypeDef TIM17_Handler;

void TIM16_Config(void);
void delay_ms(u32 nms);
void TIM17_Config(void);
#endif