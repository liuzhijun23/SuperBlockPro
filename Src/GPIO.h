#ifndef GPIO_H_
#define GPIO_H_
#include "GlobalVar.h"


#define SPEAKER_ARR     255

#define KEY_POS_GPIO    GPIOB
#define KEY_POS_PIN     GPIO_PIN_6

#define POWER_KEY_GPIO  GPIOB
#define POWER_KEY_PIN   GPIO_PIN_5

#define LEFT_KEY_GPIO   GPIOB
#define LEFT_KEY_PIN    GPIO_PIN_4

#define RIGHT_KEY_GPIO  GPIOB
#define RIGHT_KEY_PIN   GPIO_PIN_3

#define POWER_KEY_STATUS()  HAL_GPIO_ReadPin(POWER_KEY_GPIO,POWER_KEY_PIN)
#define LEFT_KEY_STATUS()   HAL_GPIO_ReadPin(LEFT_KEY_GPIO,LEFT_KEY_PIN)
#define RIGHT_KEY_STATUS()   HAL_GPIO_ReadPin(RIGHT_KEY_GPIO,RIGHT_KEY_PIN)

extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim3;
extern u16 voiceArr1[];

void EnableAllGpio(void);
void SpeakerInit(void);
void Set_Speaker_Duty(uint16_t duty_ch2, uint16_t duty_ch3);
void KeyInit(void);

#endif