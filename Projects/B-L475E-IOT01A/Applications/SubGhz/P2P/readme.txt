/**
  @page Point-to-Point communication example using SubGhz module on B-L475E-IOT01A

  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics ********************
  * @file    P2P/readme.txt
  * @author  MCD Application Team
  * @brief   This application is an example to show a Point-to-Point 
             communication between two nodes using B-L475E-IOT01A discovery boards 
  *******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
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
  *******************************************************************************
  @endverbatim

@par Application Description 

  This application aims at demonstrating point-to-point communication between two
  B-L475E-IOT01A boards with SubGhz module using Spirit1 driver and STM32Cube firmware. 
 
  How to play the example:
  - Power-up the two nodes (B-L475E-IOT01A boards)
  - The LED LD2 on STM32 B-L475E-IOT01A Discovery board board starts to blink
  - User can press user button (Blue Colour) on any of the STM32 Discovery boards; 
     This causes a command packet to be sent from the node (Node1) to the other 
     node (Node2).
  - The successful communication with the other node will cause the LED LD1 on 
      B-L475E-IOT01A to blink on the receiving node (Node2)
  - The receiving node (Node2) will acknowledge the command by sending an RF 
     packet and this can be seen by blink of LED LD1 on B-L475E-IOT01A of 
     the Node1 
 
  To summarise:
    *1*  User presses User Button on Node1
    *2*  Node1  ----------- RF Command packet ------>   Node2
    *3*    Success = LED LD1 on Node2 Blinks
    *4*  Node1  <---------- Ack packet --------------   Node2             
    *5*    Success = LED LD1 Blinks on Node1

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - SubGhz/P2P/Src/main.c                Main program
  - SubGhz/P2P/Src/system_stm32l4xx.c    STM32L4xx system clock configuration file
  - SubGhz/P2P/Src/stm32l4xx_it.c        STM32 interrupt handlers (radio EXTI and user button)
  - SubGhz/P2P/Src/clocks_and_power.c    Clock config and Low Power modes
  - SubGhz/P2P/Src/p2p_app.c             P2P application
  - SubGhz/P2P/Inc/stm32l4xx_hal_conf.h  HAL configuration file
  - SubGhz/P2P/Inc/stm32l4xx_it.h        STM32 interrupt handlers header file
  - SubGhz/P2P/Inc/clocks_and_power.h    API for the function defined in clocks_and_power.c 
  - SubGhz/P2P/Inc/p2p_app.h             Defines and compilation flags for different running modes
  - SubGhz/Common/                       These files are Common also to other applic/examples then P2P
  - SubGhz/Common/spsgrf.c/h             SPSGRF component driver
  - SubGhz/Common/spsgrf_app.c/h         Wrapper to simplify the use of the SPSGRF driver
  - SubGhz/Common/spsgrf_io.c/h          GPIO and SPI bus operation used by the SPSGRF driver

@par Hardware and Software environment

  - This application runs on STM32L475XX devices, B-L475E-IOT01A board (MB1297) 
    
  - This application has been tested with the following environment:
     - B-L475E-IOT01A board. 

  - B-L475E-IOT01A Discovery board Set-up    
    - Connect the Discovery board to your PC with a USB cable type A to mini-B 
      to ST-LINK connector (CN1).
    - Please ensure that the ST-LINK connectors and jumpers are fitted.
     
  - User can select desired P2P features in p2p_app.h file located 
     @SubGhz/P2P/Inc/p2p_app.h

     /******* Platform definition : Uncomment the IoT board Type to be used ****/
     #define SPSGRF_EU		   /* EU frequencies range (IOT01A2) */
     // #define SPSGRF_US          /* US frequencies range (IOT01A1) */	
     /**************************************************************************/

     /************************Set the Node address******************************/ 
     /*Source address of one node should be destination for other node & vice-versa*/   
     #define MY_ADDRESS                  0x44//0x34//
     #define DESTINATION_ADDRESS         0x44//0x44// 
     /**************************************************************************/
    
     /*************************Uncomment the the protocol to be used************/
     //#define USE_STack_PROTOCOL
     #define USE_BASIC_PROTOCOL

     #if defined(USE_STack_PROTOCOL)
     //#define USE_STack_LLP  /*Uncomment if LLP featured need to be used*/
     #endif

     #ifdef USE_BASIC_PROTOCOL
     #define CSMA_ENABLE  /* Comment this line to disable the CSMA */
     #endif
     /**************************************************************************/

@par How to use it ? 

In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - Open your preferred toolchain (IAR, Keil, System Workbench for STM32) 
    the project for the required STM32 IoT Discovery board
 - Rebuild all files and load your image into target memory.
 - Run the application.
  

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
