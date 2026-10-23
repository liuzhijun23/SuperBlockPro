/*
 * boot_anim.c - 开机动画: 潮水式从左到右扫过并渐隐
 *
 * 原理: SM16208 只有开/关两态(无每点亮度寄存器), 所以用"时间分片 PWM"
 *       模拟灰度: 把一帧切成 LEVELS 个子帧, 亮度等级 L 的点在前 L 个子帧点亮。
 *
 * 方向: 实测 bit0 = 最左列(bit7 = 最右列), 所以用 "1u << c" 让
 *       c=0(最左列)先点亮, 实现从左到右扫过。
 */
#include "boot_anim.h"
#include "SM16208.h"
#include <string.h>

/* ==================== 可调参数 ==================== */
#define LEVELS      16      /* 亮度级数(2^n 更顺, 这里 16 级渐变更细腻) */
#define ROW_ON_US   120     /* 每个子帧里每行的点亮时间(us), 决定整体亮度 */
#define TAIL_LEN    6       /* 波前3列全亮 + 渐隐3列 = 6 列宽 */

/* 距波峰 0~5 列的亮度:
 *   0/1/2 三列全亮(亮带), 3/4 两列快速掉落, 5 全灭 -> 消退干脆不拖沓 */
static const uint8_t g_trail[TAIL_LEN] = { 15, 15, 15, 5, 1, 0 };

/* ==================== 微秒延时(SysTick 计数, M0+ 无 DWT) ====================
 * SysTick 已在 HAL_Init 里按 1ms 配置, VAL 每个内核时钟递减一次,
 * 直接读 VAL 差值做微秒级计时(需处理 1ms 到点重载的回绕) */
static void delay_us(uint32_t us)
{
    uint32_t ticks  = us * (SystemCoreClock / 1000000u);
    uint32_t prev   = SysTick->VAL;
    uint32_t waited = 0;

    while (waited < ticks)
    {
        uint32_t cur = SysTick->VAL;

        if (cur < prev)
        {
            waited += (prev - cur);                          /* 正常向下计数 */
        }
        else if (cur > prev)
        {
            waited += (prev + SysTick->LOAD + 1u - cur);     /* 计数到 0 后回绕重载 */
        }
        prev = cur;
    }
}

/* ==================== 底层: 送一行并点亮 ====================
 * 时序与 display_matrix() 完全一致: 移16位 -> 锁存 -> 消影 -> 选行 -> 开显示
 * 区别仅在于点亮时间用可调的 us 而不是固定 1ms */
static void sm16208_send_row(uint8_t row, uint8_t pattern, uint32_t on_us)
{
    uint16_t send_data = (uint16_t)pattern << 6;

    for (int i = 0; i < 16; i++)
    {
        if (send_data & 0x8000)
            HAL_GPIO_WritePin(SDI_GPIO, SDI_PIN, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(SDI_GPIO, SDI_PIN, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SCK_GPIO, SCK_PIN, GPIO_PIN_RESET);
        send_data <<= 1;
    }

    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LE_GPIO, LE_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_SET);   /* 消影 */

    HAL_GPIO_WritePin(A2_GPIO, A2_PIN, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A1_GPIO, A1_PIN, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(A0_GPIO, A0_PIN, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(OE_GPIO, OE_PIN, GPIO_PIN_RESET); /* 开显示 */

    if (on_us) delay_us(on_us);
}

/* ==================== 渲染一帧亮度图(时间分片 PWM) ====================
 * b[8][8]: 每点亮度 0~LEVELS-1 */
static void render_brightness(const uint8_t b[8][8])
{
    uint8_t s, r, c;

    for (s = 0; s < LEVELS; s++)          /* LEVELS 个子帧 */
    {
        for (r = 0; r < 8; r++)           /* 8 行(正常逐行扫描, A0 会持续翻转, 不触发 SM5166 保护) */
        {
            uint8_t pattern = 0;
            for (c = 0; c < 8; c++)
            {
                if (b[r][c] > s)
                    pattern |= (uint8_t)(1u << c);   /* bit0=最左列 */
            }
            sm16208_send_row(r, pattern, ROW_ON_US);
        }
    }
}

/* ==================== 生成一帧潮水波形 ====================
 * crest: 波峰所在的列(浮点, 可为负或>7, 表示在屏外) */
static void wave_frame(uint8_t b[8][8], float crest)
{
    uint8_t r, c;

    for (r = 0; r < 8; r++)
    {
        for (c = 0; c < 8; c++)
        {
            int d = (int)(crest - (float)c);   /* 该列落后波峰多少列 */
            if (d >= 0 && d < TAIL_LEN)
                b[r][c] = g_trail[d];
            else
                b[r][c] = 0;
        }
    }
}

/* ==================== 开机动画入口 ==================== */
void Boot_Animation(void)
{
    uint8_t b[8][8];
    float crest;

    /* 波峰从屏外左侧扫到屏外右侧; 步长决定动画时长与平滑度 */
    for (crest = -3.0f; crest <= 11.0f; crest += 0.10f)
    {
        wave_frame(b, crest);
        render_brightness(b);
    }

    /* 收尾: 全灭, 交还显示给主循环 */
    memset(b, 0, sizeof(b));
    render_brightness(b);
}
