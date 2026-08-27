#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H
#include "stm32g0xx.h"
#include "stm32g0xx_hal.h"

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  
typedef const int16_t sc16;  
typedef const int8_t sc8;  

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  
typedef __I int16_t vsc16; 
typedef __I int8_t vsc8;   

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  
typedef const uint16_t uc16;  
typedef const uint8_t uc8; 

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  	

typedef int64_t		s64;
typedef uint64_t	u64;

#define false   0
#define true    1

/* STM32G030K8 无数据EEPROM，用内部Flash最后一页(2KB)存储参数 */
#define FLASH_USER_PAGE_ADDR    0x0800F800
#define WORKING_TIME_SAVE_ADDR  FLASH_USER_PAGE_ADDR
#define WORK_TIME_DEFAULT       60      //默认工作时间，单位分钟

u16 ReadTimeSetting(void);
void WriteTimeSetting(u16 time);

extern __IO uint32_t TimingDelay;
extern u16 workTimeSetting;//工作时间设定，单位分钟
extern u16 workTime;    //已工作时间，单位ms
extern __IO u8 fall_flag;
extern __IO u16 fall_delay;
extern __IO u16 release_delay;
extern __IO u8 keyState;
extern __IO u8 work_event;

extern u16 debugData1;
extern u16 debugData2;
extern u16 debugData3;
extern u16 debugData4;
#endif