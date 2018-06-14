/**
  @page RCC_CRS_Synchronization_IT RCC Clock Recovery Service example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    RCC/RCC_CRS_Synchronization_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RCC Clock Recovery Service example.
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

This example describes how to use the RCC HAL API to configure the clock recovery service (CRS)
in Interrupt mode.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 80 MHz.

Then, HSI48 and LSE oscillators are enabled. 
In this example, as a first step a synchronization miss is raised when using a wrong synchronization 
source (GPIO instead of LSE which is not configured). In a 2nd step, a reconfiguration is done to
use LSE and the correct synchronization.

In this test, this is the scenario:
 - set the source to GPIO and then enable IT
 - to provoke a SYNC event, call the software event generation function
 - Interrupt is raised to indicate a SYNC MISS and LED2 remains off
 - in main program, wait for 1 sec and reconfigure source to LSE
 - Toggle quickly LED2 when SYNC WARN is detected
 - Increase tollerance (FELIM value) when SYNC WARN is detected
 - At the end of the test LED2 should stay ON

Note: HSI48 frequency can be checked with oscilloscope using MCO PIN PA.08

@par Directory contents 

  - RCC/RCC_CRS_Synchonization_IT/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - RCC/RCC_CRS_Synchonization_IT/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - RCC/RCC_CRS_Synchonization_IT/Inc/main.h                  Header for main.c module  
  - RCC/RCC_CRS_Synchonization_IT/Src/stm32l4xx_it.c          Interrupt handlers
  - RCC/RCC_CRS_Synchonization_IT/Src/main.c                  Main program
  - RCC/RCC_CRS_Synchonization_IT/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment

  - This example runs on STM32L452xx Devices.
    
  - This example has been tested with NUCLEO-L452RE Rev C board and can be
    easily tailored to any other supported device and development board.    


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
