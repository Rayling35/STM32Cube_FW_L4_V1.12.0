/**
  @page HID_Standalone_BCD USB Device Humain Interface (HID + BCD) example
  
  @verbatim
  ******************************************************************************
  * @file    USB_Device/HID_Standalone_BCD/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB HID BCD example.
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

This example describes how to use the BCD feature based on the USB HID device application on the STM32L4xx devices.
 
The STM32L432xx device integrated battery charger detection circuitry supports USB-IF Battery 
Charger Detection, BCD,(revision 1.2). The hpcd.Init.battery_charging_enable in the usbd_conf.c 
should be set to 1 to enable the support for BCD.

This example is part of the USB Device Library package using STM32Cube firmware.

This is a typical example on how to use the STM32L432xx USB FS Device peripheral where the STM32 MCU is
enumerated as a HID device using the native PC Host HID driver to which the STM32 nucleo 
board is connected, 

Battery charger detection will begin automatically when VBUS is detected. The STM32L432xx include the 
capability to detect various USB battery chargers and can detect a range of USB battery chargers including a Standard Downstream
Port (SDP), a Charging Downstream Port (CDP), and a Dedicated Charging Port (DCP). For more information
on USB battery charger detection, please see the USB Battery Charging Specification, Revision 1.2 (Note 1).

If a DCP is connected (D+/D- are shorted or connected through 200 ohm resistor)
In CDP case we used a HP dock Station: charging port

@note LED 3 is ON when the BCD contact is detected (one of SDP,CDP or DCP)

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick. The user is 
provided with the SystemClock_Config()function to configure the clock (SYSCLK).
In this application the system clock is set to 48MHz.

The 48 MHz clock for the USB can be derived from one of the two following sources:
  � PLL clock(clocked by the HSE): If the USB uses the PLL as clock source.
  � RC48 Clock (HSI48): The HSI48 clock is generated from an internal 48 MHz RC oscillator, coupled with
    the clock recovery system (CRS). 
    The CRS allows automatic trimming of the internal HSI48, synchronized with USB SOF signal at 1KHz rate, 
    to guarantee its optimal accuracy over the whole device operational range.    
User can select USB clock from HSI48 or PLL through macro defined in main.h
(USE_USB_CLKSOURCE_CRSHSI48 and USE_USB_CLKSOURCE_PLL).

@note LED 3 is toggling in case of system clock error.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL configuration.
      
@note To reduce the example footprint, the toolchain dynamic allocation is replaced by a static allocation
      by returning the address of a pre-defined static buffer with the HID class structure size. 
      
For more details about the STM32Cube USB Device library, please refer to UM1734 
"STM32Cube USB Device library".
      
@par Directory contents

  - USB_Device/HID_Standalone_BCD/Src/main.c                  Main program
  - USB_Device/HID_Standalone_BCD/Src/system_stm32l4xx.c      STM32L4xx system clock configuration file
  - USB_Device/HID_Standalone_BCD/Src/stm32l4xx_it.c          Interrupt handlers
  - USB_Device/HID_Standalone_BCD/Src/usbd_conf.c             General low level driver configuration
  - USB_Device/HID_Standalone_BCD/Src/usbd_desc.c             USB device HID descriptor
  - USB_Device/HID_Standalone_BCD/Inc/main.h                  Main program header file
  - USB_Device/HID_Standalone_BCD/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - USB_Device/HID_Standalone_BCD/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - USB_Device/HID_Standalone_BCD/Inc/usbd_conf.h             USB device driver Configuration file
  - USB_Device/HID_Standalone_BCD/Inc/usbd_desc.h             USB device MSC descriptor header file  

	
@par Hardware and Software environment

  - This example runs on STM32L432xx devices.
  - This demo has been tested with NUCLEO-L432KC RevC board and can be
    easily tailored to any other supported device and development board.

  - Since there is no USB 2.0 Full speed connector (Type B) on the nucleo board, user has to make 
    his own USB shield daughter board with the a USB connector and plug it on top of the  CN13 
    connectors of the STM32L432KC-Nucleo. The USB connector has to be connected to the USB device associated GPIOs
    as follows:
    - DP (D+ of the USB connector) <======> PA12 (Nucleo board)
    - DM (D- of the USB connector) <======> PA11 (Nucleo board)
    - VBUS oof the USB connector <======> PA9 ( Nucleo board)
    - GND of the USB connector <======> GND ( Nucelo board)
    To improve EMC performance (noise immunity and signal integrity), it is recommended to connect a 100nF
	ceramic capacitor to the USB VDD pin.
      
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
  