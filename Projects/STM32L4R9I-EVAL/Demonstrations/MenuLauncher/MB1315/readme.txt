/**
  @page Demo MB1313
 
  @verbatim
  ******************************************************************************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   Description of MB1313 Demonstration
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

@par Demonstration Description

The STM32Cube demonstration platform comes on top of the STM32Cube(TM) as a firmware
package that offers a full set of software components based on a modular architecture.
All modules can be reused separately in standalone applications.
All these modules are managed by the STM32Cube demonstration kernel that allows to
dynamically add new modules and access common resources (storage, graphical
components and widgets, memory management, real-time operating system).
The STM32Cube demonstration platform is built around the FreeRTOS real-time operating
system and offers a large scope of use cases based on the STM32Cube HAL BSP and several
middleware components.

The demonstration's executables STM32Cube_Demo-STM32L4R9I-EVAL_MB1314-V1.0.0.hex or 
STM32Cube_Demo-STM32L4R9I-EVAL_MB1315-V1.0.0.hex can be flashed to the target using 
the ST-Link Utility. Depending on which LCD board MB1314 or MB1315 is used the user has
to select the corresponding hex file when programming the target. 

The demonstation can run on both MB1314 and MB1315 respectively rectangular and
round LCDs.


Multimedia content is also available in the SDCard folder within the demonstration package and is
to be copied on the SD card using the host PC. Below is the listing of these additional files.

Audio files :
\---
   |   Dublin Forever.wav
   |   Gardenss 22KHz.wav
   |   Love Letters.wav
   |
   +---Electronica
   |       album_art.bmp
   |       Dubstep.wav
   |       Scifi.wav
   |       ScifiTwo.wav
   |
   +---Empty
   |       empty_folder.txt
   |
   +---Jazz
   |       album_art.bmp
   |       Love.wav
   |       The Jazz Piano.wav
   |
   +---NoCover
   |       Audio Sample.wav
   |
   \---Rock
           album_art.bmp
           Clear Day.wav
           Little Idea.wav 


Firmware files:
  MB1314_STEW_firmware.bin            STemWin Binary firmware for MB1314 LCD
  MB1314_STEW_resources.bin           STemWin Binary resources for MB1314 LCD
  MB1314_TGFX_firmware.bin            Touch GFX Binary firmware for MB1314 LCD
  MB1314_TGFX_resources.bin           Touch GFX Binary resources for MB1314 LCD
  MB1314_EWIZ_firmware.bin            Embedded Wizard Binary firmware for MB1314 LCD
  MB1314_EWIZ_resources.bin           Embedded Wizard Binary resources for MB1314 LCD

  MB1315_STEW_firmware.bin            STemWin Binary firmware for MB1315 LCD
  MB1315_STEW_resources.bin           STemWin Binary resources for MB1315 LCD
  MB1315_TGFX_firmware.bin            Touch GFX Binary firmware for MB1315 LCD
  MB1315_TGFX_resources.bin           Touch GFX Binary resources for MB1315 LCD
  MB1315_EWIZ_firmware.bin            Embedded Wizard Binary firmware for MB1315 LCD
  MB1315_EWIZ_resources.bin           Embedded Wizard Binary resources for MB1315 LCD

After connection of the LCD on the board, either the MB1315 or the MB1314,
the demonstration starts by displaying an animation with the ST logo and goes
into the Menu Launcher screen where the user can select between three demonstrations,
that's one demonstration per graphics stack: STemWin, TouchGFX and Embedded Wizard.
When a Sub-Demo is selected, the Menu Launcher will check if the firmware and resources
are already existing in both internal and external flashes then if exist it will jump
to the selected Sub-Demo otherwise a popup message is displayed requesting a confirmation
to load the suitable firmware and resources. After confirmation the MenuLauncher starts
loading the firmware and resources binaries into repectively the internal flash and the
octospi memories, a progress bar is shown to follow the loading progress.

Once loading is terminated, the binary Sub-Demo is started.

@note: each Sub-Demo has to load its firmware and resources separately if not already done.
@note: depending on the Sub-Demo, resource loading may take several minutes.


I- MB1314
===========
Within the launcher, the user selects which demonstration to run by sweeping the bottom of the
screen and pressing on the selected graphics stack logo. The sections below describe the features
of each demonstration.


STemWin
=======

The STemWin demonstration features the following modules:

  - Clock faces
  - Audio player
  - Audio recorder
  - Power measurements
  - Information
  - Reset

 + Clock faces
 ----------------
The module display the current time and date. The user can customize the clock face by double-tapping
on the clock main view. Doing so brings in a carousel view with four clock faces and a settings menu
to configure the time, date and to set alarms. The user has to swipe through the carousel and tap on
the selected face to set the new clock face.

 + Audio player
 ----------------
This module enables playing .WAV audio files, as provided with the accompanying SD card. The user starts
by double-tapping on the player screen to get into the module's main view then press the previous, next
and play icons to go through the available audio files (enumerated from the SD card) and to start the playback.
The audio player displays the duration and the progress within the song as playback goes on. It's also possible
to toggle on/off auto-repeat and shuffle functionalities by tapping on the icons at the bottom of the screen.
The user can go back to the main menu by tapping on the Back icon.

 + Audio recorder
 ----------------
This module enables recording audio samples via the built-in microphones and saving these on the SD card.
The user has to double-tap on the recorder front screen to get into the module's main view and where the
recorder has already started capturing ambient audio. The use can save the captured audio to the SD card
in real-time by tapping on the save icon. The file listing icon on the right displays the list of the audio
content captured and stored on the SD card.

 + Power measurements
 -------------------------
This module enables measuring the MCU power consumption in various execution modes. The user starts by double-tapping
the screen to start interacting with the module. By then the user can select between the execution modes by tapping
on the left and right icons and then start the benchmarking run by pressing the middle run icon. Execution modes
include Run, Sleep, LP Run, LP Sleep, Stop, Standby and Shutdown modes. For each run, the module configures the MCU
for the respective execution mode and relies on the MFX chip to measure the consumed power which is then displayed
onscreen. The module temporarily turns off the screen (and other peripherals) while measuring the power.

 + Information icon
 -------------------------
This module displays the following information:
  The CPU speed
  The board name
  The MCU core
  The demonstration firmware version

   + Reset
 -------------------------
This module allow returning back to the Menu Launcher
  ST Logo Splash Screen should not appear when back to MenuLauncher from here


Embedded Wizard
=================

The Embedded Wizard demonstration features the following modules:
 
  Running
  Watch
  Info
  'Back' icon

 + Running 
 -------------------------
 This module displays several graphic submenus related to activity monitoring (measures, 
 heart bit, statistics, map ...).
 
 + Watch
 -------------------------
 This module provides different kinds of watch displays.

 + Info
 -------------------------
 This module yields several information on Embedded Wizard experience.
 
 + 'Back' icon
 -------------------------
 Pressing this icon allows to immediately come back to the initial menu.  
 
 

TouchGFX
======== 
 
Reduced and Full TouchGFX demonstration are described in the same section.
Both demonstrations provide the same set of applications but the full demonstration
offers more graphic elements (e.g. waveforms in the background when audioplayer is
running, more different watch displays, more activity monitoring sub menus...)


 + Audio player
 ----------------
This module allows to play various *.wav stored on the SD card.
While playing audio, to move from one audio album to another, stop playing the audio first.

 + Game
 -------------------------
This "Bird" game stresses the gain provided by the Chrom-ART IP. Pressing the "ST"
button enables/disables this IP and the CPU load, displayed in real time, allows
to check the hw IP gain in real time.

 + Watch
 -------------------------
This module provides different kinds of watch displays.

 + Power measurements
 -------------------------
This module enables measuring the MCU power consumption in various execution modes. The user selects the target
execution mode by swiping between the available mode, which include Run, Sleep, LP Run, LP Sleep, Stop, Standby
and Shutdown, then taps on the selected mode to start the benchmarking run. For each run, the module configures the MCU
for the respective mode and relies on the external MFX chip to measure the consumed power which is then displayed
onscreen. The module temporarily turns off the screen (and other peripherals) while measuring the power.

 + Heartbeats
 -------------------------
This module displays several graphic submenus related to different activity monitoring
(measures and statistics).

 + 'Back' icon
 -------------------------
Pressing this icon allows to immediately come back to the initial menu.


II- MB1315
==========

the launcher the user can either select a demonstation to run or display the
info about the system.


Info
=====
In the launcher main screen, the user can press the "i" icon to show or hide
the system info window. The info contains:
- the STM32 family (STM32L4R9I)
- the Board on which the demonstation is running (STM32L4R9I-EVAL)
- the CPU Frequency (120 MHz)
- the FW version (V1.0.0)


STemWin
=======

The STemWin demonstation offers the following modules:

  - Audio player
  - Audio recorder
  - Home alarm
  - Garden control
  - Games
  - Benchmark
  - USB device
  - System info

+ Audio player
----------------
This module allows playing .wav files. The files are fetched from the uSD.
When the user presses the "audio player" icon, a mediaplayer interface is
displayed with the lists of tracks, .wav files, extracted from the uSD. The
user can:

- Play pause stop a tack
- switch between tracks
- Adjust the volume level on-fly or mute it compeletly
- Run the equilizer to customize the sound output
- Choose to add a file to the playlist
- Choose to add an entire folder to the playlist
- Toggle on/off the auto-repeat feature for one or all files
- Make the audio player run in background, that he can select to run another
  application


+ Audio Recorder
-----------------
The module allows the user to record a sound track via the embedded
microphones, save it to a file into the uSD and replay it.
To start recording, the user needs to press the record button, on pressed
a counter is displayed to show the time elapsed since the start.
To save the recording the user should press the stop button.
Once saved, it is possible to replay the track and hear it using a headset
it is possible also, when playing the track, to pause/resume it via the pause
play button.

+ Home alarm
------------ 
Control of Home alarm system, equipped with cameras.
Static picture shown when a room is selected and then the camera icon pressed
General room alarm activation/deactivation when pressed.

+ Gardening control
-------------------
The gardening control module provides a graphic garden watering system behaviour

+ Games
---------
The game coming in the STM32Cube demonstration is based on the Reversi game. It is a
strategy board game for two players, played on an 8×8 board. The goal of the game is to
have the majority of disks turned to display your color when the last playable empty square
is filled.

+ Benchmark
------------
This module is intended to show the system performace regarding the GFX 2D
drawing. when The user presses the "Start Speed Benchmark", a test drawing
random-sized colorized rectangles for some seconds then the application gets
back to the main screen with a score, in "Pix/s", idisplayed in the right side
of the screen and the CPU usage "%" updated in the left side.

+ USB Device
--------------
This modules allows the user to connect the STM32L4R9_Eval board as a USB device into the PC
and explore the uSD plugged into the EVAL board.
Before  running the module, the user must connect the board to a PC via a 'USB micro B-Male to A-Male'
cable to the connector CN3.
After starting the application, the main screen shows:
- An image giving the status of the USB cable (green if connected and red if not)
- An image about the uSD status (green if connected and red if not)
- A Button with the label "Connect USB"

when the user presses the "Connect USB" button, the PC detects the board as
"EVAL_L4R9AI" volume and mounts the uSD as a removable disk.
It is then possible to access the uSD as a normal storage device, with read
write delete and even format action.

+ System Info
--------------  
The system info module provides information about the core, supported eval boards, 
CPU speed and demonstration version.


TouchGFX
=========

This Sub-Demo  offers the following sub-demos
 - Custom controls
 - Easing Equtions
 - TouchGFX Presentation
 - Graphs and Pie charts

All subdemos above start when the user presses the "DEMO" button on the main screen

+ Custom control
----------------

Upon Custom controls demonstration pick up, the following icons show up:
 An up and down norrows for:
  - Air pressure Gauge
  - Scan progress bar
  - Percentage progress bar
  - Date item picker
  - 'Return' button

 In the various modules two "up" and "down" narrows placed on the left side of the LCD display
 to move from one custum control  to another.

 ++ Air pressure Gauge
 -----------------------
 This Custom control exemple allows to visualize air pressure in gauge format.Show a simulated air presure gauge.

 ++ Scan progress bar
 ----------------------
 This Custom control exemple allows to demonstrate data flow when the user press the scan spot on the middle of the LCD Display.
When the scan is completed, the user is notified when the scan is completed (text message displayed on screen).
A new rescan can be relented


 ++ Percentage progress bar
 ---------------------------
 This Custom control exemple allows to visualize percentage on the progress bar when the user's finger move along.


 ++ Date item picker
 --------------------
This Custom control exemple allows to pick a date from the select item on the LCD Display. Scroll through
 the various proposed day, month and year to choose one.


 ++ 'Return' button
 --------------------
 Pressing this button allows to immediatly come back to the initial menu.

+ Easing Equtions
------------------

When the Easing Equtions demonstration starts, the following icons show up on scroll list along the screen left side:

  - Back
  - Bounce
  - Circular(Cir.)
  - Cubic
  - Elastic
  - Exponential
  - Linear
  - Quadratic
  - Quartic
  - Quintic
  - Sinusoidal
  - 'Return' button

Every exemple from the folowing can run in three modes Ease In, Ease Out or Ease In/Out on the bottom center side of the screen.

 ++ Back
 --------
 This Easing Equtions exemple displays ball position curve mouvement over time in back mode.

 ++ Bounce
 ----------
 This Easing Equtions exemple displays ball position curve mouvement over time in Bounce mode.

 ++ Circular
 -----------
 This Easing Equtions exemple ball position curve mouvement over time in Circular mode.

 ++ Cubic
 -----------
 This Easing Equtions exemple displays ball position curve mouvement over time in Cubic mode.

 ++ 'Return' button
 --------------------
 Pressing this button  allows to immediatly come back to the initial menu.


Embedded Wizard
==================
This Sub-Demo offers the following sub-demos:
 - Climate Cabinet
 - Washing Machine
 - Paper Cutter
 - Waveform Generator
 - Graphics Accelerator


In each demonstration, on the top left side home button to go back to the lancher menu.
An arrow in the buttom center side of the display once clicked a pop up display will appear
to show information about GUI development.On click the luncher menu appear. 

+ Climate Cabinet
------------------

Upon Climate Cabinet demonstration pick up, the following scrolling list show up:
 An up and down sliding for:
  - 'Temperature and Humidity' button
  - 'Dwell Time' button
  - 'Heating and Cooling' Time button
  - 'Start' button

 ++ 'Temperature and Humidity' button
 ------------------------------------
 This option allows to adjust temperature and humidity parameters.

 ++ 'Dwell Time' button
 -----------------------
 This option allows to adjust dwell time parameters.


 ++ 'Heating and Cooling Time' button
 ------------------------------------
 This option allows to adjust Heating and Cooling parameters.

 ++ 'Start' button
 ------------------
 Pressing this button allows to immediatly start the demonstration.

+ Washing Machine
-------------------

Upon Washing Machine demonstration pick up, the following icons show up on scroll list along the screen left side :

  - Program
  - Temperature
  - U/min
  - Options
  - Finish
  - 'Start' button

When this demostration is selected, five column table containing different options of the waching machine, every column
is a scrolling list.

 ++ Program
 -----------
 Contain seven diffrent modes: Hot/Clolored Wash, Easy Care, Delicates, Sportwear, WoolHandwash, Eco, Drain or Spin.

 ++ Temperature
 ---------------
 This option allows to fix temperature fo the washing, it goes between cold and 95 degree.

 ++ Finish
 -----------
 This option allows to set uo the duration for the washing period.

 ++ 'Start' button
 -----------------
 Pressing this button  allows to immediatly come back to the initial menu.

+ Paper Cutter
--------------
Upon Paper Cutter demonstration pick up, four options are available:
  - Feed
  - Speed
  - Output Format
  - Batch
  - 'Start' button

 ++ Feed
 --------
 This custum contains four diffrent options;pinfeed perforated, pinfeed non-perforated, pinless perforated and pinless non-perforated.
 Once one of the four options is selected, click on the green circular green 'OK' button to save the choice.
 To cancel the choice, on the buttom right size, click on the cancel button.  

 ++ Speed
 ----------
 This custum allows to control paper generation speed, User can choose from 600 to 3600 paper  speed per hour.
 Two arrows placed on the top center side of the screen to fix the speed of produced papers.
 Once  selected, click on the green circular green 'OK' button to save the choice.
 To cancel the choice, on the buttom right size, click on the cancel button.

 ++ Output Format
 -----------------
 This custum allows to choose the size of th paper, different din paper formats are available from A3 to A8 on the right side of the screen,
 On the left side a graphical representation of the paper which user can manualy pick his preferred din paper format. 
 Once wanted dimension selected, click on the green circular green 'OK' button to save the choice.
 To cancel the choice, on the buttom right size, click on the cancel button.

 ++ Batch
 ---------
 This custum allows to control number of paper to produce,by adjusting from 10 to 1000 user can produce a custum paper number.
 Two arrows placed on the top center side of the screen to fix the number of produced papers.
 
 ++ 'Start' button
 -------------------
 Pressing this button on the left bottom side allows to immediatly come back to the initial menu.


++ Waveform Generator
-----------------------
 Upon Waveform Generator demonstration pick up, A waveform graph  is loaded to the screen display on the left side
 contains oscilations from two input chanels.
 On the right side of the display a scolling list for the two input chanels containing two slider to calibrate the frequency,
 the amplitude and different oscilations formats(sine, square,ramp or white noise wave) for the user to choose between them.


 
++ Graphics Accelerator
------------------------
 Upon Graphics Accelerator demonstration pick up, a graphical demonstration of diffrent shapes is lunched; Alpha8 Blend, Bitmap Copy,
 Rectagle Blend or rectange Copy.
 The following buttons show up:

  - 'Next' button
  - 'on/off' button
 On the right side of the screen many features are visible like how many frames per secon(FPS) oàr how much the CPU is loaded
 and the name of the shape palying in the demonstration.
 
 ++ 'Next' button
 ------------------
 When this button is clicked a random graphical shapes are generated different from the previous.


 ++ 'on/off' button
 -------------------
 Pressing this button  allows to activate or disactivate Chrom-ART.
 
@note the application doesn't reuqire uSD to run
@note the application starts automatically when left without interaction for
      some time


@par Hardware and Software environment

 1 - The jumpers configuration is as follows:
     JP1 fitted in 1-2 position (VDD_USB connected to VDD_MCU)
     JP2 fitted in 1-2 position (VDDA connected to VDD_MCU)
     JP4 fitted in 1-2 position (Allowing to measure its own current consumption.)
     JP5 fitted in 2-3 position (COMP2)
     JP8 fitted in 1-2
     JP9 fitted in 1-2
     JP10 fitted in 1-2
     JP14 fitted in 1-2
     JP15 fitted in 2-3
     JP16 fitted in 2-3 (DFSDM to enable recording)
     JP11 fitted in 5-6
     JP3 ON
     JP6 OFF
     JP12 OFF (CAN_RX enable)
     JP13 ON (CAN Termination resistor)
     CN4 OFF
     CN10 ON

 2 - Open STM32 STM32 ST-LINK Utility v4.1.0.3, click on "External Loader" from the bar menu 
     then check "MX25LM51245G_STM32L4R9I-EVAL" box

     Connect the STM32L4R9I_EVAL board to PC with USB cable through CN21
     Use the demonstration STM32Cube_Demo-STM32L4R9I_EVAL_MB1315-V1.0.0.hex binary file with the
     ST-Link Utility to program both internal Flash and external OSPI memory.

 3 - Copy the audio files from "\Utilities\Media\Audio" and the binary files provided
     under "Binary\SDCard" folder within the demonstration package in the SD card (root directory)
     and insert the SD card into CN8 connector

 4 - Fit on the MB1313 the suitable LCD screen: the MB1314 for round LCD demo or the MB1315 for
     rectangular LCD demo.
 
 5 - Run the demonstration

  - This demonstration runs on STM32L4R9Ixx devices.

  - This application has been tested with STM32L4R9I-EVAL board (MB1313-revB) and can be
    tailored to any other supported device and development board.

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
