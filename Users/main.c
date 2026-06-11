/**
 ******************************************************************************
 * @file    GPIO_Toggle\main.c
 * @author  MCD Application Team
 * @version V2.0.4
 * @date    26-April-2018
 * @brief   This file contains the main function for GPIO Toggle example.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "TM1650.h"
#include "timer.h"
#include "GPIO.h"
#include "stm8s_clk.h"
#include "GlobalVar.h"
#include "SM16208.h"

#define VERSION "Ver1.0"

void WorkProc(u8 state)
{
    u32 time = 0;
    switch (state)
    {
    case 1:
        PUMP_ON();  
        RELAY_ON();
        FAN_ON();
        //while(FORCE_STATUS()){} //等待负压开关动作
        delay_ms(15000);
        UV_LED_ON();
        
        while(time < workTimeSetting)
        {
            delay_ms(1000);//延时1秒
            time++;
            TM1650_Show_Number(workTimeSetting-time);
            if(time == workTimeSetting-3)
            {
                PUMP_OFF();
            } 
            else if(time == workTimeSetting-1)
                BEEP_ON();
        }
        PUMP_OFF();
        UV_LED_OFF();
        RELAY_OFF();
        BEEP_OFF();
        FAN_OFF();
        break;
    case 6:
        break;
    default:
        break;
    }
    
}

//u16 image_arr[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
u16 image_arr[8] = { 0x00, 0x0E, 0x06, 0x02, 0x60, 0x70, 0x20, 0x00 };

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
 void main(void)
{
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);//16M主频
    CLK_HSICmd(ENABLE);

    TIM4_Config();
    delay_ms(100);
    
    disableInterrupts();
    //MY_GPIO_Init();
    //exit_init();
    SM16208_Init();
    enableInterrupts();
    
    //TIM2_Config();
    
    // u16 temp = ReadTimeSetting();
    // if(temp < 1000)
    //     workTimeSetting = temp;
    // TM1650_Show_Number(workTimeSetting);

    display_matrix(image_arr);

    while (1)
    {
        // KeyProcess();
        // if(work_event)
        // {
        //     work_event = 0;
        //     u8 state = keyState;
        //     keyState = 0;
        //     WorkProc(state);
        // }

        display_matrix(image_arr);

        if(debugData1)
        {
            debugData1 = 0;
            display_matrix(image_arr);
        }
        // BEEP_ON();
        // RELAY_ON();
        // delay_ms(2000);
        // BEEP_OFF();
        // RELAY_OFF();
        // delay_ms(2000);
    }
}

void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}


/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
