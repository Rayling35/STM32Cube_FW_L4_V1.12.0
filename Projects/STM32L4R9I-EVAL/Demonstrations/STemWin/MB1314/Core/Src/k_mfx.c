/**
  ******************************************************************************
  * @file    k_mfx.c
  * @author  MCD Application Team 
  * @brief   This file provides the kernel menu functions 
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
#include "iddmeasure.h"

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
osMessageQId MfxEvent;
osSemaphoreId MfxIddSemaphore;

/* Flags used to recover Idd measurements results from Standby or Shutdown mode */
extern Idd_StateTypedef IddMeasureState;
extern FlagStatus Fetch_IddResults;
extern FlagStatus Simulate_SecondPress;
extern osMessageQId StorageEvent;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void MfxThread(void const * argument);


/**
  * @brief  Mfx thread initialization
  * @param  None 
  * @retval None
  */
void k_MfxInit(void)
{  
  /* Create Mfx Message Queue */
  osMessageQDef(osqueue, 3, uint16_t);
  MfxEvent = osMessageCreate (osMessageQ(osqueue), NULL);

  /* Create Semaphore lock */
  osSemaphoreDef(MFX_IDD_SEM);
  
  /* Create the Semaphore used by the two threads */
  MfxIddSemaphore = osSemaphoreCreate(osSemaphore(MFX_IDD_SEM), 1); 
  /* Get the semaphore */
  osSemaphoreWait(MfxIddSemaphore, osWaitForever);
  
  /* Create  background task */
  osThreadDef(MFX_Thread, MfxThread, osPriorityRealtime, 0, 128);
  osThreadCreate (osThread(MFX_Thread), NULL);
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
  osEvent event;
  uint32_t irqPending;
  
  for( ;; ){
    event = osMessageGet( MfxEvent, osWaitForever );
    
    if( event.status == osEventMessage ){

      /* Disable MFX interrupt to manage current one */
      HAL_NVIC_DisableIRQ(MFX_INT_EXTI_IRQn);

      switch(event.value.v){
        case MFX_INTERRUPT_EVENT:
          if (IddMeasureState == IDD_STATE_MEASURE_ON_GOING) {
#ifdef WA_RESET_AFTER_IDD_MEASURE
             HAL_NVIC_SystemReset();
#else
            /* if function pointer exists, restore context clocks and power context */
            if(IddTest[iddTestIndex].IddRestore != NULL){
              IddTest[iddTestIndex].IddRestore();
              /* Configure HW resources */
              SystemHardwareInit(HWINIT_IDD);
            }
#endif
          }
          
          irqPending = MFX_IO_Read(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_PENDING);
          
          /* GPIO IT from MFX */
          if(irqPending & MFX_IRQ_PENDING_GPIO){
            uint32_t statusGpio = BSP_IO_ITGetStatus(SD_DETECT_PIN);

            if(statusGpio & SD_DETECT_PIN){
              k_SDCardDetectCallback();
            }
//            else if(statusGpio & TS_DSI_INT_PIN)
//            {
//              if (IddMeasureState != IDD_STATE_MEASURE_ON_GOING){
//                k_TouchUpdate();
//                if (Simulate_SecondPress == SET)
//                { 
//                  Fetch_IddResults = SET ;
//                  Simulate_SecondPress = RESET;                    
//                }
//              }
//            }
            else{
              Error_Handler();
            }
            
            BSP_IO_ITClear(statusGpio);
          }
          else if(irqPending & MFX_IRQ_PENDING_IDD){
            if (IddMeasureState == IDD_STATE_MEASURE_ON_GOING){
              IddMeasureState = IDD_STATE_MEASURE_OK;
              osMutexRelease(MfxIddSemaphore);
            }
          }
          else if(irqPending & MFX_IRQ_PENDING_ERROR){
            if (IddMeasureState == IDD_STATE_MEASURE_ON_GOING) {
              IddMeasureState = IDD_STATE_MEASURE_ERROR;
              /* Error register will be read and acknoledged by iddmeasure */
              osMutexRelease(MfxIddSemaphore);
            }
            else{
              errorSrc = MFX_IO_Read(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_SRC);
              errorMsg = MFX_IO_Read(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_MSG);
            }
          }
          
          /* Ack all IRQ pending except GPIO if any */
          irqPending &= ~MFX_IRQ_PENDING_GPIO;
          if (irqPending){
            MFX_IO_Write(IDD_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_ACK, irqPending);
          }
          break;         
      }

      /* Re-enable MFX interrupt */
      HAL_NVIC_EnableIRQ(MFX_INT_EXTI_IRQn);
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
