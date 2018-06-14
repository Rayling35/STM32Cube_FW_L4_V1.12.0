/**
  @page PWR_STANDBY_SMPS Power Standby SMPS Mode Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_STANDBY_SMPS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power Standby SMPS Mode example.
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
 
This example shows how to enter SMPS Standby mode and wake up from this mode using 
an interrupt.

In the associated software, the system clock is set to 80 MHz, an EXTI line
is connected to the user button thru PC.13 and configured to generate an 
interrupt on falling edge upon key press.

After start-up, 

1) The system automatically runs at 80 MHz without SMPS at R1.

2) After some transitions the system enters INTO RUN with 
  external SMPS R2 at 80 MHz (A).3) 
  
3) then stays 10 seconds before entering standby mode.

4) And stays in standby mode until push-button is pressed. When push-button is pressed 
   goes back to 2) and 3) 

etc.
  
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

  - PWR/PWR_STANDBY_SMPS/Inc/stm32l4xx_conf.h         HAL Configuration file
  - PWR/PWR_STANDBY_SMPS/Inc/stm32l4xx_it.h           Header for stm32l4xx_it.c
  - PWR/PWR_STANDBY_SMPS/Inc/main.h                   Header file for main.c
  - PWR/PWR_STANDBY_SMPS/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
  - PWR/PWR_STANDBY_SMPS/Src/stm32l4xx_it.c           Interrupt handlers
  - PWR/PWR_STANDBY_SMPS/Src/main.c                   Main program
  - PWR/PWR_STANDBY_SMPS/Src/stm32l4xx_hal_msp.c      HAL MSP module

@par Hardware and Software environment

  - This example runs on STM32L496xx devices
    
  - This example has been tested with STMicroelectronics NUCLEO-L496ZG-P MB1312/S (144 pins)
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-L496ZG-P (144 pins) set-up:
    - Use LED1 and LED2 connected respectively to PC.07 and PB.07 pins
    - User push-button connected to pin PC.13 (External line 13)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Disconnect toolchain 
 - Unplug the USB cable
 - Connect Amperemeter between the 2 pins of JP5 (IDD).
 - Plug the USB (starts the example)
 

Option:
 - Fast transition towards SMPS 
   in main.c uncomment the following line
   // #define NO_DELAY_TOWARDS_SMPS        1
   Comment 
   // #define NO_DELAY_TOWARDS_SMPS        1
   allows clearer step transitions.

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
