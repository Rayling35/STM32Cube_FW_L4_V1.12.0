/**
  ******************************************************************************
  * @file    ADC/ADC_LowPower/Src/stm32l4xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
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

/** @defgroup ADC_LowPower
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief ADC MSP initialization
  *        This function configures the hardware resources used in this example:
  *          - Enable clock of ADC peripheral
  *          - Configure the GPIO associated to the peripheral channels
  *          - Configure the DMA associated to the peripheral
  *          - Configure the NVIC associated to the peripheral interruptions
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef  RCC_PeriphCLKInitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable clock of GPIO associated to the peripheral channels */
  ADCx_CHANNELa_GPIO_CLK_ENABLE();
  
  /* Enable clock of ADCx peripheral */
  ADCx_CLK_ENABLE();
  
  /* Note: In case of usage of asynchronous clock derived from ADC dedicated  */
  /*       PLL 64MHz, with ADC setting                                        */
  /*       "AdcHandle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1",            */
  /*       the clock source has to be enabled at RCC top level using macro    */
  /*       "__HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_PLLSAI1)" or function       */
  /*       "HAL_RCCEx_PeriphCLKConfig()" (refer to comments in file           */
  /*       "stm32l4xx_hal_adc.c" header).                                     */

  /* Enable asynchronous clock source of ADCx */
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  RCC_PeriphCLKInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1M = 1;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1N = 32;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* ADCx Channel GPIO pin configuration */
  GPIO_InitStruct.Pin = ADCx_CHANNELa_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADCx_CHANNELa_GPIO_PORT, &GPIO_InitStruct);
  
  /*##-3- Configure the DMA ##################################################*/

  /* ADC does not use DMA in this ADC example */

  /*##-4- Configure the NVIC #################################################*/

  /* NVIC configuration for ADC interrupt */
  /* Priority: high-priority */
  HAL_NVIC_SetPriority(ADCx_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(ADCx_IRQn);
}

/**
  * @brief ADC MSP de-initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable clock of ADC peripheral
  *          - Revert GPIO associated to the peripheral channels to their default state
  *          - Revert DMA associated to the peripheral to its default state
  *          - Revert NVIC associated to the peripheral interruptions to its default state
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  /*##-1- Reset peripherals ##################################################*/
  ADCx_FORCE_RESET();
  ADCx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* De-initialize the ADC Channel GPIO pin */
  HAL_GPIO_DeInit(ADCx_CHANNELa_GPIO_PORT, ADCx_CHANNELa_PIN);

  /*##-3- Disable the DMA ####################################################*/

  /* ADC does not use DMA in this ADC example */

  /*##-4- Disable the NVIC ###################################################*/  
  /* Disable the NVIC configuration for ADC interrupt */
  HAL_NVIC_DisableIRQ(ADCx_IRQn);
}

/**
  * @brief TIM MSP initialization
  *        This function configures the hardware resources used in this example:
  *          - Enable clock of peripheral
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /* TIM peripheral clock enable */
  TIMx_CLK_ENABLE();
}

/**
  * @brief TIM MSP de-initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable clock of peripheral
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Reset peripherals ##################################################*/
  TIMx_FORCE_RESET();
  TIMx_RELEASE_RESET();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
