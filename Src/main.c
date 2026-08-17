/*!
 * @file        main.c
 *
 * @brief       Main program body
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
#include "stdio.h"
#include "GlobalVar.h"

/** @addtogroup Examples
  @{
  */

/** @addtogroup GPIO_Toggle
  @{
  */

/** @defgroup GPIO_Toggle_Macros Macros
  @{
  */

/**@} end of group GPIO_Toggle_Macros */

/** @defgroup GPIO_Toggle_Enumerations Enumerations
  @{
  */

/**@} end of group GPIO_Toggle_Enumerations */

/** @defgroup GPIO_Toggle_Structures Structures
  @{
  */

/**@} end of group GPIO_Toggle_Structures */

/** @defgroup GPIO_Toggle_Variables Variables
  @{
  */

/**@} end of group GPIO_Toggle_Variables */

/** @defgroup GPIO_Toggle_Functions Functions
  @{
  */

/* Delay */
void Delay(void);

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
int main(void)
{
    EnableAllGpio();

    TIM6_Config();//period timer
    TIM17_Config();//8kHz timer
    delay_ms(100);

    SM16208_Init();
    SpeakerInit();

    while (1)
    {
        if(debugData1)
        {
            Audio_Start();
           
            debugData1 = 0;
        }

        //display_matrix(image_arr[1]);
        //display_matrix(key_filter);
    }
}

/*!
 * @brief       Delay
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
void Delay(void)
{
    volatile uint32_t delay = 0xffff5;

    while (delay--);
}

/**@} end of group GPIO_Toggle_Functions */
/**@} end of group GPIO_Toggle */
/**@} end of group Examples */
