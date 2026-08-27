#include "GlobalVar.h"

__IO uint32_t TimingDelay = 0;
u16 workTimeSetting = 60;//工作时间设定，单位秒
u16 workTime = 0;    //已工作时间，单位ms
__IO u8 fall_flag = 0;
__IO u16 fall_delay = 0; 
__IO u16 release_delay = 0;
__IO u8 keyState = 0;
__IO u8 work_event = 0;

u16 debugData1 = 0;
u16 debugData2 = 0;
u16 debugData3 = 0;
u16 debugData4 = 0;

u16 ReadTimeSetting(void)
{
    /* Flash内容可直接通过地址读取；未写入过(0xFFFF)时返回默认值 */
    u16 time = *(__IO u16 *)WORKING_TIME_SAVE_ADDR;
    if (time == 0xFFFF)
    {
        time = WORK_TIME_DEFAULT;
    }
    return time;
}

void WriteTimeSetting(u16 time)
{
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError = 0;

    HAL_FLASH_Unlock();

    /* 写入前必须整页擦除 */
    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.Page = (FLASH_USER_PAGE_ADDR - FLASH_BASE) / FLASH_PAGE_SIZE;
    eraseInit.NbPages = 1;
    if (HAL_FLASHEx_Erase(&eraseInit, &pageError) == HAL_OK)
    {
        /* G0仅支持64位双字编程，高48位保持1(0xFF) */
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WORKING_TIME_SAVE_ADDR,
                          0xFFFFFFFFFFFF0000ULL | (u64)time);
    }

    HAL_FLASH_Lock();
}