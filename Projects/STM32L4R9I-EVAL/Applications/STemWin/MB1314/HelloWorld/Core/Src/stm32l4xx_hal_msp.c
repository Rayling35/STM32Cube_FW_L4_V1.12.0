/**
  ******************************************************************************
  * @file    STemWin/MB1314/HelloWorld/Core/Src/stm32l4xx_hal_msp.c
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


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_10
#define USARTx_TX_GPIO_PORT              GPIOB
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_11
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF7_USART3

#define RTC_CLOCK_SOURCE_LSI

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief RTC MSP Initialization
  *        This function configures the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  *
  * @note  Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select
  *        the RTC clock source; in this case the Backup domain will be reset in
  *        order to modify the RTC Clock source, as consequence RTC registers (including
  *        the backup registers) and RCC_BDCR register are set to their reset values.
  *
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
  RCC_OscInitTypeDef        RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

  /*##-1- Enables the PWR Clock and Enables access to the backup domain ######*/
  /* To enable access on RTC registers */
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  /*##-2- Configure LSE/LSI as RTC clock source ###############################*/
#ifdef RTC_CLOCK_SOURCE_LSE
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  /* Configures the External Low Speed oscillator (LSE) drive capability */
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);
#elif defined (RTC_CLOCK_SOURCE_LSI)
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
#else
#error Please select the RTC Clock source inside the main.h file
#endif /*RTC_CLOCK_SOURCE_LSE*/

  /*##-3- Enable RTC peripheral Clocks #######################################*/
  /* Enable RTC Clock */
  __HAL_RCC_RTC_ENABLE();

  /*##-4- Configure the NVIC for RTC WKUP ###################################*/
  HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

/**
  * @brief RTC MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
  /*##-1- Reset peripherals ##################################################*/
   __HAL_RCC_RTC_DISABLE();
}

/**
  * @brief DMA2D MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hdma2d: DMA2D handle pointer
  * @retval None
  */
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d)
{
  /* Enable the DMA2D clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /* Reset of DMA2D IP */
  __HAL_RCC_DMA2D_FORCE_RESET();
  __HAL_RCC_DMA2D_RELEASE_RESET();

  /*##-2- NVIC configuration  ################################################*/
  /* NVIC configuration for DMA2D transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2D_IRQn, 8, 0);
  HAL_NVIC_EnableIRQ(DMA2D_IRQn);
}

/**
  * @brief DMA2D MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hdma2d: DMA2D handle pointer
  * @retval None
  */
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d)
{
  /* Enable the DMA2D clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /* Enable DMA2D reset state */
  __HAL_RCC_DMA2D_FORCE_RESET();

  /* Release DMA2D from reset state */
  __HAL_RCC_DMA2D_RELEASE_RESET();

  /* ##-2- Disable DMA2D Clock ##################################################*/
  __HAL_RCC_DMA2D_CLK_DISABLE();

  /* ##-3- Disable DMA2D IRQ in NVIC #############################################*/
  HAL_NVIC_DisableIRQ(DMA2D_IRQn);
}

/**
  * @brief  Initialize the GFXMMU MSP.
  * @param  hgfxmmu : GFXMMU handle.
  * @retval None.
  */
void HAL_GFXMMU_MspInit(GFXMMU_HandleTypeDef *hgfxmmu)
{
  /* Enable the GFXMMU clock */
  __HAL_RCC_GFXMMU_CLK_ENABLE();
  
  /* Reset of GFXMMU IP */
  __HAL_RCC_GFXMMU_FORCE_RESET();
  __HAL_RCC_GFXMMU_RELEASE_RESET();
}

/**
  * @brief  De-initialize the GFXMMU MSP.
  * @param  hgfxmmu : GFXMMU handle.
  * @retval None.
  */
void HAL_GFXMMU_MspDeInit(GFXMMU_HandleTypeDef *hgfxmmu)
{
  /* Enable the GFXMMU clock */
  __HAL_RCC_GFXMMU_CLK_ENABLE();
  
  /* Reset of GFXMMU IP */
  __HAL_RCC_GFXMMU_FORCE_RESET();
  __HAL_RCC_GFXMMU_RELEASE_RESET();

  __HAL_RCC_GFXMMU_CLK_DISABLE();
}

