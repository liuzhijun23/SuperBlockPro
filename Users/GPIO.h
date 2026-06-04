#ifndef GPIO_H_
#define GPIO_H_
#include "stm8s.h"

#define MODE_KEY_GPIO   GPIOD
#define MODE_KEY_PIN    GPIO_PIN_6

//蜂鸣器
#define BEEP_GPIO   GPIOD
#define BEEP_PIN    GPIO_PIN_4

//UV灯
#define UV_LED_GPIO     GPIOA
#define UV_LED_PIN      GPIO_PIN_1

//气泵
#define PUMP_GPIO   GPIOA
#define PUMP_PIN    GPIO_PIN_3

//电磁阀
#define RELAY_GPIO  GPIOB 
#define RELAY_PIN   GPIO_PIN_4

//负压开关
#define FORCE_GPIO  GPIOC
#define FORCE_PIN   GPIO_PIN_7

//风扇控制信号
#define FAN_GPIO    GPIOD
#define FAN_PIN     GPIO_PIN_3

//箱盖闭合传感器信号
#define CLOSE_DET_GPIO  GPIOB
#define CLOSE_DET_PIN   GPIO_PIN_5

//按键1和2
#define KEYR_GPIO   GPIOC
#define KEYR_PIN    GPIO_PIN_3
#define KEYL_GPIO   GPIOD
#define KEYL_PIN    GPIO_PIN_2

#define KEY_NULL    0
#define KEY_L       1
#define KEY_R       2

#define MODE_KEY_STATUS()   GPIO_ReadInputPin(MODE_KEY_GPIO,MODE_KEY_PIN)
#define UV_LED_ON() GPIO_WriteHigh(UV_LED_GPIO,UV_LED_PIN)
#define UV_LED_OFF() GPIO_WriteLow(UV_LED_GPIO,UV_LED_PIN)
#define PUMP_ON()   GPIO_WriteHigh(PUMP_GPIO,PUMP_PIN)
#define PUMP_OFF()  GPIO_WriteLow(PUMP_GPIO,PUMP_PIN)
#define FORCE_STATUS() GPIO_ReadInputPin(FORCE_GPIO,FORCE_PIN)
#define KEYL_STATUS()   GPIO_ReadInputPin(KEYL_GPIO,KEYL_PIN)
#define KEYR_STATUS()   GPIO_ReadInputPin(KEYR_GPIO,KEYR_PIN)
#define RELAY_ON()  GPIO_WriteHigh(RELAY_GPIO,RELAY_PIN)
#define RELAY_OFF()  GPIO_WriteLow(RELAY_GPIO,RELAY_PIN)
#define CLOSE_DET_STATUS()  GPIO_ReadInputPin(CLOSE_DET_GPIO,CLOSE_DET_PIN)
#define FAN_ON()    GPIO_WriteHigh(FAN_GPIO,FAN_PIN)
#define FAN_OFF()    GPIO_WriteLow(FAN_GPIO,FAN_PIN)

void exit_init(void);
void MY_GPIO_Init(void);
u8 KeyScan(void);
void KeyProcess(void);

#endif