#ifndef GPIO_H_
#define GPIO_H_
#include "GlobalVar.h"


#define SPEAKER_ARR     255

extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim3;
extern u16 voiceArr1[];

void EnableAllGpio(void);
void SpeakerInit(void);
void Set_Speaker_Duty(uint16_t duty_ch2, uint16_t duty_ch3);

#endif