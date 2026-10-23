/*
 * key_detect.c - 电源/左/右 三键事件检测模块
 *
 * 硬件前提: 三个独立 GPIO 按键, 下拉输入, 按下 = 高电平
 *   POWER_KEY = PB5, LEFT_KEY = PB4, RIGHT_KEY = PB3 (见 GPIO.h)
 *
 * 使用方法:
 *   1. main 初始化时调用一次 Key_Detect_Init()
 *   2. 每 1ms 调用一次 Key_Detect_Scan()(推荐放在 TIM16 1ms 中断里)
 *   3. 主循环里用 Key_GetEvent() 取事件, 事件取出即移除
 *
 * 时序参数(都在下面"可调参数"里):
 *   - 消抖 30ms
 *   - 长按阈值 1000ms; 到达后再等 300ms 组合窗口才发事件,
 *     用于识别"第二只键也按住了"的组合长按 -> 长按事件总延迟约 1.3s
 *   - 电源短按必须等 400ms 确认不是双击后才发出(双击检测的代价)
 *   - 左/右短按必须等 250ms 归组窗口, 确认不是"左右同时短按"
 *
 * 语义约定:
 *   - 每次按压只产生一个事件; 被长按(组合)消费的键抬起时不再发短按
 *   - 长按在按住期间发出(不需要等到抬起); 短按在抬起后发出
 *   - 若一个键已超过长按阈值、但在组合窗口结束前抬起, 按单个长按立即结案
 *   - 三键同时长按需求未定义, 默认不产生事件(见 fire_long_group 的 default)
 */
#include "key_detect.h"
#include "GPIO.h"

/* ==================== 可调参数 ==================== */
#define KEY_TICK_MS         10u    /* 处理节拍(ms): Scan 每 1ms 调一次, 计满 10 处理一次 */
#define KEY_DEBOUNCE_TICKS  3u     /* 消抖拍数: 3 x 10ms = 30ms */
#define KEY_LONG_MS         1000u  /* 长按阈值 */
#define KEY_DOUBLE_MS       400u   /* 电源双击: 相邻两次释放的最大间隔 */
#define KEY_COMBO_LONG_MS   300u   /* 长按组合窗口: 等其它键也达到长按阈值的时间 */
#define KEY_SHORT_GROUP_MS  250u   /* 左右短按归组窗口 */
#define KEY_EVT_Q_SIZE      8u

/* 内部按键索引 */
#define KIDX_POWER   0
#define KIDX_LEFT    1
#define KIDX_RIGHT   2
#define KEY_NUM      3

typedef struct
{
    uint8_t  cand;      /* 候选电平 */
    uint8_t  cnt;       /* 消抖计数 */
    uint8_t  pressed;   /* 消抖后状态: 1=按下 */
    uint32_t hold_ms;   /* 本次按住持续时间 */
    uint8_t  consumed;  /* 已被长按(组合)消费, 抬起时不再产生短按 */
} Key_t;

static Key_t       m_key[KEY_NUM];
static uint16_t    m_div;             /* 1ms -> 10ms 分频计数 */

/* 长按组合评估 */
static uint16_t    m_grp_idle_ms;     /* 组合成员不再增加已持续的时间 */

/* 左右键短按归组 */
static uint8_t     m_short_pend;      /* bit: KIDX_LEFT / KIDX_RIGHT */
static uint16_t    m_short_pend_ms;

/* 电源单击/双击 */
static uint8_t     m_pwr_clicks;      /* 已释放的短按次数 */
static uint16_t    m_pwr_pend_ms;     /* 距最近一次短按释放的时间 */

/* 事件环形队列 */
static volatile KeyEvt_t m_q[KEY_EVT_Q_SIZE];
static volatile uint8_t  m_q_wr = 0;
static volatile uint8_t  m_q_rd = 0;

/* ---------------- 事件队列 ---------------- */
static void evt_push(KeyEvt_t e)
{
    uint8_t next = (uint8_t)((m_q_wr + 1u) % KEY_EVT_Q_SIZE);
    if (next != m_q_rd)               /* 队列满则丢弃本事件 */
    {
        m_q[m_q_wr] = e;
        m_q_wr = next;
    }
}

