/**
  @page BLE HeartRate  BLE HeartRate application

  @verbatim
  ******************************************************************************
  * @file    BLE/HeartRate/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the BLE HeartRate application
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

This application shows how to use BLE component for HeartRate profile application.

The STM32 B-L475E-IOT01A Discovery board acts as GATT server.
Once the code is downloaded on the STM32 B-L475E-IOT01A Discovery board and executed,
the modules are initialized and the device starts advertising. 
The user needs an application (running for example on smartphone) in order to act as GATT client.
ST provides the following application (STM32 BLE Profiles):
https://play.google.com/store/apps/details?id=com.stm.bluetoothlevalidation
Tip:
To quickly download and launch the "STM32 BLE Profiles" application the NFC tag can be used.
By executing the NFC example (available in /Applications/NFC/WrAARtoRunBLEapp/) the NFC EEPROM 
is programmed (and it remains programmed) such that, each time the smartphone approches the NFC 
antenna, the "STM32 BLE Profiles" application is automatically launched on the smartphone.

The user should activate Bluetooth Smart, execute such application, and SCAN for Bluetooth devices.
The device HR_L475_IoT will be detected.
The user should connect the smartphone to the STM32 B-L475E-IOT01A.
The presence of HeartRate profile should be detected by the smartphone application.
The user should click on the Heart Rate profile (this depends on the smartphone application used).
In general any smartphone application should allow the user to see the heart Rate measurement.
STM32 BLE Profiles smartphone application displays and expresses them in BPM (beat per minute).
In this example HR_L475_IoT Discovery sends dummy values each second.

The STM32 B-L475E-IOT01A example supports the full feature of Heart Rate Service as from specification
https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.heart_rate.xml
i.e. it provides other information like the sensor location and by writing 0x1 to the Heart Rate Control point
the Energy Expanded field is reset.
STM32 BLE Profiles smartphone application does not support these options but other smartphone applications 
can be found on the internet and used to test these features.


@par Directory contents

 - BLE/HeartRate/Src/main.c                   Main Program
 - BLE/HeartRate/Src/system_stm32l4xx.c       STM32L4xx system clock configuration file
 - BLE/HeartRate/Src/stm32l4xx_it.c           STM32 interrupt handlers
 - BLE/HeartRate/Src/hr.c                     Heart Rate application
 - BLE/HeartRate/Src/hrs_app.c                Heart Rate Service Application
 - BLE/HeartRate/Src/dis_app.c                Device Information Service Application
 - BLE/HeartRate/Inc/config.h                 Application configuration file
 - BLE/HeartRate/Inc/stm32l4xx_hal_conf.h     HAL configuration file
 - BLE/HeartRate/Inc/stm32l4xx_it.h           STM32 interrupt handlers header file
 - BLE/HeartRate/Inc/hr.h                     Exported files and function of hr.c 
 - BLE/HeartRate/Inc/hrs_app.h                Exported files and function of hrs_app.c 
 - BLE/HeartRate/Inc/dis_app.h                Exported files and function of dis_app.c 
 - BLE/Common/                                These files are Common also to other applic/examples then HeartRate
 - BLE/Common/ble_core/*.*                    BlueNRG-MS Bluetooth Low Energy device driver 
 - BLE/Common/ble_services/*.*                GATT services according to BLE spec
 - BLE/Common/debug/*.*                       Code usefull for debugging (DBG should be activated in config.h)
 - BLE/Common/tl/*.*                          HCI layer and SPI protocol    
 - BLE/Common/hw/*.*                          HW board and device dependencies (SPI pins, timeserver, low power) 
 - BLE/Common/utilities/*.*                   Scheduler, memory/queue/fifo/list management, otp, etc   

@par Hardware and Software environment

  - This application runs on STM32L475XX devices, B-L475E-IOT01A board (MB1297) 
    
  - This application has been tested with the following environment:
     - B-L475E-IOT01A board. 

  - B-L475E-IOT01A Discovery board Set-up    
    - Connect the Discovery board to your PC with a USB cable type A to mini-B 
      to ST-LINK connector (CN1).
    - Please ensure that the ST-LINK connectors and jumpers are fitted.
  
  - When using Android Phone
    - Activate Bluetooth
    - Install a BLE application supporting HeartRate service, e.g.:
      https://play.google.com/store/apps/details?id=com.stm.bluetoothlevalidation 
    - SCAN for bluetooth devices and connect to HR_L475_IoT

@par How to use it ? 
   
In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
