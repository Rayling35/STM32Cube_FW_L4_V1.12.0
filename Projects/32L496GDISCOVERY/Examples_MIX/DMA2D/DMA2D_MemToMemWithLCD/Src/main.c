/**
  ******************************************************************************
  * @file    Examples_MIX/DMA2D/DMA2D_MemToMemWithLCD/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a description of how to configure 
  *          DMA2D peripheral in Memory to Memory transfer mode 
  *          and display the result on LCD, in resorting to DMA2D LL APIs.
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
#include "RGB565_240x160.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @addtogroup DMA2D_MemToMemWithLCD
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Blended image Ready flag */
__IO uint32_t   blended_image_ready = 0;

/* Private function prototypes -----------------------------------------------*/
static void IO_Init(void);
static void LCD_ImagePreparation(uint16_t x0, uint16_t y0, uint16_t xSize, uint16_t ySize);

static void DMA2D_Config(void);
static void SystemClock_Config(void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  blended_image_ready = 0;
  
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
  
  /* Configure the system clock */
  SystemClock_Config(); 
    
  /* Configure LED1 and LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  
  /*##-1- LCD Configuration ##################################################*/
  /* I/O initialization, required before LCD initialization */
  IO_Init();
  
  /* LCD initialization */
  BSP_LCD_Init();
  
  /* Configure LCD before image display: set first pixel position and image size */
  LCD_ImagePreparation((ST7789H2_LCD_PIXEL_WIDTH - LAYER_SIZE_X)/2, (ST7789H2_LCD_PIXEL_HEIGHT - LAYER_SIZE_Y)/2, LAYER_SIZE_X, LAYER_SIZE_Y);
  
  /*##-2- DMA2D configuration ################################################*/
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2D);
  NVIC_SetPriority(DMA2D_IRQn, 0);  
  NVIC_EnableIRQ(DMA2D_IRQn);
  
  DMA2D_Config();
  
  /*##-3- Start DMA2D transfer ###############################################*/  
  LL_DMA2D_FGND_SetMemAddr(DMA2D, (uint32_t)&RGB565_240x160);   /* Source buffer in format RGB565 and size 240x160                 */
  LL_DMA2D_SetOutputMemAddr(DMA2D, (uint32_t)&(LCD_ADDR->REG)); /* LCD data address                                                */
  LL_DMA2D_ConfigSize(DMA2D, LAYER_SIZE_Y * LAYER_SIZE_X, 1);   /* Force 1 pixel per line and width in pixels x height in pixels   */
                                                                /* as number of lines to align DMA2D transfer to LCD configuration */ 
   
  /* Enable the transfer complete, transfer error and configuration error interrupts */
  LL_DMA2D_EnableIT_TC(DMA2D);
  LL_DMA2D_EnableIT_TE(DMA2D);
  LL_DMA2D_EnableIT_CE(DMA2D);  
  
  /* Enable the Peripheral */
  LL_DMA2D_Start(DMA2D);
  
  /*##-4- Wait until DMA2D transfer is over ################################################*/
  while(blended_image_ready == 0) {;}
    
  
  while (1)
  { 
    ; 
  }
}



/**
  * @brief DMA2D configuration.
  * @note  This function Configure tha DMA2D peripheral :
  *        1) Configure the transfer mode : memory to memory
  *        2) Configure the output color mode as RGB565
  *        3) Configure the transfer from FLASH to SRAM   
  *        4) Configure the data size : 240x160 (pixels)  
  * @retval
  *  None
  */
static void DMA2D_Config(void)
{
  /* Configure the DMA2D Color Mode */  
  LL_DMA2D_SetOutputColorMode(DMA2D, LL_DMA2D_OUTPUT_MODE_RGB565);
  
  /* Foreground Configuration:     */
  /* Set Alpha value to full opaque */
  LL_DMA2D_FGND_SetAlpha(DMA2D, 0xFF);
  /* Foreground layer format is RGB565 (16 bpp) */
  LL_DMA2D_FGND_SetColorMode(DMA2D, LL_DMA2D_INPUT_MODE_RGB565);
}

/**
  * @brief  On Error Handler on condition TRUE.
  * @param  condition : Can be TRUE or FALSE
  * @retval None
  */
void OnError_Handler(uint32_t condition)
{
  if(condition)
  {
    BSP_LED_On(LED1);
    while(1) { ; } /* Blocking on error */
  }
}


/**
  * @brief IO initialization.
  * @note  GPIO PH.00 setting to activate STM32L496 Discovery I/Os
  *        and I/O initialization.  
  * @retval None
  */
static void IO_Init(void)
{   
  GPIO_InitTypeDef GPIO_InitStruct;
  

  __HAL_RCC_GPIOH_CLK_ENABLE();
 
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull =   GPIO_NOPULL;
  GPIO_InitStruct.Alternate = 0;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    
  HAL_GPIO_Init( GPIOH, &GPIO_InitStruct ); 
 
  HAL_GPIO_WritePin( GPIOH, GPIO_PIN_0, GPIO_PIN_RESET); 
  
  /* Initialize the IO functionalities */
  BSP_IO_Init();  
}

/**
  * @brief LCD image preparation.
  * @note  Configure image position and size for Discovery STM32L496 LCD
  *        and set LCD in pixel writing mode.
  *        This API must be invoked before transferring the image data to the LCD.  
  * @param  x0: first pixel x position
  * @param  y0: first pixel y position 
  * @param  xSize: image width (in pixels)
  * @param  ySize: image height (in pixels)           
  * @retval None
  */
static void LCD_ImagePreparation(uint16_t x0, uint16_t y0, uint16_t xSize, uint16_t ySize)
{
  /* CASET: Column Address Set */ 
  LCD_IO_WriteReg(ST7789H2_CASET);
  /* Send commands */
  LCD_IO_WriteData(0x00);
  LCD_IO_WriteData(x0);
  LCD_IO_WriteData(0x00);
  LCD_IO_WriteData(x0 + xSize -1);
  /* RASET: Row Address Set */  
  LCD_IO_WriteReg(ST7789H2_RASET);  
  /* Send commands */
  LCD_IO_WriteData(0x00);
  LCD_IO_WriteData(y0);
  LCD_IO_WriteData(0x00);
  LCD_IO_WriteData(y0 + ySize -1); 
    
  /* Prepare to write to LCD RAM */
  LCD_IO_WriteReg(ST7789H2_WRITE_RAM);  
}            

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
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
