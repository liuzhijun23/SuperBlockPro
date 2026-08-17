#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

#include "apm32e030.h"
#include "apm32e030_tmr.h"
#include "apm32e030_rcm.h"
#include "apm32e030_gpio.h"
#include "apm32e030_fmc.h"

#include "timer.h"
#include "GPIO.h"
#include "audio.h"
#include "SM16208.h"
#include "main.h"

/* APM32E030 无数据EEPROM，用内部Flash最后一页(1KB)存储参数 */
#define FLASH_USER_PAGE_ADDR    0x0800FC00
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