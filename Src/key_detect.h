#ifndef KEY_DETECT_H_
#define KEY_DETECT_H_

#include "stm32g0xx.h"

/*
 * 按键事件定义 (对应需求的 11 种)
 */
typedef enum
{
    KEY_EVT_NONE = 0,
    KEY_EVT_POWER_LONG       = 1,   /* 1  电源键长按 */
    KEY_EVT_LEFT_SHORT       = 2,   /* 2  左键短按 */
    KEY_EVT_RIGHT_SHORT      = 3,   /* 3  右键短按 */
    KEY_EVT_LEFT_LONG        = 4,   /* 4  左键长按 */
    KEY_EVT_RIGHT_LONG       = 5,   /* 5  右键长按 */
    KEY_EVT_LR_LONG          = 6,   /* 6  左右键同时长按 */
    KEY_EVT_POWER_LEFT_LONG  = 7,   /* 7  电源键+左键长按 */
    KEY_EVT_POWER_RIGHT_LONG = 8,   /* 8  电源键+右键长按 */
    KEY_EVT_POWER_DOUBLE     = 9,   /* 9  电源键快按2下 */
    KEY_EVT_POWER_SHORT      = 10,  /* 10 电源键短按 */
    KEY_EVT_LR_SHORT         = 11,  /* 11 左右键同时短按 */
} KeyEvt_t;

/* 初始化, main 里调用一次 */
void     Key_Detect_Init(void);

/* 周期扫描: 每 1ms 调用一次(建议放在 TIM16 1ms 中断里), 内部按 10ms 节拍处理 */
void     Key_Detect_Scan(void);

/* 主循环取事件: 无事件返回 KEY_EVT_NONE, 取出后事件即被移除 */
KeyEvt_t Key_GetEvent(void);

#endif
