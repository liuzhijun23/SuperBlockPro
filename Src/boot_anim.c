/*
 * Column wave matched to ledwave.mp4: a broad left-to-right wash,
 * followed by a long, staggered fade. bit0 is the physical left column.
 * Animation time is independent of the multiplex refresh time.
 */
#include "boot_anim.h"
#include "SM16208.h"

#define COLUMN_DELAY_MS  105u
#define RISE_MS           90u
#define HOLD_MS          180u
#define FADE_MS         1000u
#define ANIMATION_MS    (7u * COLUMN_DELAY_MS + RISE_MS + HOLD_MS + FADE_MS)
#define PWM_BITS           5u
#define PWM_UNIT_US       24u

static void delay_us(uint32_t us)
{
    uint32_t ticks = us * (SystemCoreClock / 1000000u);
    uint32_t prev = SysTick->VAL;
    uint32_t waited = 0;
    while (waited < ticks)
    {
        uint32_t cur = SysTick->VAL;
        if (cur < prev)
            waited += prev - cur;
        else if (cur > prev)
            waited += prev + SysTick->LOAD + 1u - cur;
        prev = cur;
    }
}

static void sm16208_send_row(uint8_t row, uint8_t pattern, uint32_t on_us)
{
    uint16_t data = (uint16_t)pattern << 6;
    int i;

    /* Keep the previous row dark throughout shifting and latching. */
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_SET);
    for (i = 0; i < 16; ++i)
    {
        HAL_GPIO_WritePin(SDI_GPIO, SDI_PIN,
                          (data & 0x8000u) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_RESET);
        data <<= 1;
    }
    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A2_GPIO, A2_PIN, (row & 4u) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A1_GPIO, A1_PIN, (row & 2u) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A0_GPIO, A0_PIN, (row & 1u) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_RESET);
    delay_us(on_us);
    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_SET);
}

/* 32 duty levels, using five weighted bit planes instead of 32 scans.
 * Nominal light time per refresh: 8 * 31 * 24us = 5.952ms.
 * Every plane scans all rows, preserving the row driver's A0 activity.
 */
static void render_columns(const uint8_t brightness[8])
{
    uint8_t plane, col, row;
    for (plane = 0; plane < PWM_BITS; ++plane)
    {
        uint8_t pattern = 0;
        for (col = 0; col < 8; ++col)
            if (brightness[col] & (1u << plane))
                pattern |= (uint8_t)(1u << col);
        for (row = 0; row < 8; ++row)
            sm16208_send_row(row, pattern, PWM_UNIT_US << plane);
    }
}

static uint8_t column_brightness(uint32_t elapsed, uint8_t col)
{
    uint32_t start = (uint32_t)col * COLUMN_DELAY_MS;
    uint32_t age, envelope;
    if (elapsed <= start)
        return 0;
    age = elapsed - start;
    if (age < RISE_MS)
        envelope = age * 255u / RISE_MS;
    else if (age < RISE_MS + HOLD_MS)
        envelope = 255u;
    else
    {
        age -= RISE_MS + HOLD_MS;
        if (age >= FADE_MS)
            return 0;
        envelope = (FADE_MS - age) * 255u / FADE_MS;
    }
    /* Approximate perceptual ramp with gamma 2; no float on Cortex-M0+. */
    return (uint8_t)((envelope * envelope * 31u + 32512u) / 65025u);
}

void Boot_Animation(void)
{
    uint8_t brightness[8];
    uint8_t col;

    Display_ScanStop();   /* 动画直接驱动显示引脚，先暂停 TIM16 中断扫描 */

    uint32_t start = HAL_GetTick();
    uint32_t elapsed;
    for (;;)
    {
        elapsed = HAL_GetTick() - start;
        if (elapsed >= ANIMATION_MS)
            break;
        for (col = 0; col < 8; ++col)
            brightness[col] = column_brightness(elapsed, col);
        render_columns(brightness);
    }
    /* Clear the latch as well as disabling output before returning. */
    sm16208_send_row(0, 0, PWM_UNIT_US);
    Display_ScanStart();  /* 动画结束，恢复中断逐行扫描 */
}
