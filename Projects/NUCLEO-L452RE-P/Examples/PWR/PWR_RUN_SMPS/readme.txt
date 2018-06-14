/**
  @page PWR_RUN_SMPS Power Mode Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_RUN_SMPS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power RUN SMPS Mode example.
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
 
This example shows how to use SMPS in RUN mode & compare power consumption
gain with use of SMPS feature.

In the associated software, the system clock is set to 80 MHz, an EXTI line
is connected to the user button thru PC.13 and configured to generate an 
interrupt on falling edge upon key press.
The SysTick is programmed to generate an interrupt each 1 ms.


After start-up, the user has five seconds to press the user button.
If the user button is pressed, at the end of the 5-second period, the MCU moves to 
RUN mode @ 80 MHz, SMPS on, power voltage scale 2.
If the user button is not pressed during that time, at the end of the 5-second 
period, the MCU remains in RUN mode @ 80 MHz, SMPS off, power voltage scale 1.  

The five-secong long period is indicated to the user by LED4 which is blinking
during that time.


LED4 is used to monitor the system state as follows:
 - LED4 ON:       configuration failed (system will go to an infinite loop)
 - LED4 toggling: 5-second long period on-going, during which the user can
                  press the user button to activate SMPS
 - LED4 off:      system in RUN mode (with or without SMPS)


@note To measure the current consumption, please connect an amperemeter to JP6.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      

@par Directory contents 

  - PWR/PWR_RUN_SMPS/Inc/stm32l4xx_conf.h         HAL Configuration file
  - PWR/PWR_RUN_SMPS/Inc/stm32l4xx_it.h           Header for stm32l4xx_it.c
  - PWR/PWR_RUN_SMPS/Inc/main.h                   Header file for main.c
  - PWR/PWR_RUN_SMPS/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
  - PWR/PWR_RUN_SMPS/Src/stm32l4xx_it.c           Interrupt handlers
  - PWR/PWR_RUN_SMPS/Src/main.c                   Main program

@par Hardware and Software environment

  - This example runs on STM32L452xx devices
    
  - his example has been tested with 
    STMicroelectronics NUCLEO-L452RE-P MB1319B (64 pins)
    board and can be easily tailored to any other supported device 
    and development board.

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
 - Wait 10 seconds and measure power consumption (A: 80 MHz RUN R1).
 - Reset board (using reset button)
 - Press user button within 5 seconds (while led1 is togling) for SMPS 
 - Wait 10s and start measuring power consumption (B: 80 MHz RUN R1)

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
