/**
  @page STemWin_SampleDemo Readme file
 
  @verbatim
  ******************************************************************************
  * @file    STemWin_SampleDemo/readme.txt 
  * @author  MCD Application Team
  * @brief   
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

This application shows how to implement a sample demonstration example allowing 
to show some of the STemWin Library capabilities.

The list of modules to be used is configured into the file Demo/GUIDEMO.h

At the first run, after power OFF/ON, a touch screen calibration is needed: in
order to do this, user is just requested to follow the displayed instructions.
Then all the demo modules are run sequentially. Throughout the demonstration, a
control frame window is displayed at the bottom right of the touch screen, including
a progress bar.
To skip a demo and immediatly jump to the next one, user has just to touch the LCD screen.

LED1 and LED2 are continuously toggling to indicate that the Demo runs properly.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - STemWin/STemWin_SampleDemo/Inc/GUIConf.h                       Header for GUIConf_stm32l496g_discovery.c
  - STemWin/STemWin_SampleDemo/Inc/LCDConf_stm32l496g_discovery.h  Header for LCDConf_stm32l496g_discovery.c
  - STemWin/STemWin_SampleDemo/Inc/GUIDEMO.h                       Header for GUI demo  
  - STemWin/STemWin_SampleDemo/Inc/stm32l4xx_hal_conf.h            HAL configuration file
  - STemWin/STemWin_SampleDemo/Inc/stm32l4xx_it.h                  Interrupt handlers header file
  - STemWin/STemWin_SampleDemo/Inc/main.h                          Header for main.c module
  - STemWin/STemWin_SampleDemo/Src/calibration.h                   TouchScreen calibration header file
  - STemWin/STemWin_SampleDemo/Src/rtc.h                           Real Time Clock setting header file       
  - STemWin/STemWin_SampleDemo/Src/stm32l4xx_it.c                  Interrupt handlers
  - STemWin/STemWin_SampleDemo/Src/rtc.c                           Real Time Clock setting source file
  - STemWin/STemWin_SampleDemo/Src/GUIConf_stm32l496g_discovery.c  Display controller initialization
  - STemWin/STemWin_SampleDemo/Src/LCDConf_stm32l496g_discovery.c  Configuration file for the GUI library
  - STemWin/STemWin_SampleDemo/Src/main.c                          Main program
  - STemWin/STemWin_SampleDemo/Src/system_stm32l4xx.c              STM32L4xx system source file
  - STemWin/STemWin_SampleDemo/Src/calibration.c                   TouchScreen calibration source file 
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_AntialiasedText.c      Text antialising source file    
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Automotive.c           Sub-demo automative source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_BarGraph.c             Sub-demo bar graph source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Bitmap.c               Sub-demo bit map source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_ColorBar.c             Sub-demo color bar source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Conf.c                 Sub-demo configuration source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Cursor.c               Sub-demo cursor source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Fading.c               Sub-demo fading source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Graph.c                Sub-demo graph source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_IconView.c             Sub-demo icon view source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_ImageFlow.c            Sub-demo image flow source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Intro.c                Sub-demo introduction source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Listview.c             Sub-demo list view source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_RadialMenu.c           Sub-demo radial menu source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Resource.c             Sub-demo graphic resource source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Skinning.c             Sub-demo image skinning source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Speed.c                Sub-demo speed source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Start.c                Sub-demo start source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_TransparentDialog.c    Sub-demo cdialog box source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_Treeview.c             Sub-demo tree view source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_VScreen.c              Sub-demo virtual screen source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_WashingMachine.c       Sub-demo washing maching source file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_ZoomAndRotate.c        Sub-demo graphic effects source file
                                                    
@par Hardware and Software environment

  - This example runs on STM32L496xx devices.
    
  - This example has been tested with STM32L496G-Discovery board and can be
    easily tailored to any other supported device and development board.      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files: Project->Rebuild all
 - Load project image: Project->Download and Debug
 - Run program: Debug->Go(F5) 


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
