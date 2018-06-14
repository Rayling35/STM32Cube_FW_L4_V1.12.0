/**
  @page PWR_STOP0_SMPS Power Stop 0 SMPS Mode Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_STOP0_SMPS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power STOP0 SMPS Mode example.
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
 
This example shows how to enter Stop 0 mode with or without SMPS enabled and to wake up 
from this mode using an interrupt.

In the associated software, the system clock is set to 80 MHz, an EXTI line
is connected to the user button thru PC.13 and configured to generate an 
interrupt on falling edge upon key press.
The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick 
interrupt handler, LED4 is toggled in order to indicate whether the MCU is in STOP 0 mode 
or RUN mode.

After start-up, the system automatically runs at 80 MHz without SMPS.
After some transitions the system ends up in RUN mode at 80 MHz, external SMPS is on,
Voltage Scale Range is 2.

The User push-button can be pressed to alternatively move from step 1 to step 2
described below
1�) MCU is in RUN SMPS R2 mode at 80 MHz
2�) MCU is in STOP 0 mode
Note that step 1�) is maintained for at least 10 seconds.

The 2 steps can be repeated in an infinite loop.

Two compilation switches are provided in main.c for illustration purposes:

- Compilation switch NO_DELAY_TOWARDS_SMPS ensures fast transitions to SMPS mode. 
  User can disable this switch to observe more easily the different transitions 
  leading to SMPS.
  By default, NO_DELAY_TOWARDS_SMPS is enabled.

- Compilation switch DISABLE_SMPS de-activates SMPS feature when MCU is in low power 
  mode. Power consumption is then that of MCU without external SMPS. At wake-up, SMPS
  feature is re-activated again to reach RUN SMPS R2 mode at 80 MHz, meaning a longer
  wake-up time to reach SMPS on.
  By default, DISABLE_SMPS is disabled.


LED4 is used to monitor the system state as follows:
 - LED4 ON: configuration failed (system will go to an infinite loop)
 - LED4 toggling: system in RUN mode
 - LED4 OFF : system in STOP 0 mode


@note To measure the current consumption, please connect an amperemeter to JP6.

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

  - PWR/PWR_STOP0_SMPS/Inc/stm32l4xx_conf.h         HAL Configuration file
  - PWR/PWR_STOP0_SMPS/Inc/stm32l4xx_it.h           Header for stm32l4xx_it.c
  - PWR/PWR_STOP0_SMPS/Inc/main.h                   Header file for main.c
  - PWR/PWR_STOP0_SMPS/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
  - PWR/PWR_STOP0_SMPS/Src/stm32l4xx_it.c           Interrupt handlers
  - PWR/PWR_STOP0_SMPS/Src/main.c                   Main program

@par Hardware and Software environment

  - This example runs on STM32L452xx devices.
    
  - This example has been tested with 
    STMicroelectronics NUCLEO-L452RE-P MB1319B (64 pins).

  - NUCLEO-L452RE-P MB1319B (64 pins) set-up:
    - Use LED4 connected to PB.13 pin
    - User push-button connected to pin PC.13 (External line 13)

    
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Disconnect toolchain 
 - Unplug the USB cable
 - Connect Amperemeter between the 2 pins of JP5 (IDD).
 - Plug the USB (starts the example)

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