KeyEvt_t Key_GetEvent(void)
{
    KeyEvt_t e = KEY_EVT_NONE;
    __disable_irq();                  /* Scan 可能在中断里 push, 取的时候关一下 */
    if (m_q_rd != m_q_wr)
    {
        e = m_q[m_q_rd];
        m_q_rd = (uint8_t)((m_q_rd + 1u) % KEY_EVT_Q_SIZE);
    }
    __enable_irq();
    return e;
}

/* ---------------- 原始电平 ----------------
 * 返回 1 = 按下。当前配置为下拉输入、按下接高电平;
 * 若实际板子按下为低, 把 GPIO_PIN_SET 改成 GPIO_PIN_RESET 即可 */
static uint8_t key_raw(uint8_t k)
{
    switch (k)
    {
    case KIDX_POWER: return (POWER_KEY_STATUS() == GPIO_PIN_SET) ? 1u : 0u;
    case KIDX_LEFT:  return (LEFT_KEY_STATUS()  == GPIO_PIN_SET) ? 1u : 0u;
    default:         return (RIGHT_KEY_STATUS() == GPIO_PIN_SET) ? 1u : 0u;
    }
}

/* 标记组合内的键已消费; 电源键参与长按会取消未决的单击/双击 */
static void mark_consumed(uint8_t grp)
{
    uint8_t k;
    for (k = 0; k < KEY_NUM; k++)
        if (grp & (1u << k)) m_key[k].consumed = 1;

    if (grp & (1u << KIDX_POWER))
    {
        m_pwr_clicks  = 0;
        m_pwr_pend_ms = 0;
    }
}

/* 按组合成员集合发对应的长按事件 */
static void fire_long_group(uint8_t grp)
{
    switch (grp)
    {
    case (1u << KIDX_POWER):                      evt_push(KEY_EVT_POWER_LONG);       break;
    case (1u << KIDX_LEFT):                       evt_push(KEY_EVT_LEFT_LONG);        break;
    case (1u << KIDX_RIGHT):                      evt_push(KEY_EVT_RIGHT_LONG);       break;
    case (1u << KIDX_LEFT)  | (1u << KIDX_RIGHT): evt_push(KEY_EVT_LR_LONG);          break;
    case (1u << KIDX_POWER) | (1u << KIDX_LEFT):  evt_push(KEY_EVT_POWER_LEFT_LONG);  break;
    case (1u << KIDX_POWER) | (1u << KIDX_RIGHT): evt_push(KEY_EVT_POWER_RIGHT_LONG); break;
    default: /* 三键同按: 需求未定义, 默认不发事件, 需要时在此添加 */              break;
    }
}

/* 某键超过长按阈值后、组合窗口结束前抬起: 立即按当前组合结案 */
static void finalize_long_now(uint8_t k)
{
    uint8_t grp = (uint8_t)(1u << k);
    uint8_t i;
    for (i = 0; i < KEY_NUM; i++)
    {
        if (i != k && m_key[i].pressed && !m_key[i].consumed &&
            m_key[i].hold_ms >= KEY_LONG_MS)
        {
            grp |= (uint8_t)(1u << i);
        }
    }
    fire_long_group(grp);
    mark_consumed(grp);
    m_grp_idle_ms = 0;
}

