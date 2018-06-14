/**
  ******************************************************************************
  * @file    k_mfx.c
  * @author  MCD Application Team
  * @brief   This file provides the kernel MFX functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_MFX
  * @brief Kernel menu routines
  * @{
  */

/* External variables --------------------------------------------------------*/
extern void BSP_SD_DetectCallback(void);

/* Private typedef -----------------------------------------------------------*/
typedef struct Mfx_Ctx_s
{
  uint8_t           InitDone;
  osSemaphoreId     IOLockID;
  osThreadId        ThreadID;
  osSemaphoreId     SemaphoreID;
} Mfx_Ctx_t;

/* Private defines -----------------------------------------------------------*/
#define MFX_IO_TIMEOUT_MS               10 /* osWaitForever */

#define MMI_INTERPRETER_QUEUE_POOL_SIZE 10
#define MMI_INTERPRETER_QUEUE_SIZE      30
#define MFX_TaskPRIORITY                osPriorityRealtime /* osPriorityLow osPriorityNormal osPriorityRealtime */
#define MFX_TaskSTACK_SIZE              (configMINIMAL_STACK_SIZE * 2)

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static Mfx_Ctx_t Mfx_Ctx = { 0 };

/* Private function prototypes -----------------------------------------------*/
static void MfxThread(void const * argument);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Mfx thread initialization to manage interrupt
  * @param  None
  * @retval None
  */
void k_MfxInit(void)
{
  if(!Mfx_Ctx.InitDone)
  {
    /* Enable SD Interrupt mode */
    // BSP_SD_ITConfig();

    /* Create IO Semaphore lock */
    osSemaphoreDef(IO_Semaphore);

    /* Create the IO Semaphore used by the IO BSP */
    Mfx_Ctx.IOLockID = osSemaphoreCreate(osSemaphore(IO_Semaphore), 1);

    /* Create Semaphore lock */
    osSemaphoreDef(MFX_Semaphore);

    /* Create the Semaphore used by the two threads */
    Mfx_Ctx.SemaphoreID = osSemaphoreCreate(osSemaphore(MFX_Semaphore), 1);

    /* Get the semaphore */
    osSemaphoreWait(Mfx_Ctx.SemaphoreID, osWaitForever);

    /* Create mfx task */
    osThreadDef(MFX_Thread, MfxThread, MFX_TaskPRIORITY, 0, MFX_TaskSTACK_SIZE);
    Mfx_Ctx.ThreadID = osThreadCreate (osThread(MFX_Thread), NULL);

    Mfx_Ctx.InitDone = 1;
  }
}

/**
  * @brief  interrupt detection
  * @param  None
  * @retval None
  */
void k_MfxDetectInt(void)
{
  if(Mfx_Ctx.InitDone)
  {
    /* Release the semaphore */
    osSemaphoreRelease(Mfx_Ctx.SemaphoreID);
  }
}


/**
  * @brief  Mfx Thread
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */

__IO uint32_t errorSrc = 0;
__IO uint32_t errorMsg = 0;

static void MfxThread(void const * argument)
{
  for( ;; )
  {
    uint32_t irqPending = 0;

    osSemaphoreWait(Mfx_Ctx.SemaphoreID, osWaitForever);

    /* Disable MFX interrupt to manage current one */
    HAL_NVIC_DisableIRQ(MFX_INT_EXTI_IRQn);

    irqPending = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_PENDING);

    /* GPIO IT from MFX */
    if(irqPending & MFXSTM32L152_IRQ_GPIO)
    {
      uint32_t statusGpio = 0;

      if(BSP_IO_ITGetStatus(SD_DETECT_PIN))
      {
        BSP_SD_DetectCallback();
        statusGpio |= SD_DETECT_PIN;
      }

      if(statusGpio)
      {
        /* Clear IO Expander IT */
        BSP_IO_ITClear(statusGpio);
      }
    }
    else if(irqPending & MFXSTM32L152_IRQ_ERROR)
    {
      errorSrc = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_SRC);
      errorMsg = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_MSG);
    }

    /* Ack all IRQ pending except GPIO if any */
    irqPending &= ~MFXSTM32L152_IRQ_GPIO;
    if (irqPending)
    {
      MFX_IO_Write(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_ACK, irqPending);
    }
    
    /* Re-enable MFX interrupt */
    HAL_NVIC_EnableIRQ(MFX_INT_EXTI_IRQn);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
