#ifndef BOOT_ANIM_H_
#define BOOT_ANIM_H_

#include "stm32g0xx.h"

/* 播放开机动画: 亮带从左到右扫过并拖着渐隐的尾巴(阻塞, 约 1.2s) */
void Boot_Animation(void);

#endif
