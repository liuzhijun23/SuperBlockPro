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

#define KEY2_GPIO   GPIOA
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

enum {
    IMAG_INDEX_DARK = 0,
    IMAG_INDEX_LIGHT,
    IMAG_INDEX_0,
    IMAG_INDEX_1,
    IMAG_INDEX_2,
    IMAG_INDEX_3,
    IMAG_INDEX_4,
    IMAG_INDEX_5,
    IMAG_INDEX_6,
    IMAG_INDEX_7,
    IMAG_INDEX_8,
    IMAG_INDEX_9,
    
};

extern const u8 image_arr[][8];
extern const u8 level_arr[][8];
extern u8 key_arr[8];
extern u8 key_history[8][CONFIRM_NUM];
extern u8 key_filter[8];
extern const u16 level_count;


void SM16208_Init(void);
void Display_ScanStart(void);
void Display_ScanStop(void);
void display_matrix(const u8* matrix);   /* 仅供 TIM16 1ms 中断调用，每次刷新一行 */
u8 ReadKeyData(void);
u8 Board_ReadPressed(u8 pressed[8]);

#endif