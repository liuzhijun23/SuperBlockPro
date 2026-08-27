#ifndef SM16208_H_
#define SM16208_H_

#include "stm32g0xx.h"
#include "GlobalVar.h"

#define POWER_GPIO  GPIOA
#define POWER_PIN   GPIO_PIN_15

#define SDI_GPIO    GPIOA
#define SDI_PIN     GPIO_PIN_7

#define SCK_GPIO    GPIOA
#define SCK_PIN     GPIO_PIN_5

#define LE_GPIO     GPIOA
#define LE_PIN      GPIO_PIN_3

#define OE_GPIO     GPIOB
#define OE_PIN      GPIO_PIN_0

#define A2_GPIO     GPIOA
#define A2_PIN      GPIO_PIN_0

#define A1_GPIO     GPIOA
#define A1_PIN      GPIO_PIN_1

#define A0_GPIO     GPIOA
#define A0_PIN      GPIO_PIN_2

#define SET_POWER_PIN(x)  HAL_GPIO_WritePin(POWER_GPIO,POWER_PIN,x)

#define KEY0_GPIO   GPIOB
#define KEY0_PIN    GPIO_PIN_1

#define KEY1_GPIO   GPIOB
#define KEY1_PIN    GPIO_PIN_2

#define KEY2_GPIO   GPIOB
#define KEY2_PIN    GPIO_PIN_8

#define KEY3_GPIO   GPIOA
#define KEY3_PIN    GPIO_PIN_9

#define KEY4_GPIO   GPIOC
#define KEY4_PIN    GPIO_PIN_6

#define KEY5_GPIO   GPIOA
#define KEY5_PIN    GPIO_PIN_10

#define KEY6_GPIO   GPIOA
#define KEY6_PIN    GPIO_PIN_11

#define KEY7_GPIO   GPIOA
#define KEY7_PIN    GPIO_PIN_12

#define CONFIRM_NUM     3

extern u8 image_arr[][8];

extern u8 key_arr[8];
extern u8 key_history[8][CONFIRM_NUM];
extern u8 key_filter[8];
extern u8 key_filter_pre[8];


void SM16208_Init(void);
void display_matrix(u8* matrix);
void process_key_events();
u8 ReadKeyData(void);

#endif