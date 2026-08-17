/*!
 * @file        apm32e030_int.c
 *
 * @brief       Main Interrupt Service Routines
 *
 * @version     V1.0.2
 *
 * @date        2025-05-15
 *
 * @attention
 *
 *  Copyright (C) 2024-2025 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32e030_int.h"
#include "main.h"
#include "apm32e030_tmr.h"
#include "GlobalVar.h"
#include "SM16208.h"
#include "audio.h"

/*!
 * @brief       This function handles NMI exception
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void NMI_Handler(void)
{
}

/*!
 * @brief       This function handles Hard Fault exception
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void HardFault_Handler(void)
{
}

/*!
 * @brief       This function handles SVCall exception
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SVC_Handler(void)
{
}

/*!
 * @brief       This function handles PendSV_Handler exception
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void PendSV_Handler(void)
{
}

/*!
 * @brief       This function handles SysTick exception
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void SysTick_Handler(void)
{
}

void TMR6_IRQHandler(void)
{
    if (TMR_ReadIntFlag(TMR6, TMR_INT_FLAG_UPDATE) == SET)
    {
        /* The interrupt flag bit must be cleared first. */
        TMR_ClearIntFlag(TMR6, TMR_INT_FLAG_UPDATE);

        if (TimingDelay > 0x00)
        {
            TimingDelay--;
        }

        process_key_events();
    }
}

void TMR17_IRQHandler(void)
{
    if (TMR_ReadIntFlag(TMR17, TMR_INT_FLAG_UPDATE) == SET)
    {
        /* The interrupt flag bit must be cleared first. */
        TMR_ClearIntFlag(TMR17, TMR_INT_FLAG_UPDATE);

        if (!playing) return;
    
        if (adpcm_byte_pos >= AUDIO_ADPCM_SIZE) {
            // 播放结束, 静音
            playing = 0;
            Audio_Sop();
            return;
        }
        
        // --- 取一个 nibble ---
        uint8_t byte_val = audio_adpcm_data[adpcm_byte_pos];
        uint8_t nibble;
        
        if (use_high_nibble == 0) {
            nibble = byte_val & 0x0F;        // 先取低4bit
            use_high_nibble = 1;
        } else {
            nibble = (byte_val >> 4) & 0x0F; // 再取高4bit
            use_high_nibble = 0;
            adpcm_byte_pos++;
        }
        
        // --- ADPCM 解码 ---
        int16_t sample = ADPCM_Decode(nibble);
        
        // --- 音量增益 ---
        int32_t amplified = (int32_t)sample * AUDIO_VOLUME_PERCENT / 100;
        if (amplified >  32767) amplified =  32767;  // 防削顶
        if (amplified < -32768) amplified = -32768;
        sample = (int16_t)amplified;
        
        // --- 映射到 PWM (8bit: 0~255) ---
        // CH2(HIGH极性) 和 CH3(LOW极性) 为差分输出, 需要相同 duty 才能产生差分电压:
        // V_diff = (pwm_val - (256-pwm_val))/256 * Vcc = (2*pwm_val-256)/256 * Vcc
        uint8_t pwm_val = (uint8_t)((sample + 32768) >> 8);

        Set_Speaker_Duty(pwm_val, pwm_val);
    }    
}
