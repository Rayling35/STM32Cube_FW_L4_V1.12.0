/**
  @page PWR_ModesSelection Power Modes Selection Example
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    PWR/PWR_ModesSelection/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power Modes Selection example.
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
 
This example shows how to enter the power mode selected by the user application from an 
Hyperterminal console on a remote Host computer. The objective is to provide a mean to 
measure the power consumption using an amperemeter on IDD connector. 

The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick 
interrupt handler.

@note To measure the current consumption remove JP6 jumper 
      and connect an amperemeter to JP6 to measure IDD current.     

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

  - PWR/PWR_ModesSelection/Inc/stm32l4xx_conf.h         HAL Configuration file
  - PWR/PWR_ModesSelection/Inc/stm32l4xx_it.h           Header for stm32l4xx_it.c
  - PWR/PWR_ModesSelection/Inc/main.h                   Header file for main.c
  - PWR/PWR_ModesSelection/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
  - PWR/PWR_ModesSelection/Src/stm32l4xx_it.c           Interrupt handlers
  - PWR/PWR_ModesSelection/Src/main.c                   Main program
  - PWR/PWR_ModesSelection/Src/lprun_test.c             Low Power RUN mode test
  - PWR/PWR_ModesSelection/Src/lpsleep_test.c           Low Power SLEEP mode test
  - PWR/PWR_ModesSelection/Src/run_range1_test.c        RUN mode in range 1 test
  - PWR/PWR_ModesSelection/Src/run_range2_test.c        RUN mode in range 2 test
  - PWR/PWR_ModesSelection/Src/shutdown_test.c          SHUTDOWN mode test
  - PWR/PWR_ModesSelection/Src/sleep_range1_test.c      SLEEP mode in range 1 test
  - PWR/PWR_ModesSelection/Src/sleep_range2_test.c      SLEEP mode in range 2 test
  - PWR/PWR_ModesSelection/Src/standby_rtc_sram2_test.c STANDBY mode with RTC and SRAM2 preserved test
  - PWR/PWR_ModesSelection/Src/standby_rtc_test.c       STANDBY mode with RTC test
  - PWR/PWR_ModesSelection/Src/standby_test.c           STANDBY mode test
  - PWR/PWR_ModesSelection/Src/stop1_mroff_rtc_test.c   STOP1 mode with RTC but Regulator OFF test
  - PWR/PWR_ModesSelection/Src/stop1_mroff_test.c       STOP1 mode with Regulator OFF  test
  - PWR/PWR_ModesSelection/Src/stop2_rtc_test.c         STOP2 mode with RTC test
  - PWR/PWR_ModesSelection/Src/stop2_test.c             STOP2 mode test

@par Hardware and Software environment

  - This example runs on STM32L4xx devices

  - This example has been tested with STMicroelectronics NUCLEO-L496ZG (144 pins)
    board embedding a low-speed clock LSE and can be easily tailored to any other 
    supported device and development board.

  - NUCLEO-L496ZG (144 pins) set-up:
    - LED1 connected to PC.07 pin
	  - LPUART1 interface connected to ST-LINK

  - HyperTerminal setup of COM port associated to STLink Virtual COM Port:
    - Baud rate = 115200 
    - Data = 8 bit
	- Parity = none
    - Stop = 1 bit
    - No hardware flow control

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
