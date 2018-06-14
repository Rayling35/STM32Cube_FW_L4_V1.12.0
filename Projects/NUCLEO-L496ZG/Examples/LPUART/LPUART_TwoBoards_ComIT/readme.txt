/**
  @page LPUART_TwoBoards_ComIT LPUART Two Boards Communication IT example

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    UART/LPUART_TwoBoards_ComIT/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the LPUART Two Boards Communication IT example.
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

This example describes a LPUART transmission (transmit/receive) in interrupt mode
between two boards.

Board: NUCLEO-L496ZG (144 pins) (embeds a STM32L496ZGT6 device)
Tx Pin: PB.11 (pin 18 on CN12)
Rx Pin: PB.10 (pin 25 on CN12)
   _________________________                       _________________________ 
  |           ______________|                     |______________           |
  |          |LPUART        |                     |        LPUART|          |
  |          |              |                     |              |          |
  |          |           TX |_____________________| RX           |          |
  |          |              |                     |              |          |
  |          |              |                     |              |          |
  |          |              |                     |              |          |
  |          |           RX |_____________________| TX           |          |
  |          |              |                     |              |          |
  |          |______________|                     |______________|          |
  |                         |                     |                         |
  |                         |                     |                         |
  |                      GND|_____________________|GND                      |
  |_STM32_Board 1___________|                     |_STM32_Board 2___________|



Two identical boards are connected as shown on the picture above.
Board 1: transmitting then receiving board
Board 2: receiving then transmitting board

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 80 MHz.

The user presses the User push-button on board 1.
Then data are transmitted through LPUART1 in IT mode. 2nd board has configured LPUART1
to receive data in IT mode. Once data received is completed, 2nd board also 
transmit same characters on LPUART1 which will be received by 1st board.
Both boards compare transmitted data to received ones. If they are same,
LED1 is turned on, else LED1 is turned off.

Warning: As both boards do not behave same way, "TRANSMITTER_BOARD" switch 
compilation exists to determine either software is for 1st transmitter board or 
2nd receiver (then transmitter) board. In other words, 1st board has to be 
flashed with software compiled with switch enable, 2nd board has to be flashed 
with software compiled with switch disable.

LED1 can be used to monitor the transfer status:
 - LED1 turns ON on master board waiting User push-button to be pressed.
 - LED1 turns OFF on master board waiting the transmission process complete.
 - LED1 turns ON when the transmission/reception process is correct.
 - If there is an initialization or transfer error, LED1 is slowly blinking (1 sec. period).

The LPUART is configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits (7 data bit + 1 parity bit)
    - One Stop Bit
    - None parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Reception and transmission are enabled in the time

@note LPUART instance used and associated resources can be updated in "main.h"
file depending hardware configuration used.

@note When the parity is enabled, the computed parity is inserted at the MSB
position of the transmitted data.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - LPUART/LPUART_TwoBoards_ComIT/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - LPUART/LPUART_TwoBoards_ComIT/Inc/stm32l4xx_it.h          IT interrupt handlers header file
  - LPUART/LPUART_TwoBoards_ComIT/Inc/main.h                  Header for main.c module  
  - LPUART/LPUART_TwoBoards_ComIT/Src/stm32l4xx_it.c          IT interrupt handlers
  - LPUART/LPUART_TwoBoards_ComIT/Src/main.c                  Main program
  - LPUART/LPUART_TwoBoards_ComIT/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - LPUART/LPUART_TwoBoards_ComIT/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L496xx devices.
    
  - This example has been tested with NUCLEO-L496ZG (144 pins) and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L496ZG (144 pins) set-up
    - Connect a wire between 1st board PB.11 (pin 18 on CN12) pin (LPUART Tx) and 2nd board PB.10 (pin 25 on CN12) pin (LPUART Rx).
    - Connect a wire between 1st board PB.10 (pin 25 on CN12) pin (LPUART Rx) and 2nd board PB.11 (pin 18 on CN12) pin (LPUART Tx).
    - Connect 1st board GND to 2nd Board GND.
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
