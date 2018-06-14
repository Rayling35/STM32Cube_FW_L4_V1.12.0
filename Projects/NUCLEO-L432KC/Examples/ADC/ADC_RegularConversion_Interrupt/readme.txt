/**
  @page ADC_RegularConversion_Interrupt conversion using interrupt

  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    ADC/ADC_RegularConversion_Interrupt/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC RegularConversion interrupt example.
  ******************************************************************************
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
  @endverbatim

@par Example Description 

This example describes how to use the ADC in interrupt mode to convert data through the HAL API.

The ADC1 is configured to convert continuously ADC_CHANNEL_9.

Each time an end of conversion occurs an interrupt is generated and the converted 
data of ADC1 DR register is affected to the uhADCxConvertedValue variable in the 
ADC conversion complete call back function.


Conversion time (reference manual, "Reset and clock control" and "ADC clocks" sections):
  1) the system clock is 80 MHz.
  2) __HAL_RCC_ADC_CONFIG() macro in HAL_ADC_MspInit() API sets the system clock as ADC asynchronous clock source 
  2) ClockPrescaler field of initialization structure is set to ADC_CLOCK_ASYNC_DIV1
     => the input ADC clock is set in asynchronous clock mode   
     => the input ADC clock is the undivided system clock 


  Sampling time is set to ADC_SAMPLETIME_6CYCLES_5 (6.5 cycles).
  ConvTime = Sampling time + 12.5 ADC clock cycles.
           = 19 clock cycles
           = (19 / 80 MHz) = 237.5 ns 
           


Use an external power supply, adjust supply voltage and connect it to pin GPIO_PIN_4 of GPIOA (Arduino pin A3).
This allows to modify ADC_CHANNEL_9 voltage.

STM32 board LED can be used to monitor the conversion:
  - LED3 is ON when there is an error occurs.

@par Directory contents 

  - ADC/ADC_RegularConversion_Interrupt/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - ADC/ADC_RegularConversion_Interrupt/Inc/stm32l4xx_it.h          DMA interrupt handlers header file
  - ADC/ADC_RegularConversion_Interrupt/Inc/main.h                  Header for main.c module  
  - ADC/ADC_RegularConversion_Interrupt/Src/stm32l4xx_it.c          DMA interrupt handlers
  - ADC/ADC_RegularConversion_Interrupt/Src/main.c                  Main program
  - ADC/ADC_RegularConversion_Interrupt/Src/stm32l4xx_hal_msp.c     HAL MSP file 
  - ADC/ADC_RegularConversion_Interrupt/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment 

  - This example runs on STM32L432xx devices.
  
  - This example has been tested with NUCLEO-L432KC RevC board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
