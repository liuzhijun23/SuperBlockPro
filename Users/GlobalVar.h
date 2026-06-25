#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H
#include "stm8s.h"

#define WORKING_TIME_SAVE_ADDR  0x4100

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