/* ---------------- 10ms 节拍处理 ---------------- */
static void key_tick(void)
{
    uint8_t k;
    uint8_t grp = 0;   /* 已达长按阈值且未消费的按下键 */
    uint8_t all = 0;   /* 所有按下且未消费的键 */

    /* ---------- 1. 消抖与按下/抬起沿 ---------- */
    for (k = 0; k < KEY_NUM; k++)
    {
        uint8_t raw = key_raw(k);
        Key_t  *p   = &m_key[k];
        uint8_t old = p->pressed;

        if (raw == p->cand)
        {
            if (p->cnt < KEY_DEBOUNCE_TICKS) p->cnt++;
        }
        else
        {
            p->cand = raw;
            p->cnt  = 1;
        }
        if (p->cnt >= KEY_DEBOUNCE_TICKS) p->pressed = p->cand;

        if (!old && p->pressed)             /* 按下沿 */
        {
            p->hold_ms  = 0;
            p->consumed = 0;
        }
        else if (p->pressed)                /* 按住计时 */
        {
            p->hold_ms += KEY_TICK_MS;
        }
        else if (old && !p->pressed)        /* 抬起沿 */
        {
            if (!p->consumed)
            {
                if (p->hold_ms >= KEY_LONG_MS)
                {
                    finalize_long_now(k);   /* 组合窗口内抬起: 立即结案 */
                }
                else if (k == KIDX_POWER)
                {
                    m_pwr_clicks++;         /* 电源短按: 进入双击判定 */
                    m_pwr_pend_ms = 0;
                }
                else
                {
                    m_short_pend |= (uint8_t)(1u << k);   /* 左/右短按: 进入归组判定 */
                }
            }
            p->hold_ms = 0;
        }
    }

    /* ---------- 2. 长按组合评估 ---------- */
    for (k = 0; k < KEY_NUM; k++)
    {
        if (m_key[k].pressed && !m_key[k].consumed && m_key[k].hold_ms >= KEY_LONG_MS)
            grp |= (uint8_t)(1u << k);
    }

    if (grp != 0)
    {
        for (k = 0; k < KEY_NUM; k++)
        {
            if (m_key[k].pressed && !m_key[k].consumed)
                all |= (uint8_t)(1u << k);
        }

        if (grp == all)
        {
            /* 所有按着的键都到了长按阈值, 再等一小会看是否有新键加入 */
            m_grp_idle_ms += KEY_TICK_MS;
            if (m_grp_idle_ms >= KEY_COMBO_LONG_MS)
            {
                fire_long_group(grp);
                mark_consumed(grp);
                m_grp_idle_ms = 0;
            }
        }
        else
        {
            /* 还有键没到阈值, 可能加入组合, 重新计时 */
            m_grp_idle_ms = 0;
        }
    }
    else
    {
        m_grp_idle_ms = 0;
    }

    /* ---------- 3. 左右键短按归组 ---------- */
    if (m_short_pend != 0)
    {
        m_short_pend_ms += KEY_TICK_MS;
        if (m_short_pend_ms >= KEY_SHORT_GROUP_MS)
        {
            uint8_t l = (m_short_pend & (1u << KIDX_LEFT))  != 0;
            uint8_t r = (m_short_pend & (1u << KIDX_RIGHT)) != 0;

            if (l && r) evt_push(KEY_EVT_LR_SHORT);
            else if (l) evt_push(KEY_EVT_LEFT_SHORT);
            else        evt_push(KEY_EVT_RIGHT_SHORT);

            m_short_pend    = 0;
            m_short_pend_ms = 0;
        }
    }
    else
    {
        m_short_pend_ms = 0;
    }

    /* ---------- 4. 电源单击/双击判定 ---------- */
    if (m_pwr_clicks != 0 && !m_key[KIDX_POWER].pressed)
    {
        m_pwr_pend_ms += KEY_TICK_MS;
        if (m_pwr_pend_ms >= KEY_DOUBLE_MS)
        {
            evt_push((m_pwr_clicks >= 2) ? KEY_EVT_POWER_DOUBLE : KEY_EVT_POWER_SHORT);
            m_pwr_clicks   = 0;
            m_pwr_pend_ms  = 0;
        }
    }
}

/* ---------------- 对外接口 ---------------- */
void Key_Detect_Init(void)
{
    uint8_t k;
    for (k = 0; k < KEY_NUM; k++)
    {
        m_key[k].cand     = 0;
        m_key[k].cnt      = 0;
        m_key[k].pressed  = 0;
        m_key[k].hold_ms  = 0;
        m_key[k].consumed = 0;
    }
    m_div           = 0;
    m_grp_idle_ms   = 0;
    m_short_pend    = 0;
    m_short_pend_ms = 0;
    m_pwr_clicks    = 0;
    m_pwr_pend_ms   = 0;
    m_q_wr          = 0;
    m_q_rd          = 0;
}

/* 每 1ms 调用一次(如 TIM16 1ms 中断), 内部 10 分频 */
void Key_Detect_Scan(void)
{
    if (++m_div >= KEY_TICK_MS)
    {
        m_div = 0;
        key_tick();
    }
}
