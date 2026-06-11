#include "GlobalVar.h"
#include "stm8s_flash.h"

__IO uint32_t TimingDelay = 0;
u16 workTimeSetting = 60;//工作时间设定，单位秒
u16 workTime = 0;    //已工作时间，单位ms
__IO u8 fall_flag = 0;
__IO u16 fall_delay = 0; 
__IO u16 release_delay = 0;
__IO u8 keyState = 0;
__IO u8 work_event = 0;

u8 debugData1 = 0;
u8 debugData2 = 0;
u8 debugData3 = 0;
u8 debugData4 = 0;

u16 ReadTimeSetting(void)
{
    u8 data1 = FLASH_ReadByte(WORKING_TIME_SAVE_ADDR+2);
    u8 data2 = FLASH_ReadByte(WORKING_TIME_SAVE_ADDR+3);
    return ((u16)data1<<8)+data2;
}

void WriteTimeSetting(u16 time)
{
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    FLASH_ProgramWord(WORKING_TIME_SAVE_ADDR, time);
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}