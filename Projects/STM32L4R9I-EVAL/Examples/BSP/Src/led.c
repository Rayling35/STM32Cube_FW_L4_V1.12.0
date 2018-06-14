/**
  ******************************************************************************
  * @file    led.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the led display feature in the 
  *          STM32L4R9I_EVAL driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Led_SetHint(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Led demo
  * @param  None
  * @retval None
  */
void Led_demo(void)
{
  uint32_t index = 0;
  
  Led_SetHint();
  
  /* Init and turn on LED 1 to 4  */
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"Initialize then turn on", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 135, (uint8_t *)"each leds after 500 ms", CENTER_MODE);

  HAL_Delay(500);
  BSP_LED_On(LED1);
  
  HAL_Delay(500);
  BSP_LED_On(LED2);
  
  HAL_Delay(500);
  BSP_LED_On(LED3);
  
  HAL_Delay(500);
  BSP_LED_On(LED4);
  
  /* Keep the LEDs on for two seconds */
  HAL_Delay(2000);
  
  /* Turn off the LEDs */ 
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"Turn off each leds after 500 ms", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 135, (uint8_t *)"                      ", CENTER_MODE);
  HAL_Delay(500);
  BSP_LED_Off(LED1);
  HAL_Delay(500);
  BSP_LED_Off(LED2);
  HAL_Delay(500);
  BSP_LED_Off(LED3);
  HAL_Delay(500);
  BSP_LED_Off(LED4);
  
  HAL_Delay(2000);
  
  /* After two seconds, turn on LED2 and LED4 */
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"         Turn on led 2         ", CENTER_MODE);
  BSP_LED_On(LED2);
  HAL_Delay(500);
  
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"         Turn on led 4         ", CENTER_MODE);
  BSP_LED_On(LED4);
  HAL_Delay(500);
  
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"         Turn on led 1         ", CENTER_MODE);
  BSP_LED_On(LED1);
  HAL_Delay(500);
  
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"         Turn on led 3         ", CENTER_MODE);
  BSP_LED_On(LED3);
  HAL_Delay(500);
  
  /* For about five seconds, toggle all the LEDs */
  BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"      Toggle all on leds       ", CENTER_MODE);
  while (index < 25)
  {
    HAL_Delay(200);
    index++;
    BSP_LED_Toggle(LED1);
    BSP_LED_Toggle(LED2);
    BSP_LED_Toggle(LED3);
    BSP_LED_Toggle(LED4);
  }
}

/**
  * @brief  Display Led demo hint
  * @param  None
  * @retval None
  */
static void Led_SetHint(void)
{
  /* Clear the LCD */ 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set Led Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"Led", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"initialize and turn on, turn off", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"and toggle the leds", CENTER_MODE);
  
  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize()- 100);
  BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize()- 102);
}
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
