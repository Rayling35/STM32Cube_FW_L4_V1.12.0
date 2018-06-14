/**
  @page WriteTag Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    NFC/WriteTag/readme.txt 
  * @author  MCD Application Team
  * @brief   This application writes NDEF messages on M24SR type 4 NFC tag.
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

@par Application Description

This application aims at showing how to write NDEF messages to an M24SR type 4 NFC tag 
so that the associated application is launched on the smartphone when it comes near the NFC antenna.

First the NFC component is initialised, the LED2 goes ON to indicate Initialization is terminated.
Then when the smartphone approches the NFC antenna and action will be taken by the smartphone 
depending on the NDEF message written on the tag.
This example writes a different message each time the USER BUTTON is pressed:
 - URI:    the "www.st.com" website is opened by the browser
 - SMS:    an SMS is prepeaed on the smartphone and ready to be sent to +33612345678
 - EMAIL:  an email is prepeaed on the smartphone and ready to be sent to customer.service@st.com
 - VCARD:  a vCard content from image file is shown on the smartphone display
 - VCARD2: a vCard content from VcardStruct is shown on the smartphone display
 - AAR:    the STM BLE application is opened on the smartphone (downloaded the first time)

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - NFC/WriteTag/Src/main.c                Main program file with several NDEF examples.
  - NFC/WriteTag/Src/system_stm32l4xx.c    STM32L4xx system clock configuration file.
  - NFC/WriteTag/Src/stm32l4xx_it.c        STM32 interrupt handlers (M24SR_GPO and user button).
  - NFC/WriteTag/Inc/stm32l4xx_hal_conf.h  HAL configuration file.
  - NFC/WriteTag/Inc/stm32l4xx_it.h        STM32 interrupt handlers header file.
  - NFC/WriteTag/Inc/VcardCSL1.h           Vcard image format (data array).
  - NFC/Common/                            These files are Common also to other applic/examples then WriteTag.
  - NFC/Common/NDEF_TagType4_lib/          This directory contains a set of source files that write NDEF messages
                                           on M24SR (tag type 4) to be exchanged with smartphone devices.
  - NFC/Common/M24SR/m24sr_wrapper.c       It simplifies the use of the M24SR driver by sequencing some commands.
  - NFC/Common/M24SR/m24sr_wrapper.h       API to M24SR wrapper, called by the middleware NDEF Libs.    
 
@par Hardware and Software environment 

  - This application runs on STM32L475XX devices, B-L475E-IOT01A board (MB1297) 
    
  - This application has been tested with the following environment:
     - B-L475E-IOT01A board. 

  - B-L475E-IOT01A Discovery board Set-up    
    - Connect the Discovery board to your PC with a USB cable type A to mini-B 
      to ST-LINK connector (CN1).
    - Please ensure that the ST-LINK connectors and jumpers are fitted.

  - When using Android Phone
    - Activate "NFC"
    - Default Android application should handle the reading of the NFC tag

@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files and load your image into target memory
  - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
