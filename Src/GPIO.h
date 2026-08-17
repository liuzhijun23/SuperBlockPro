#ifndef GPIO_H_
#define GPIO_H_
#include "main.h"


#define SPEAKER_ARR     255

extern u16 voiceArr1[];

void EnableAllGpio(void);
void SpeakerInit(void);
void Set_Speaker_Duty(uint16_t duty_ch2, uint16_t duty_ch3);

#endif