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
#include "GPIO.h"
#include "key_detect.h"
#include "boot_anim.h"

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
        ledColor = RED;
        display_matrix(level_arr[curr_level]);
        break;
    case SHOW_PASS:
        display_matrix(level_arr[curr_level]);
        show_cnt++;
        if(show_cnt > 100)
        {
            show_flag = SHOW_WAIT;
            show_cnt = 0;
            ledColor = RED;
        }
        else
        {
            if(show_cnt%40 == 10)
                ledColor = RED;
            else if(show_cnt%40 == 20)
                ledColor = BLUE;
            else if(show_cnt%40 == 30)
                ledColor = YELLOR;
            else if(show_cnt % 40 == 0)
                ledColor = GREEN;
        }
        break;
    case SHOW_WAIT:
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
            WriteLevelSetting(curr_level);
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
    KeyInit();
    Key_Detect_Init();

    disp_ptr = image_arr[2];

    Boot_Animation();
    Display_ScanStart();

    levelSaved = ReadLevelSetting();
    curr_level = levelSaved;

    while (1)
    {
        if(play_audio_flag)
        {
            Audio_Start();
            play_audio_flag = 0;
        }

        if(debugData1 == 1)
        {
            debugData1 = 0;
            WriteLevelSetting(debugData2);
        }
        else if(debugData1 == 2)
        {
            debugData1 = 0;
            Boot_Animation();
        }
        else if(debugData1 == 3)
        {
            debugData1 = 0;
            ShowLevel(curr_level);
        }

        powerKeyState = POWER_KEY_STATUS();
        leftKeyState = LEFT_KEY_STATUS();
        rightKeyState = RIGHT_KEY_STATUS();

        /* 按键事件处理: 从事件队列取事件并分�?*/
        {
            KeyEvt_t ev = Key_GetEvent();
            switch (ev)
            {
            case KEY_EVT_POWER_LONG:       /* 1  电源键长�?*/  
                debugData2 = 1;     
                break;
            case KEY_EVT_LEFT_SHORT:       /* 2  左键短按 */    
                debugData2 = 2;      
                break;
            case KEY_EVT_RIGHT_SHORT:      /* 3  右键短按 */   
                debugData2 = 3;      
                break;
            case KEY_EVT_LEFT_LONG:        /* 4  左键长按 */   
                debugData2 = 4;      
                break;
            case KEY_EVT_RIGHT_LONG:       /* 5  右键长按 */   
                debugData2 = 5;          
                break;
            case KEY_EVT_LR_LONG:          /* 6  左右键同时长�?*/  
                debugData2 = 6;    
                break;
            case KEY_EVT_POWER_LEFT_LONG:  /* 7  电源+左键长按 */ 
                debugData2 = 7;    
                break;
            case KEY_EVT_POWER_RIGHT_LONG: /* 8  电源+右键长按 */    
                debugData2 = 8;    
                break;
            case KEY_EVT_POWER_DOUBLE:     /* 9  电源键快�?�?*/    
                debugData2 = 9;    
                break;
            case KEY_EVT_POWER_SHORT:      /* 10 电源键短�?*/ 
                debugData2 = 10;          
                break;
            case KEY_EVT_LR_SHORT:         /* 11 左右键同时短�?*/  
                debugData2 = 11;    
                break;
            default: break;
            }
        }
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


