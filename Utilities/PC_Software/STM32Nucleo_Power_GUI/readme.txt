/**
  @page Demo_Binary   Description of the STM32 Nucleo Power GUI tool
  
  @verbatim
  ******************************************************************************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the STM32 Nucleo Power GUI tool.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
   @endverbatim

@par Description

This directory contains the STM32 Nucleo Power GUI tool and the binaries that
must be used on the Nucleo boards when running this tool.
 
The STM32 Nucleo Power GUI tool connects to the STM32 Nucleo hardware boards 
supported by the firmware package. It allows selecting the various low-power modes 
and benchmarking codes thanks to the available binary files. Users can therefore 
quickly assess STM32L4 low-power performance.

 + Using "STM32 Nucleo Power GUI tool"    
    - Connect the STM32 Nucleo board to a PC with a 'USB type A to Micro-B' 
      (Nucleo-144) or 'USB type A to Mini-B' (Nucleo-64) cable through USB 
      connector CN1 to power the board.
    - Select the wanted binary and reprogram the STM32 Nucleo firmware 
      (ex. STM32 ST-LINK Utility, available for download from www.st.com).
      Once done, to ensure all IOs are at their reset levels, unplug then plug
      the board again. 
    - Connect an amperemeter to the IDD jumper (JP5 for Nucleo-144, JP6 for Nucleo-64).      
    - Unzip "Nucleo GUI.zip" on your laptop or desktop and launch Qtserial.exe.
    - Obey the instructions appearing on the screen in connecting to the COM port
      associated with the Nucleo board.
    - Pick one low power mode proposed among those by the GUI tool and press
      "Confirm".
    - Measure the MCU power consumption on the amperemeter.
    - Reset the board before picking up another low power mode.  
    
    
 + Binaries are available under "Binaries" folder:
      - NUCLEO-L433RC-P.hex for STM32L433RC Nucleo board with external SMPS
      - NUCLEO-L452RE.hex for STM32L452RE Nucleo board without external SMPS
      - NUCLEO-L452RE-P.hex for STM32L452RE Nucleo board with external SMPS      
      - NUCLEO-L476RG.hex for STM32L476RG Nucleo board
      - NUCLEO-L496ZG.hex for STM32L496ZG Nucleo board without external SMPS
      - NUCLEO-L496ZG-P.hex for STM32L496ZG Nucleo board with external SMPS
      - NUCLEO-L4R5ZI.hex for STM32L4R5ZI Nucleo board without external SMPS
      - NUCLEO-L4R5ZI-P.hex for STM32L4R5ZI Nucleo board with external SMPS              

          
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
