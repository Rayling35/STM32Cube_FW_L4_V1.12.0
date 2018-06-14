/**
  ******************************************************************************
  * @file    stm32l4xx_it.c 
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32l4xx_it.h"
#include "GUI.h"

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
extern volatile GUI_TIMER_TIME OS_TimeMS;

extern SAI_HandleTypeDef             BSP_AUDIO_hSai;
extern SAI_HandleTypeDef             BSP_AUDIO_hSai_Rx;
extern DFSDM_Filter_HandleTypeDef    BSP_AUDIO_hDfsdmLeftFilter;
extern SD_HandleTypeDef              hsd_eval;
extern DSI_HandleTypeDef             hdsi;
extern LTDC_HandleTypeDef            hltdc;
extern GFXMMU_HandleTypeDef          hgfxmmu;
extern DMA2D_HandleTypeDef           hdma2d;
extern RTC_HandleTypeDef             RtcHandle;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  while(1);
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while(1);
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while(1);
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while(1);
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while(1);
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
#if (GUI_OS == 0)
  HAL_IncTick();
  
  OS_TimeMS++;
#else
  osSystickHandler();
#endif
}
  
/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(MFX_INT_PIN);
}

/**
  * @brief  This function handles External line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
#if defined(USE_GVO_390x390)
  HAL_GPIO_EXTI_IRQHandler(TS_DSI_INT_PIN);
#else
  HAL_GPIO_EXTI_IRQHandler(TS_RGB_INT_PIN);
#endif
}

/**
  * @brief  This function handles External line 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler (void)
{
  if(__HAL_GPIO_EXTI_GET_FLAG(WAKEUP_BUTTON_PIN) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(WAKEUP_BUTTON_PIN);
  }
  
  if(__HAL_GPIO_EXTI_GET_FLAG(TS_RGB_INT_PIN) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(TS_RGB_INT_PIN);
  }
}

/**
 * @brief  This function handles SDMMC interrupt request.
 * @param  None
 * @retval None
 */
void SDMMC1_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hsd_eval);
}

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc);
}

/**
  * @brief  This function handles LTDC error global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_ER_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc);
}

#if defined(USE_GVO_390x390)
/**
  * @brief  This function handles DSI global interrupt request.
  * @param  None
  * @retval None
  */
void DSI_IRQHandler(void)
{
  HAL_DSI_IRQHandler(&hdsi);
}

/**
  * @brief  This function handles DSI global interrupt request.
  * @param  None
  * @retval None
  */
void GFXMMU_IRQHandler(void)
{
  HAL_GFXMMU_IRQHandler(&hgfxmmu);
}
#endif /* USE_GVO_390x390 */

/**
  * @brief  This function handles RTC Alarm interrupt request.
  * @param  None
  * @retval None
  */
void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&RtcHandle);
}

/**
  * @brief  This function handles DFSDM Left DMAinterrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDM_DMAx_LEFT_IRQHandler(void)
{ 
  HAL_DMA_IRQHandler(BSP_AUDIO_hDfsdmLeftFilter.hdmaReg);
}
    /**
  * @brief  This function handles DFSDM Right DMAinterrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDM_DMAx_RIGHT_IRQHandler(void)
{ 
  HAL_DMA_IRQHandler(BSP_AUDIO_hDfsdmRightFilter.hdmaReg);
}

/**
  * @brief  This function handles SAI1 interrupt request.
  * @param  None
  * @retval None
  */
void SAI1_IRQHandler(void)
{
  HAL_SAI_IRQHandler(&BSP_AUDIO_hSai);
}

/**
  * @brief  This function handles SAI DMAinterrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_SAIx_DMAx_IRQHandler(void)
{ 
  HAL_DMA_IRQHandler(BSP_AUDIO_hSai.hdmatx);
}

///**
//  * @brief  This function handles DMA2D global interrupt request.
//  * @param  None
//  * @retval None
//  */
//void DMA2D_IRQHandler(void)
//{
//  HAL_DMA2D_IRQHandler(&hdma2d);
//}

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
