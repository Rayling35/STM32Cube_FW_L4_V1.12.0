/**
  @page OSPI_RAM_ExecuteInPlace OSPI HyperRAM execute in place example
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    OSPI/OSPI_RAM_ExecuteInPlace/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the code execution from OSPI HyperRAM memory example.
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

This example describes how to execute a part of the code from the OSPI HyperRAM memory. To do this, 
a section is created where the function is stored.

At the startup, the OSPI HyperRAM is configured in memory-mapped mode and the data are copied from the initialization
section of the flash to the OSPI HyperRAM memory. And finally the code in executed in a forever loop.

LED1, LED2, LED3 and LED4 toggle in a forever loop.
LED_RED is on as soon as an error is returned by HAL API, and no more LED toggles.

In this example, HCLK is configured at 120 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - OSPI/OSPI_RAM_ExecuteInPlace/Src/main.c                 Main program
  - OSPI/OSPI_RAM_ExecuteInPlace/Src/system_stm32l4xx.c     STM32L4xx system clock configuration file
  - OSPI/OSPI_RAM_ExecuteInPlace/Src/stm32l4xx_it.c         Interrupt handlers 
  - OSPI/OSPI_RAM_ExecuteInPlace/Src/stm32l4xx_hal_msp.c    HAL MSP module
  - OSPI/OSPI_RAM_ExecuteInPlace/Inc/main.h                 Main program header file  
  - OSPI/OSPI_RAM_ExecuteInPlace/Inc/stm32l4xx_hal_conf.h   HAL Configuration file
  - OSPI/OSPI_RAM_ExecuteInPlace/Inc/stm32l4xx_it.h         Interrupt handlers header file

        
@par Hardware and Software environment  

  - This example runs on STM32L4R9xx devices.
    
  - This example has been tested with STMicroelectronics STM32L4R9I_EVAL
    boards and can be easily tailored to any other supported device 
    and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
