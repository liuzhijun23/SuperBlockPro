#ifndef SM16208_H_
#define SM16208_H_

#include "stm8s.h"

#define SDI_GPIO    GPIOC
#define SDI_PIN     GPIO_PIN_6

#define SCK_GPIO    GPIOC
#define SCK_PIN     GPIO_PIN_5

#define LE_GPIO     GPIOC
#define LE_PIN      GPIO_PIN_4

#define OE_GPIO     GPIOD
#define OE_PIN      GPIO_PIN_0

#define A2_GPIO     GPIOD
#define A2_PIN      GPIO_PIN_4

#define A1_GPIO     GPIOD
#define A1_PIN      GPIO_PIN_3

#define A0_GPIO     GPIOD
#define A0_PIN      GPIO_PIN_2

#define KEY_PORT    GPIOB


void SM16208_Init(void);
void display_matrix(u8* matrix);

#endif