/**
  ******************************************************************************
  * @file    Examples_LL/IWDG/IWDG_RefreshUntilUserEvent/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to configure IWDG down-counter (without Window)
  *          using the STM32L4xx IWDG LL API.
  *          Peripheral initialization done using LL unitary services functions.
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

/** @addtogroup STM32L4xx_LL_Examples
  * @{
  */

/** @addtogroup IWDG_RefreshUntilUserEvent
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint8_t ubKeyPressed = 0;
/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config_2MHz(void);
void     Check_IWDG_Reset(void);
void     Configure_IWDG(void);
void     LED_Init(void);
void     LED_On(void);
void     UserButton_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
 /* Configure the system clock to 2MHz */
  SystemClock_Config_2MHz();

  /* Initialize LED1 */
  LED_Init();

  /* Initialize button in EXTI mode */
  UserButton_Init();
  
  /* Check if the system has resumed from IWDG reset */
  Check_IWDG_Reset();
  
  /* Configure the IWDG */
  Configure_IWDG();

  /* Infinite loop */
  while (1)
  {
    if (1 != ubKeyPressed)
    {
      /* Refresh IWDG down-counter to default value */
      LL_IWDG_ReloadCounter(IWDG);
      
      LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
      /* Note that period used for Counter Reload MUST be higher than blinking timing value*/
      /* This Counter reload timeout period is a function of this value and the 
         clock prescaler. Refer to the datasheet for the timeout information  */
      LL_mDelay(LED_BLINK_FAST);
    }
  }
}

/**
  * @brief  This function configures IWDG
  * @param  None
  * @retval None
  */
void Configure_IWDG(void)
{
  /* Enable the peripheral clock of DBG register (uncomment for debug purpose) */
  /* ------------------------------------------------------------------------- */
  /*  LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_IWDG_STOP); */
  
  /* Enable the peripheral clock IWDG */
  /* -------------------------------- */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
  }

  /* Configure the IWDG with window option disabled */
  /* ------------------------------------------------------- */
  /* (1) Enable the IWDG by writing 0x0000 CCCC in the IWDG_KR register */
  /* (2) Enable register access by writing 0x0000 5555 in the IWDG_KR register */
  /* (3) Write the IWDG prescaler by programming IWDG_PR from 0 to 7 - LL_IWDG_PRESCALER_4 (0) is lowest divider*/
  /* (4) Write the reload register (IWDG_RLR) */
  /* (5) Wait for the registers to be updated (IWDG_SR = 0x0000 0000) */
  /* (6) Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA) */
  LL_IWDG_Enable(IWDG);                             /* (1) */
  LL_IWDG_EnableWriteAccess(IWDG);                  /* (2) */
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_4);  /* (3) */
  LL_IWDG_SetReloadCounter(IWDG, 0xFEE);            /* (4) */
  while (LL_IWDG_IsReady(IWDG) != 1)                /* (5) */
  {
  }
  LL_IWDG_ReloadCounter(IWDG);                      /* (6) */
}

/**
  * @brief  This function check if the system has resumed from IWDG reset
  * @param  None
  * @retval None
  */
void Check_IWDG_Reset(void)
{
  if (LL_RCC_IsActiveFlag_IWDGRST())
  {
    /* clear IWDG reset flag */
    LL_RCC_ClearResetFlags();

    /* turn Led on and wait for user event to perform example again */
    LED_On();
    
    while(ubKeyPressed != 1)
    {
    }

    /* Reset ubKeyPressed value */
    ubKeyPressed = 0;
  }
}

/**
  * @brief  Initialize LED2.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED1 Clock */
  LED1_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED1 */
  LL_GPIO_SetPinMode(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-on LED1.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED1 on */
  LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
}

/**
  * @brief  Configures User push-button in EXTI Line Mode.
  * @param  None
  * @retval None
  */
void UserButton_Init(void)
{
  /* Enable the BUTTON Clock */
  USER_BUTTON_GPIO_CLK_ENABLE();
  
  /* Configure GPIO for BUTTON */
  LL_GPIO_SetPinMode(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_PULL_NO);
  /* Connect External Line to the GPIO*/
  USER_BUTTON_SYSCFG_SET_EXTI();
  
  /* Enable a rising trigger EXTI line 13 Interrupt */
  USER_BUTTON_EXTI_LINE_ENABLE();
  USER_BUTTON_EXTI_FALLING_TRIG_ENABLE();
  
  /* Configure NVIC for USER_BUTTON_EXTI_IRQn */ 
  NVIC_SetPriority(USER_BUTTON_EXTI_IRQn,0x03);
  NVIC_EnableIRQ(USER_BUTTON_EXTI_IRQn);
}
/**
  * @brief  System Clock Configuration to 2MHz
  *         The system Clock is configured as follows :
  *            System Clock source            = MSI
  *            SYSCLK(Hz)                     = 2000000
  *            HCLK(Hz)                       = 2000000
  *            MSI Frequency(Hz)              = 2000000
  * @param  None
  * @retval None
  */
void SystemClock_Config_2MHz(void)
{
  /* Change Sysclock */
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_5);
  
  /* Set systick to 1ms in using frequency set to 2MHz */
  LL_Init1msTick(2000000);
  
  /* Update CMSIS variable */
  SystemCoreClock = 2000000; 
}
/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT                                               */
/******************************************************************************/
/**
  * @brief  Function to manage IRQ Handler
  * @param  None
  * @retval None
  */
void UserButton_Callback(void)
{
  ubKeyPressed = 1;
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
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

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
