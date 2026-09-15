/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "GlobalVar.h"
#include "audio.h"
#include "SM16208.h"

void SystemClock_Config(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
u32 test_count = 0;

void ShowLedProc(void)
{
    static u16 show_cnt = 0;
    switch (show_flag)
    {
    case SHOW_LEVEL:
        display_matrix(level_arr[curr_level]);
        if(pass_mission_flag)
        {
            if(CompareArr(key_filter,image_arr[0],8))
            {
                pass_mission_flag = 0;
                show_flag = SHOW_2;
                show_cnt = 0;
            }
        }
        break;
    case SHOW_2:
        display_matrix(image_arr[IMAG_INDEX_2]);
        if(show_cnt++ > 200)
        {
            show_cnt = 0;
            show_flag = SHOW_0;
        }
        break;
    case SHOW_0:
        display_matrix(image_arr[IMAG_INDEX_0]);
        if(show_cnt++ > 200)
        {
            show_cnt = 0;
            curr_level++;
            show_flag = SHOW_LEVEL;
        }
        break;
    default:
        break;
    }
}

int main(void)
{
    HAL_Init();
   // HAL_SuspendTick(); 
    SystemClock_Config();
    EnableAllGpio();

    TIM16_Config();//period timer
    TIM17_Config();//8kHz timer
    delay_ms(100);

    SM16208_Init();
    SpeakerInit();

    while (1)
    {
        if(play_audio_flag)
        {
            Audio_Start();
            play_audio_flag = 0;
        }

        ShowLedProc();

    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 8;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}


void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}


