/**
  @page WiFi_Client_Server es WiFi module in TCP Client mode demonstration
  
  @verbatim
  ******************************************************************************
  * @file    readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Es_WIFI Module in TCP Client mode.
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

This application shows how to use the Es-WiFi module to perform a TCP client mode
using STM32Cube HAL. It demonstrates how to set up a client program and connect it 
to a TCP server.

The Inventek eS-WiFi module is offered with a complete TCP/IP stack and requires 
only a simple AT command over the SPI interface to communicate with the module.

In a typical embedded application, the STM32 microcontroller is used to send the 
AT command to initiate a client connection. 

The es-wifi module starts to connect to an access point. Once connected, we should 
connect to a specific server. The address of the server is declared in RemoteIP[] 
in main.c.
Then, the es-wifi module will be initiated as a client and connected to the server and 
will check the connection. 8002 is the standard port number used for access.
If connection is successful, the client sends a message "STM32:Hello!" 
to the server.
While connection by the client is still alive, the server and client can communicate. 

If the USART is used to output a message on hyperterminal(#define TERMINAL_USE in 
main.c), log messages will be displayed on Hyperterminal to inform user about 
es_wifi module status and the IP address value, else this will be ensured by LEDs:
  + LED2 On: error connection.

This application may be used with a Smartphone (more detailed setup
instructions are described in section "Hardware and Software environment").

@par Directory contents
 - WiFi/WiFi_Client_Server/Inc/main.h                 eader for main.c module
 - WiFi/WiFi_Client_Server/Inc/stm32l4xx_hal_conf.h   HAL configuration file
 - WiFi/WiFi_Client_Server/Inc/stm32l4xx_it.h         STM32 interrupt handlers header file
 - WiFi/WiFi_Client_Server/Src/main.c                 Main Program
 - WiFi/WiFi_Client_Server/Src/system_stm32l4xx.c     STM32L4xx system clock configuration file
 - WiFi/WiFi_Client_Server/Src/stm32l4xx_it.c         STM32 interrupt handlers
 - WiFi/Common/Src/es_wifi.c                          Implementation of the ES_WIFI_XXX() API.
 - WiFi/Common/Src/es_wifi_io.c                       Implementation of the ES_WIFI_IO_XXX() API.
 - WiFi/Common/Src/wifi.c                             Implementation of the WIFI_XXX() API.
 - WiFi/Common/Inc/es_wifi.h                          Header for the functions and defines used by the es_wifi.c 
 - WiFi/Common/Inc/es_wifi_io.h                       Header for the functions and defines used by the es_wifi_io.c   
 - WiFi/Common/Inc/wifi.h                             Header for the functions and defines used by the wifi.c   

@par Hardware and Software environment

  - This application runs on STM32L475XX devices.
    
  - This application has been tested with the following environment:
     - B-L475E-IOT01A Rev-C board. 
 
 - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal. 
    A virtual COM port will then appear in the HyperTerminal. 

  - Hyperterminal configuration:
    - Data Length = 7 Bits
    - One Stop Bit
    - Parity None
    - BaudRate = 115200 baud
    - Flow control: None 

  - Using Android Phone
    - Configure a phone as Access Point
    - Connect another phone to this Network
    - Update in main.c the following defines SSID and PASSWORD with your own AP settings
    - Open TCP Server application already installed on the smartphone (link: https://play.google.com/store/search?q=tcp%20server&c=apps&hl=en )
    - Get the IP address of the server and update the RemoteIP variable in main.c
    - Set server port number to 8002 and press create server
 
In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Check that DK board is connected to a remote PC before running the application
 - Run the application

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
