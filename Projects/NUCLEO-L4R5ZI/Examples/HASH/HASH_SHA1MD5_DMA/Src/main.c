/**
  ******************************************************************************
  * @file    HASH/HASH_SHA1MD5_DMA/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a short description of HASH digest calculation
  *          using SHA1 and MD5 example.
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

/** @addtogroup HASH_SHA1MD5_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* HASH handler declaration */
HASH_HandleTypeDef     HashHandle;
__ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The STM32L4xx series is the result of a perfect symbiosis of the real-time control capabilities of an MCU and the signal processing performance of a DSP, and thus complements the STM32 portfolio with a new class of devices, digital signal controllers (DSC).";

__ALIGN_BEGIN static uint8_t aMD5Digest[16] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectMD5Digest[16] __ALIGN_END = {0x63, 0xaa, 0x3b, 0xb4, 0xb1, 0xfa, 0x81, 0xbf,
                                                                 0x15, 0x7b, 0x4b, 0x15, 0xd9, 0xb6, 0x10, 0xb8
                                                                };
__ALIGN_BEGIN static uint8_t aSHA1Digest[20] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectSHA1Digest[20] __ALIGN_END = {0x6b, 0x34, 0x75, 0xb7, 0x73, 0x53, 0x33, 0x85, 
                                                                  0x77, 0x75, 0x5c, 0xc9, 0x0b, 0xcd, 0x73, 0x35, 
                                                                  0x30, 0xa2, 0x35, 0x12
                                                                  };
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure LEDs */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /* Configure the system clock to 120 MHz */
  SystemClock_Config();


  /****************************************************************************/
  /******************************** SHA1 **************************************/
  /****************************************************************************/
  if(HAL_HASH_DeInit(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }
  HashHandle.Init.DataType = HASH_DATATYPE_8B;

  if (HAL_HASH_Init(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }

  /* Start HASH computation using DMA transfer */
  if (HAL_HASH_SHA1_Start_DMA(&HashHandle, (uint8_t *)aInput, strlen((char const *)aInput)) != HAL_OK)
  {
    Error_Handler();
  }
  /* Wait for DMA transfer to complete */ 
  while (HAL_HASH_GetState(&HashHandle) == HAL_HASH_STATE_BUSY);

  /* Get the computed digest value */
  if (HAL_HASH_SHA1_Finish(&HashHandle, aSHA1Digest, 0xFF) != HAL_OK)
  {
    Error_Handler();
  }

  /* Compare computed digest with expected one */
  if (memcmp(aSHA1Digest, aExpectSHA1Digest, sizeof(aExpectSHA1Digest) / sizeof(aExpectSHA1Digest[0])) != 0)
  {
    BSP_LED_On(LED3);
  }
  else
  {
    BSP_LED_On(LED1);
  }

  /****************************************************************************/
  /******************************** MD5 ***************************************/
  /****************************************************************************/
  if(HAL_HASH_DeInit(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }
  HashHandle.Init.DataType = HASH_DATATYPE_8B;

  if (HAL_HASH_Init(&HashHandle) != HAL_OK)
  {
    Error_Handler();
  }

  /* Start HASH computation using DMA transfer */
  if (HAL_HASH_MD5_Start_DMA(&HashHandle, (uint8_t *)aInput, strlen((char const *)aInput)) != HAL_OK)
  {
    Error_Handler();
  }
  /* Wait for DMA transfer to complete */ 
  while (HAL_HASH_GetState(&HashHandle) == HAL_HASH_STATE_BUSY);

  /* Get the computed digest value */
  if (HAL_HASH_MD5_Finish(&HashHandle, aMD5Digest, 0xFF) != HAL_OK)
  {
    Error_Handler();
  }

  /* Compare computed digest with expected one */
  if (memcmp(aMD5Digest, aExpectMD5Digest, sizeof(aExpectMD5Digest) / sizeof(aExpectMD5Digest[0])) != 0)
  {
    Error_Handler();
  }
  else
  {
    BSP_LED_On(LED2);
  }
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 120000000
  *            HCLK(Hz)                       = 120000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 60
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  
  /* Enable voltage range 1 boost mode for frequency above 80 Mhz */
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  __HAL_RCC_PWR_CLK_DISABLE();

  /* Enable MSI Oscillator and activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  /* To avoid undershoot due to maximum frequency, select PLL as system clock source */
  /* with AHB prescaler divider 2 as first step */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* AHB prescaler divider at 1 as second step */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while (1)
  {
  } 
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
