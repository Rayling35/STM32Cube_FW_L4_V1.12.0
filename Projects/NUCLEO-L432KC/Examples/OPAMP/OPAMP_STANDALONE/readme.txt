/**
  @page OPAMP_STANDALONE Amplify an applied signal example  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    OPAMP/OPAMP_STANDALONE/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the OPAMP standalone signals generation example.
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

This example shows how to configure OPAMP peripheral in standalone mode. The gain 
in this mode can be set externally (external gain setting mode). 

  
   OPAMP1 is configured as following:
   - Standalone OPAMP mode is configured (as VINM is connected to OPAMP1_VOUT, OPAMP then
     operates as in follower mode (external follower)).
   - Non Inverting input is connected to DAC_OUT1 (sinevawe).
   - OPAMP Output is available on OPAMP1_VOUT (sine wave signal).
   - Use a Jumper between Arduino GND and D2 pins to switch from
     normal power mode to low power mode.
      
    
@par Directory contents 

  - OPAMP/OPAMP_STANDALONE/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - OPAMP/OPAMP_STANDALONE/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - OPAMP/OPAMP_STANDALONE/Inc/main.h                  Header for main.c module  
  - OPAMP/OPAMP_STANDALONE/Src/stm32l4xx_it.c          Interrupt handlers
  - OPAMP/OPAMP_STANDALONE/Src/main.c                  Main program
  - OPAMP/OPAMP_STANDALONE/Src/stm32l4xx_hal_msp.c     HAL MSP file
  - OPAMP/OPAMP_STANDALONE/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment  
  
  - This example runs on STM32L432xx devices.
    
  - This example has been tested with NUCLEO-L432KC RevC board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L432KC RevC Set-up
    
    - Connect with a wire PA.01 (OPAMP_VINM) from Arduino A1 (connector CN4) to 
      PA.03 (OPAMP_VOUT) from Arduino A2 (connector CN4).
    - Connect an oscilloscope to PA.03 (OPAMP_VOUT) from Arduino A2 (connector CN4) 
      to display waveform (OPAMP output). 
      The OPAMP voltage output is same as VINP in both normal et low power mode. 
    - In order to start test, connect a jumper between Arduino GND and D2 (connector CN3). 
      Then disconnect/connect this jumper to alternate from normal and low power mode
      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

