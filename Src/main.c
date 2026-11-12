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
#include "rotate_anim.h"
#include "timer.h"
#include <string.h>

void SystemClock_Config(void);

/* Game transitions run in the main loop; TIM16 only scans the board. */
typedef enum
{
    GAME_SHOW_NUMBER,
    GAME_PLAY,
    GAME_CELEBRATE,
    GAME_WAIT_CLEAR,
    GAME_COMPLETE
} GameState;

#define NUMBER_MS         1800u
#define PASS_MS           2600u
#define PASS_BLINK_MS     1200u
#define BOARD_BLINK_MS     180u
#define COLOR_STEP_MS      150u

static GameState game_state;
static u32 state_started;
static u16 digit_divisor;

/* Debug-only overlay: preserve both game state and its elapsed time. */
static u8 rotate_active;
static u32 rotate_started;
static const u8 *rotate_saved_frame;
static u8 rotate_saved_color;

static void Rotate_Start(u32 now)
{
    if (!rotate_active)
    {
        rotate_saved_frame = disp_ptr;
        rotate_saved_color = ledColor;
        rotate_started = now;
        rotate_active = 1u;
    }
}

static void Rotate_Update(u32 now)
{
    static u8 frames[2][8];
    static u8 next_frame;
    u32 elapsed = now - rotate_started;

    if (Rotate_Render(elapsed, frames[next_frame]))
    {
        disp_ptr = rotate_saved_frame;
        ledColor = rotate_saved_color;
        state_started += elapsed;
        rotate_active = 0u;
    }
    else
    {
        /* Publish all eight rows atomically; never edit the displayed buffer. */
        disp_ptr = frames[next_frame];
        next_frame ^= 1u;
    }
}

static void Game_Enter(GameState state, u32 now)
{
    game_state = state;
    state_started = now;
    switch (state)
    {
    case GAME_SHOW_NUMBER:
    {
        u16 number = curr_level + 1u;
        digit_divisor = 1u;
        while (number / digit_divisor >= 10u)
            digit_divisor *= 10u;
        disp_ptr = image_arr[IMAG_INDEX_0 + number / digit_divisor];
        ledColor = RED;
        break;
    }
    case GAME_PLAY:
    case GAME_CELEBRATE:
    case GAME_WAIT_CLEAR:
        disp_ptr = level_arr[curr_level];
        ledColor = RED;
        break;
    case GAME_COMPLETE:
        disp_ptr = image_arr[IMAG_INDEX_DARK];
        ledColor = NONE;
        break;
    }
}

static void Game_Update(u32 now)
{
    u32 elapsed = now - state_started;
    u8 pressed[8];
    static const u8 colors[] = { RED, GREEN, YELLOR, BLUE };

    switch (game_state)
    {
    case GAME_SHOW_NUMBER:
        if (elapsed >= NUMBER_MS)
        {
            digit_divisor /= 10u;
            if (digit_divisor == 0u)
                Game_Enter(GAME_PLAY, now);
            else
            {
                u16 digit = ((curr_level + 1u) / digit_divisor) % 10u;
                disp_ptr = image_arr[IMAG_INDEX_0 + digit];
                state_started = now;
            }
        }
        break;
    case GAME_PLAY:
        if (Board_ReadPressed(pressed) &&
            memcmp(pressed, level_arr[curr_level], sizeof(pressed)) == 0)
        {
            Game_Enter(GAME_CELEBRATE, now);
            Audio_Start();
        }
        break;
    case GAME_CELEBRATE:
        if (elapsed >= PASS_MS)
            Game_Enter(GAME_WAIT_CLEAR, now);
        else
        {
            if (elapsed < PASS_BLINK_MS && (elapsed / BOARD_BLINK_MS) % 2u)
                disp_ptr = image_arr[IMAG_INDEX_DARK];
            else
                disp_ptr = level_arr[curr_level];
            ledColor = colors[(elapsed / COLOR_STEP_MS) % sizeof(colors)];
        }
        break;
    case GAME_WAIT_CLEAR:
        if (Board_ReadPressed(pressed) &&
            memcmp(pressed, image_arr[IMAG_INDEX_DARK], sizeof(pressed)) == 0)
        {
            if (curr_level + 1u < level_count)
            {
                ++curr_level;
                WriteLevelSetting(curr_level);
                Game_Enter(GAME_SHOW_NUMBER, HAL_GetTick());
            }
            else
                Game_Enter(GAME_COMPLETE, now);
        }
        break;
    case GAME_COMPLETE:
        break;
    }
}

static void Game_HandleKey(KeyEvt_t ev, u32 now)
{
    if (ev != KEY_EVT_NONE)
        debugData2 = (u32)ev;

    /* Keep the automatic clear-and-advance flow intact during a celebration. */
    if (game_state == GAME_CELEBRATE || game_state == GAME_WAIT_CLEAR)
        return;

    if (ev == KEY_EVT_LEFT_SHORT && curr_level > 0u)
    {
        --curr_level;
        Game_Enter(GAME_SHOW_NUMBER, now);
    }
    else if (ev == KEY_EVT_RIGHT_SHORT && curr_level + 1u < level_count)
    {
        ++curr_level;
        Game_Enter(GAME_SHOW_NUMBER, now);
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    EnableAllGpio();

    TIM16_Config();
    TIM17_Config();
    delay_ms(100);

    SM16208_Init();
    SpeakerInit();
    KeyInit();
    Key_Detect_Init();

    disp_ptr = image_arr[IMAG_INDEX_DARK];
    Boot_Animation();

    levelSaved = ReadLevelSetting();
    curr_level = (levelSaved < level_count) ? levelSaved : 0u;
    Game_Enter(GAME_SHOW_NUMBER, HAL_GetTick());
    Audio_Start();

    while (1)
    {
        if (debugData1 == 4)
        {
            debugData1 = 0;
            Rotate_Start(HAL_GetTick());
        }

        if (rotate_active)
        {
            /* Discard key events during the overlay rather than replaying later. */
            (void)Key_GetEvent();
            Rotate_Update(HAL_GetTick());
            continue;
        }

        if (debugData1 == 1)
        {
            debugData1 = 0;
            if (debugData2 < level_count)
                WriteLevelSetting((u16)debugData2);
        }
        else if (debugData1 == 2)
        {
            debugData1 = 0;
            Boot_Animation();
            Game_Enter(GAME_SHOW_NUMBER, HAL_GetTick());
        }
        else if (debugData1 == 3)
        {
            debugData1 = 0;
            Game_Enter(GAME_SHOW_NUMBER, HAL_GetTick());
        }

        powerKeyState = POWER_KEY_STATUS();
        leftKeyState = LEFT_KEY_STATUS();
        rightKeyState = RIGHT_KEY_STATUS();

        Game_HandleKey(Key_GetEvent(), HAL_GetTick());
        Game_Update(HAL_GetTick());
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


