/**
  ******************************************************************************
  * @file    ts.c
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
#include "stm32l4r9i_discovery.h"
#include "stm32l4r9i_discovery_io.h"
#include "stm32l4r9i_discovery_ts.h"

#include "cmsis_os.h"
#include "k_bsp.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_MFX
  * @brief Kernel menu routines
  * @{
  */
    
/* External variables --------------------------------------------------------*/
extern uint8_t GUI_Initialized;

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static osSemaphoreId TouchIntSemaphore;
static osThreadId    TouchIntThread;
static uint8_t       TS_Initialized = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void TouchThread(void const * argument);

/**
  * @brief  Touch hardware abd thread initialization to manage interrupt
  * @param  None 
  * @retval None
  */
void TouchInit(void)
{
  /* Create Touch Screen task */
  osThreadDef(TS_Thread, TouchThread, osPriorityAboveNormal, 0, 128);
  TouchIntThread = osThreadCreate (osThread(TS_Thread), NULL);
}

/**
  * @brief  Used to check if the Touch is already initialized or not
  * @param  None 
  * @retval Touch initialization done or not
  */
uint8_t IsTouchInitialized(void)
{
  return TS_Initialized;
}

/**
  * @brief  Touch hardware and thread de-initialization
  * @param  None 
  * @retval None
  */
void TouchDeInit(void)
{
#ifdef TS_INTERRUPT_MODE_ENABLED
  /* DeInitialize the Touch Screen Controller */
  BSP_TS_ITClear();
  BSP_TS_DeInit();
#endif
  /* Delete the Touch Screen task */
  if(TouchIntThread)
  {
    osThreadTerminate(TouchIntThread);
  }

  /* Delete the Semaphore lock */
  if(TouchIntSemaphore)
  {
    osSemaphoreDelete(TouchIntSemaphore);
  }
}

/**
  * @brief  interrupt detection
  * @param  None 
  * @retval None
  */
void TouchDetectInt(void)
{  
  /* Release the semaphore if the thread was created prior to this call */
  if(TouchIntSemaphore)
  {
    osSemaphoreRelease(TouchIntSemaphore);
  }
}


/**
  * @brief  Touch Screen Thread
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
static void TouchThread(void const * argument)
{
  /* Create Semaphore lock */
  osSemaphoreDef(TOUCH_SCREEN_SEM);
  
  /* Create the Semaphore used by the two threads */
  TouchIntSemaphore = osSemaphoreCreate(osSemaphore(TOUCH_SCREEN_SEM), 1); 

  /* Get the semaphore */
  osSemaphoreWait(TouchIntSemaphore, osWaitForever);

  for( ;; )
  {
    /* WA to force TS init after the LCD init */
    if(GUI_Initialized && !TS_Initialized)
    {
      BSP_IO_Init();

      /* Initialize the Touch Screen Controller */
      if (BSP_TS_Init(390, 390) == TS_OK)
      {
#ifdef TS_INTERRUPT_MODE_ENABLED
        /* Enable TS interrupt */
        if(BSP_TS_ITConfig() == TS_OK)
        {
          TS_Initialized = 1;
        }
#else
        TS_Initialized = 1;
#endif
      }
      else
      {
        TS_Initialized = 0;
        osDelay(20);
      }
    }
    else if(!GUI_Initialized)
    {
      osDelay(100);
    }
    else
    {
      osSemaphoreWait(TouchIntSemaphore, osWaitForever);
#ifdef TS_INTERRUPT_MODE_ENABLED
      /* Disable TS interrupt to manage current one */
      HAL_NVIC_DisableIRQ(TS_INT_EXTI_IRQn);
#endif
      /* Update TS data */
      k_TouchUpdate();
#ifdef TS_INTERRUPT_MODE_ENABLED
      /* Re-enable TS interrupt */
      HAL_NVIC_EnableIRQ(TS_INT_EXTI_IRQn);
#endif
    }
  }
}



/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
