/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g0xx_it.h"
#include "timer.h"
#include "GlobalVar.h"
#include "SM16208.h"
#include "audio.h"
#include "GPIO.h"


/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

void TIM16_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&TIM16_Handler, TIM_FLAG_UPDATE) != RESET)
    {
        __HAL_TIM_CLEAR_FLAG(&TIM16_Handler, TIM_FLAG_UPDATE);

        if (TimingDelay > 0x00)
        {
            TimingDelay--;
        }

        process_key_events();
    }
}

void TIM17_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&TIM17_Handler, TIM_FLAG_UPDATE) != RESET)
    {
        __HAL_TIM_CLEAR_FLAG(&TIM17_Handler, TIM_FLAG_UPDATE);

        debugData2++;

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

        Set_Speaker_Duty(pwm_val, 255-pwm_val);
    }
}

