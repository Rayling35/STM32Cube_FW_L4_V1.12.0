/**
  ******************************************************************************
  * @file    mfx.c
  * @author  MCD Application Team 
  * @brief   This file provides the kernel menu functions 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2017 STMicroelectronics International N.V. 
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
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define MFX_IRQ_PENDING_GPIO    0x01                                                              
#define MFX_IRQ_PENDING_IDD     0x02                                                              
#define MFX_IRQ_PENDING_ERROR   0x04
#define MFX_IRQ_PENDING_TS_DET  0x08
#define MFX_IRQ_PENDING_TS_NE   0x10
#define MFX_IRQ_PENDING_TS_TH   0x20
#define MFX_IRQ_PENDING_TS_FULL 0x40
#define MFX_IRQ_PENDING_TS_OVF  0x80

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static osSemaphoreId MfxIntSemaphore;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void MfxThread(void const * argument);

/**
  * @brief  Mfx thread initialization to manage interrupt
  * @param  None 
  * @retval None
  */
void MfxInit(void)
{
  /* Create  mfx task */
  osThreadDef(MFX_Thread, MfxThread, osPriorityRealtime, 0, 128);
  osThreadCreate (osThread(MFX_Thread), NULL);
}

/**
  * @brief  interrupt detection
  * @param  None 
  * @retval None
  */
void MfxDetectInt(void)
{  
  /* Release the semaphore if the thread was created prior to this call */
  if(MfxIntSemaphore)
  {
    osSemaphoreRelease(MfxIntSemaphore);
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
  uint32_t irqPending;

  /* Create Semaphore lock */
  osSemaphoreDef(MFX_IDD_SEM);
  
  /* Create the Semaphore used by the two threads */
  MfxIntSemaphore = osSemaphoreCreate(osSemaphore(MFX_IDD_SEM), 1); 

  /* Get the semaphore */
  osSemaphoreWait(MfxIntSemaphore, osWaitForever);

  for( ;; )
  {
    osSemaphoreWait(MfxIntSemaphore, osWaitForever);    

    /* Disable MFX interrupt to manage current one */
    HAL_NVIC_DisableIRQ(MFX_INT_EXTI_IRQn);
    
    irqPending = MFX_IO_Read(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_PENDING);
    
    /* GPIO IT from MFX */
    if(irqPending & MFX_IRQ_PENDING_GPIO)
    {
      uint32_t statusGpio = BSP_IO_ITGetStatus(SD_DETECT_PIN | TS_INT_PIN);

      if(statusGpio & SD_DETECT_PIN)
      {
        if(BSP_SD_IsDetected() == SD_PRESENT)
        {
          /* Notify App about connection event */
          osMessagePut ( StorageEvent, MSDDISK_CONNECTION_EVENT, 0);
        }
        else
        {
          /* Notify App about disconnection event */
          osMessagePut ( StorageEvent, MSDDISK_DISCONNECTION_EVENT, 0);
        }
      }

      if(statusGpio & TS_INT_PIN)
      {
#ifdef TS_INTERRUPT_MODE_ENABLED
        /* Update TS data */
        TouchDetectInt();
#endif /* TS_INTERRUPT_MODE_ENABLED */
      }

      /* Clear IO Expander IT */
      BSP_IO_ITClear(statusGpio);
    }
    
    /* Ack all IRQ pending except GPIO if any */
    irqPending &= ~MFX_IRQ_PENDING_GPIO;
    if (irqPending)
    {
      MFX_IO_Write(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_ACK, irqPending);
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
