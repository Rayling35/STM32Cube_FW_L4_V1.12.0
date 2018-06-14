/**
  @page PWR_SHUTDOWN PWR shutdown example
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    PWR/PWR_SHUTDOWN/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR SHUTDOWN example.
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
 
This example shows how to enter the system in SHUTDOWN mode and wake-up from this
mode using external RESET or WKUP pin.

In the associated software, the system clock is set to 80 MHz.
The SysTick is programmed to generate an interrupt each 1 ms.

After a reset (or wake-up from SHUTDOWN mode), LED3 is ON and MCU is in RUN mode.
The system enters SHUTDOWN mode after 5s, LED3 is OFF.
A rising edge on wakeup pin WKUP1 PA.00 (Arduino A0) will wake-up the system from SHUTDOWN.
Alternatively, an external RESET of the board will lead to a system wake-up as well.
The LED3 blinks once in order to indicate the system was resumed from Shutdown mode.
These steps are repeated in an infinite loop.
    

@note This example can not be used in DEBUG mode due to the fact 
      that the Cortex-M4 core is no longer clocked during low power mode 
      so debugging features are disabled.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - PWR/PWR_SHUTDOWN/Inc/stm32l4xx_conf.h         HAL Configuration file
  - PWR/PWR_SHUTDOWN/Inc/stm32l4xx_it.h           Header for stm32l4xx_it.c
  - PWR/PWR_SHUTDOWN/Inc/main.h                   Header file for main.c
  - PWR/PWR_SHUTDOWN/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
  - PWR/PWR_SHUTDOWN/Src/stm32l4xx_it.c           Interrupt handlers
  - PWR/PWR_SHUTDOWN/Src/main.c                   Main program
  - PWR/PWR_SHUTDOWN/Src/stm32l4xx_hal_msp.c      HAL MSP module

@par Hardware and Software environment

  - This example runs on STM32L432xx devices

  - This example has been tested with STMicroelectronics NUCLEO-L432KC RevC
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-L432KC RevC Set-up
    - LED3 connected to PB.03 pin.
    - Put a wire between PA.00 (Arduino A0) and 5V pin to generate a rising edge on PWR_WAKEUP_PIN1.
    - To measure the current consumption in SHUTDOWN mode, remove jumper JP1 
      and connect an amperemeter to measure IDD current. 
    

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