/**
  * @brief LTDC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
  /* Enable the LTDC clock */
  __HAL_RCC_LTDC_CLK_ENABLE();

  /* Reset of LTDC IP */
  __HAL_RCC_LTDC_FORCE_RESET();
  __HAL_RCC_LTDC_RELEASE_RESET();

  /* Configure the clock for the LTDC */
  /* We want DSI PHI at 500MHz */
  /* We have only one line => 500Mbps */
  /* With 24bits per pixel, equivalent PCLK is 500/24 = 20.8MHz */
  /* We will set PCLK at 15MHz */
  /* Following values are OK with MSI = 4MHz */
  /* (4*60)/(1*4*4) = 15MHz */
  RCC_PeriphCLKInitTypeDef  PeriphClkInit;
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInit.PLLSAI2.PLLSAI2Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI2.PLLSAI2M = 1;
  PeriphClkInit.PLLSAI2.PLLSAI2N = 60;
  PeriphClkInit.PLLSAI2.PLLSAI2R = RCC_PLLR_DIV4;
  PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLLSAI2_DIV4;
  PeriphClkInit.PLLSAI2.PLLSAI2ClockOut = RCC_PLLSAI2_LTDCCLK;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    while(1);
  }

  /* NVIC configuration for LTDC interrupts that are now enabled */
  HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(LTDC_IRQn);
  HAL_NVIC_SetPriority(LTDC_ER_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
}

/**
  * @brief LTDC MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{
  /* Disable IRQ of LTDC IP */
  HAL_NVIC_DisableIRQ(LTDC_IRQn);
  HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);

  /* Disable LTDC block */
  __HAL_LTDC_DISABLE(hltdc);

  /* Reset of LTDC IP */
  __HAL_RCC_LTDC_FORCE_RESET();

  /* Disable LTDC clock */
  __HAL_RCC_LTDC_CLK_DISABLE();
}


/**
  * @brief  Initializes the DSI MSP.
  * @param  hdsi: pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @retval None
  */
void HAL_DSI_MspInit(DSI_HandleTypeDef* hdsi)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Enable DSI Host and wrapper clocks */
  __HAL_RCC_DSI_CLK_ENABLE();
  
  /* Reset the DSI Host and wrapper */
  __HAL_RCC_DSI_FORCE_RESET();
  __HAL_RCC_DSI_RELEASE_RESET();
 
  /* Enable HSE used for DSI PLL */
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_RCC_GetOscConfig(&RCC_OscInitStruct);
  if(RCC_OscInitStruct.HSEState == RCC_HSE_OFF)
  {
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      while(1);
}
  }

  /* Configure PG6 in AF11 DSIHOST_TE */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF11_DSI;
  gpio_init_structure.Pin       = GPIO_PIN_11;
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);

  /* NVIC configuration for DSI interrupt that is now enabled */
  HAL_NVIC_SetPriority(DSI_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DSI_IRQn);
}


/**
  * @brief  De-initializes the DSI MSP.
  * @param  hdsi: pointer to a DSI_HandleTypeDef structure that contains
  *               the configuration information for the DSI.
  * @retval None
  */
void HAL_DSI_MspDeInit(DSI_HandleTypeDef* hdsi)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  GPIO_InitTypeDef  gpio_init_structure;

  /* Disable IRQ of DSI IP */
  HAL_NVIC_DisableIRQ(DSI_IRQn);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_OFF;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  /* GPIOF deactivation */
  gpio_init_structure.Pin       = GPIO_PIN_11;
  HAL_GPIO_DeInit(GPIOF, gpio_init_structure.Pin);

  /* Enable DSI reset state */
  __HAL_RCC_DSI_FORCE_RESET();

  /* ##-2- Disable DSI Clock ##################################################*/
  __HAL_RCC_DSI_CLK_DISABLE();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
