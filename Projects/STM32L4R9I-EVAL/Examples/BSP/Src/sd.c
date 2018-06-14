/**
  ******************************************************************************
  * @file    BSP/Src/sd.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the SD Driver
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
#define SD_CARD_PRESENCE_POLLING_MODE         0
#define SD_CARD_PRESENCE_INTERRUPT_MODE      1

#define SD_CARD_PRESENCE_VALIDATION_MODE      SD_CARD_PRESENCE_INTERRUPT_MODE       

#define BLOCK_START_ADDR         0     /* Block start address      */
#define NUM_OF_BLOCKS            5     /* Total number of blocks   */
#define BUFFER_WORDS_SIZE        ((BLOCKSIZE * NUM_OF_BLOCKS) >> 2) /* Total data size in bytes */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t aTxBuffer[BUFFER_WORDS_SIZE];
uint32_t aRxBuffer[BUFFER_WORDS_SIZE];
__IO uint32_t SDWriteStatus = 0, SDReadStatus = 0;

extern __IO FlagStatus  TamperItOccurred;

/* Private function prototypes -----------------------------------------------*/
static void SD_SetHint(void);
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);
static uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  SD Demo
  * @param  None
  * @retval None
  */
void SD_demo (void)
{
  uint8_t SD_state = MSD_OK;
  static uint8_t prev_status = 2;  /* Undefined state */

  SD_SetHint();

  BSP_LCD_SetTextColor(LCD_COLOR_RED);
  BSP_LCD_DisplayStringAt(20, BSP_LCD_GetYSize() - 30, (uint8_t *)"SD Not Connected", LEFT_MODE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  
  SD_state = BSP_SD_Init();

#if (SD_CARD_PRESENCE_VALIDATION_MODE == SD_CARD_PRESENCE_INTERRUPT_MODE)
  BSP_SD_ITConfig();
#endif
  
  if (SD_state != MSD_OK)
  {
    if(SD_state == MSD_ERROR_SD_NOT_PRESENT)
    {
      BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD shall be inserted before running test", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD Initialization : FAIL.", LEFT_MODE);
    }
    BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
  }
  else
  {
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD Initialization : OK.", LEFT_MODE);

    BSP_LCD_DisplayStringAt(20, BSP_LCD_GetYSize() - 30,   (uint8_t *)"SD Connected    ", LEFT_MODE);
    prev_status = SD_PRESENT;
    
    SD_state = BSP_SD_Erase(BLOCK_START_ADDR, (BLOCKSIZE * NUM_OF_BLOCKS));
      /* Wait until SD card is ready to use for new operation */
      while(BSP_SD_GetCardState() != SD_TRANSFER_OK)
      {
      }
    if (SD_state != MSD_OK)
    {
      BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"SD ERASE : FAILED.", LEFT_MODE);
      BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
    }
    else
    {
      BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"SD ERASE : OK.", LEFT_MODE);

      /* Fill the buffer to write */
      Fill_Buffer(aTxBuffer, BUFFER_WORDS_SIZE, 0x22FF);
      SD_state = BSP_SD_WriteBlocks_DMA(aTxBuffer, BLOCK_START_ADDR, NUM_OF_BLOCKS);
        /* Wait for the write process is completed */
        while((SDWriteStatus == 0))
        {
        }
        SDWriteStatus = 0;
        
        /* Wait until SD cards are ready to use for new operation */
        while((BSP_SD_GetCardState() != SD_TRANSFER_OK))
        {
        } 
        
      if (SD_state != MSD_OK)
      {
        BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"SD WRITE : FAILED.", LEFT_MODE);
        BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
      }
      else
      {
        BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)"SD WRITE : OK.", LEFT_MODE);
        SD_state = BSP_SD_ReadBlocks_DMA(aRxBuffer, BLOCK_START_ADDR, NUM_OF_BLOCKS);
          /* Wait for the read process is completed */
          while(SDReadStatus == 0)
          {
          }
          SDReadStatus = 0;
          
          /* Wait until SD card is ready to use for new operation */
          while(BSP_SD_GetCardState() != SD_TRANSFER_OK)
          {
          }         
        if (SD_state != MSD_OK)
        {
          BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"SD READ : FAILED.", LEFT_MODE);
          BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
        }
        else
        {
          BSP_LCD_DisplayStringAt(20, 145, (uint8_t *)"SD READ : OK.", LEFT_MODE);
          if (Buffercmp(aTxBuffer, aRxBuffer, BUFFER_WORDS_SIZE) > 0)
          {
            BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"SD COMPARE : FAILED.", LEFT_MODE);
            BSP_LCD_DisplayStringAt(20, 175, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
          }
          else
          {
            BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"SD Test : OK.", LEFT_MODE);
            BSP_LCD_DisplayStringAt(20, 175, (uint8_t *)"SD can be removed.", LEFT_MODE);
          }
        }
      }
    }
  }

  BSP_LCD_DisplayStringAt(20, 205, (uint8_t*)"Press Wakeup push-button to switch to next menu", CENTER_MODE);

  while (1)
  {
#if (SD_CARD_PRESENCE_VALIDATION_MODE == SD_CARD_PRESENCE_INTERRUPT_MODE)
    /* Check MFX interrupt occurred */    
    if(MfxItOccurred == SET)
    {
      Mfx_Event();    
#endif
      /* Check if the SD card is plugged in the slot */
      if (BSP_SD_IsDetected() != SD_PRESENT)
      {
        if(prev_status != SD_NOT_PRESENT)
        {
          BSP_SD_Init();
          prev_status = SD_NOT_PRESENT; 
          BSP_LCD_SetTextColor(LCD_COLOR_RED);
          BSP_LCD_DisplayStringAt(20, BSP_LCD_GetYSize() - 30, (uint8_t *)"SD Not Connected", LEFT_MODE);
        }
      }
      else if (prev_status != SD_PRESENT)
      {
        BSP_LCD_DisplayStringAt(20, BSP_LCD_GetYSize() - 30,   (uint8_t *)"SD Connected    ", LEFT_MODE);
        prev_status = SD_PRESENT;
      }
#if (SD_CARD_PRESENCE_VALIDATION_MODE == SD_CARD_PRESENCE_INTERRUPT_MODE)
    }
#endif

    if (TamperItOccurred == SET)
    {
      /* Add delay to avoid rebound and reset it status */
      HAL_Delay(500);
      TamperItOccurred = RESET;
      
      return;
    }
  }
}

/**
  * @brief  Display SD Demo Hint
  * @param  None
  * @retval None
  */
static void SD_SetHint(void)
{
  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Set LCD Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"SD", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to write", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"and read data on the microSD and also", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"how to detect the presence of the card", CENTER_MODE);

  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
  BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);

  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 1: pBuffer identical to pBuffer1
  *         0: pBuffer differs from pBuffer1
  */
static uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

/**
  * @brief Tx Transfer completed callback
  * @param None
  * @retval None
  */
void BSP_SD_WriteCpltCallback(void)
{
  SDWriteStatus = 1;
}

/**
  * @brief Rx Transfer completed callback
  * @param None
  * @retval None
  */
void BSP_SD_ReadCpltCallback(void)
{
  SDReadStatus = 1; 
}

/**
  * @brief SDMMC error callback
  * @param None
  * @retval None
  */
void HAL_SD_ErrorCallback(SD_HandleTypeDef *hsd)
{
  Error_Handler();
}

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
