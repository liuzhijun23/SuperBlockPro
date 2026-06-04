#ifndef _TIMER_H
#define _TIMER_H
#include "stm8s.h"

#define F_CPU 16000000

#define BEEP_ON()   TIM2_Cmd(ENABLE)
#define BEEP_OFF()  TIM2_Cmd(DISABLE)

void TIM4_Config(void);
void delay_ms(u32 nms);
void TIM2_Config(void);
#endif