/**
  @page TIM_OnePulse TIM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/TIM/TIM_OnePulse/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM_OnePulse example.
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

This example shows how to configure a timer to generate a positive pulse in
Output Compare mode with a length of tPULSE and after a delay of tDELAY;
This example is based on the STM32L4xx TIM LL API; peripheral initialization is done
using LL unitary service functions for optimization purpose (performance and size).

The pulse is generated on OC2.

This example uses 2 timer instances:

  - TIM1 generates a positive pulse of 50 us after a delay of 50 us. User push-button
    is used to start TIM1 counter. 
    
                                              ___
                                             |   |
    User push-button ________________________|   |________________________________        
                                                            ___________
                                                           |           |
    OC1              ______________________________________|           |________
    (TIM1_CH1)                                <---50 us---><---50 us--->
                                                |            |_ uwMeasuredPulseLength
                                                |_ uwMeasuredDelay

  TIM1_CH1 delay and pulse length are measured every time a pulse is generated. 
  Both can be observed through the debugger by monitoring the variables uwMeasuredDelay and
  uwMeasuredPulseLength respectively.

  - TIM3 generates a positive pulse of 3 s after a delay of 2 s. TIM3 counter start
    is controlled through the slave mode controller. TI1FP1 signals is selected as
    trigger input meaning that TIM3 counter starts when a rising edge is detected on
    TI1FP1. The TIM3 output channel is mapped on the pin PC.07 (connected to LED1 on board
    NUCLEO-L496ZG (144 pins)). Thus LED1 status (on/off) mirrors the timer output level (active v.s. inactive).

       __________________________     _________________________________________ 
                                 |   |
    TI1                          |___|
    (TIM3_CH1)
        ______________________________________                             ____
                                              |                           |
    OC2                                       |___________________________|
    (TIM3_CH2)                   <-----2s-----><----------3 s------------->
   

Both TIM1 and TIM3 are configured to generate a single pulse (timer counter 
stops automatically at the next update event (UEV).

Connecting TIM1 OC1 to TIM3 TI1 allows to trigger TIM3 counter by pressing
the User push-button.

@par Directory contents 

  - TIM/TIM_OnePulse/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - TIM/TIM_OnePulse/Inc/main.h                  Header for main.c module
  - TIM/TIM_OnePulse/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_OnePulse/Src/stm32l4xx_it.c          Interrupt handlers
  - TIM/TIM_OnePulse/Src/main.c                  Main program
  - TIM/TIM_OnePulse/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L496xx devices.
    
  - This example has been tested with NUCLEO-L496ZG (144 pins) board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L496ZG (144 pins) Set-up:
      - TIM1_CH1  PE.09: connected to pin 4 of CN10 connector  
      - TIM3_CH1  PC.06: connected to pin 1 of CN7 connector 
      - TIM3_CH2  PC.07: connected to pin 11 of CN7 connector 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
