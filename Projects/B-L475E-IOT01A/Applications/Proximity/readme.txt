/**
  @page Proximity  Description of the Proximity application
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    Applications/Proximity/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the Proximity application.
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

@par Application Description

This application shows how to use the VL53L0X sensor mounted on the B-L475E-IOT01A 
board to provide proximity information.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 80 MHz.

This application uses the hyperterminal to display proximity information and to 
get orders from user:

- "N" or "n" to display new proximity
- "Q" or "q" to quit the test


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - BSP/Src/main.c                 Main program
  - BSP/Src/system_stm32l4xx.c     STM32L4xx system clock configuration file
  - BSP/Src/stm32l4xx_it.c         Interrupt handlers 
  - BSP/Src/vl53l0x                Drivers of the vl53l0x sensor
  - BSP/Inc/main.h                 Main program header file  
  - BSP/Inc/stm32l4xx_hal_conf.h   HAL Configuration file
  - BSP/Inc/stm32l4xx_it.h         Interrupt handlers header file

        
@par Hardware and Software environment  

  - This example runs on STM32L475xx devices.
    
  - This example has been tested with STMicroelectronics B-L475E-IOT01A boards.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open an hyperterminal with following setting:
    + COM: STLink Virtual COM Port(COMxxx). This can be found by opening computer
           Device Manager, Port(COM & LPT) once the board is connected to the PC.
    + BaudRate = 115200 baud  
    + Word Length = 8 Bits (7 data bit + 1 parity bit)
    + One Stop Bit
    + Parity none
    + Hardware flow control disabled (RTS and CTS signals)
    + Reception and transmission are enabled in the time
    
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
