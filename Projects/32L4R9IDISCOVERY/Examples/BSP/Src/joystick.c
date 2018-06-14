/**
  ******************************************************************************
  * @file    BSP/Src/joystick.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the joystick feature in the 
  *          STM32L4R9I-EVAL driver
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

extern __IO JOYState_TypeDef JoyState;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Joystick_SetHint(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Joystick demo
  * @param  None
  * @retval None
  */
void Joystick_demo (void)
{ 
  static uint16_t xPtr = 50;
  static uint16_t yPtr = 150;
  static uint16_t old_xPtr = 50;
  static uint16_t old_yPtr = 150;  

  Joystick_SetHint();
  
  while(BSP_LCD_IsFrameBufferAvailable() != LCD_OK);
  /* Initial cursor display */
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    
  BSP_LCD_DisplayChar(xPtr, yPtr, 'X');
  BSP_LCD_Refresh();
  
  while (1)
  {
    /* Check MFX interrupt occurred */    
    if(MfxItOccurred == SET)
    {
      Mfx_Event();

      /* Initial Joystick state set following MFX interrupt */
      if(JoyState != JOY_NONE)
      {
        /* Wait 1 ms to manage debounce */
        HAL_Delay(1);

        switch(JoyState)
        {
        case JOY_UP:
          if(yPtr > 150)
          {
            yPtr--;
          }
          break;     
        case JOY_DOWN:
          if(yPtr < 256)
          {
            yPtr++;
          }
          break;          
        case JOY_LEFT:
          if(xPtr > 50)
          {
            xPtr--;
          }
          break;         
        case JOY_RIGHT:
          if(xPtr < 323)
          {
            xPtr++;
          }
          break;                 
        default:
          break;           
        }
    
        while(BSP_LCD_IsFrameBufferAvailable() != LCD_OK);
        if(JoyState == JOY_NONE)
        {
          BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
          BSP_LCD_DisplayChar(xPtr, yPtr, 'X');   
        }
        else
        {
          BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
          BSP_LCD_DisplayChar(old_xPtr, old_yPtr, 'X');
          BSP_LCD_SetTextColor(LCD_COLOR_BLUE); 
          BSP_LCD_DisplayChar(xPtr, yPtr, 'X');
      
          old_xPtr = xPtr;
          old_yPtr = yPtr;
        }
        BSP_LCD_Refresh();        
      }
    }
    
    if(JoyState == JOY_SEL)
    {
      return;
    }
    HAL_Delay(5);
  }
}


/**
  * @brief  Display joystick demo hint
  * @param  None
  * @retval None
  */
static void Joystick_SetHint(void)
{
  while(BSP_LCD_IsFrameBufferAvailable() != LCD_OK);
  /* Clear the LCD */ 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set LCD Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 130);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)"Joystick", CENTER_MODE);
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"Use the joystick to move", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 75, (uint8_t *)"the pointer in the rectangle", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 90, (uint8_t *)"Press SEL to go to next menu", CENTER_MODE);
  
  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_DrawRect(40, 140, BSP_LCD_GetXSize() - 80, BSP_LCD_GetYSize()- 240);
  BSP_LCD_DrawRect(41, 141, BSP_LCD_GetXSize() - 82, BSP_LCD_GetYSize()- 242);
  BSP_LCD_Refresh();
}
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
