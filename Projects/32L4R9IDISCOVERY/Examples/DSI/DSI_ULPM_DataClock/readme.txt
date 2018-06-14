/**
  @page DSI_ULPM_DataClock : enter and exit DSI ULPM Mode on data and clock lanes
  while displaying an RGB888 picture 390x390 in DSI mode Command on LCD screen.

  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    DSI/DSI_ULPM_DataClock/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the LCD DSI enter and exit DSI ULPM Mode on data lane
  *          and clock lane example.
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

This example provides a description of how to use the embedded LCD DSI controller
(using IPs GFXMMU, LTDC and DSI Host) to drive the round LCD mounted on board and
manage entry and exit in DSI ULPM mode on data lane and clock lane. In this mode,
the DSI PHY state machine is entering a low power state on data lane and clock lane.

The DSI Dphy_Clk should be derived from the clock tree PLL.PLLR (ck_plldsi) to allow
a switch off of the PLL DPHY to save power during the ULPM phase.
When exiting from ULPM, the PLL DPHY is first switched back on and locked, then the DSI DPHY will exit
power down and display should operate as before.

In this example a RGB888 picture (390x390) is displayed on LCD in DSI Mode Command
(LED2 is switched on).

On a Joystick SEL button press from the user within 10 seconds, the LCD display will be
switched off.
One second later,  the DSI PHY Data and clock lane will enter ULPM mode (LED2 will
switch off). DphyClk is derived from PLL.PLLR, then DPHY PLL is switched Off.
After 5 seconds in Off mode, the PLL DPHY is switched back on and locked,
then the ULPM on data and clock lanes will be exited in DPHY DSI state machine.
The LCD will be switched back on (LED2 back to on) and the LCD will display the same
image as before.

Ten seconds after the image is displayed, a dimming is initiated with a final LCD display off
after ten more seconds.

In case of error, LED1 will be switched on.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents

  - DSI/DSI_ULPM_DataClock/Inc/stm32l4xx_hal_conf.h      HAL configuration file
  - DSI/DSI_ULPM_DataClock/Inc/stm32l4xx_it.h            Interrupt handlers header file
  - DSI/DSI_ULPM_DataClock/Inc/main.h                    Header for main.c module
  - DSI/DSI_ULPM_DataClock/Inc/image_390x390_rgb888.h    Image 390x390 in RGB888 to display on LCD
  - DSI/DSI_ULPM_DataClock/Src/stm32l4xx_it.c            Interrupt handlers
  - DSI/DSI_ULPM_DataClock/Src/main.c                    Main program
  - DSI/DSI_ULPM_DataClock/Src/stm32l4xx_hal_msp.c       HAL MSP file
  - DSI/DSI_ULPM_DataClock/Src/system_stm32l4xx.c        STM32L4xx system source file

@par Hardware and Software environment

  - This example runs on STM32L4R9xx devices.

  - This example has been tested with STMicroelectronics STM32L4R9I-Discovery
    board and can be easily tailored to any other supported device
    and development board.

  - STM32L4R9I-Discovery Set-up
    - Make sure that round DSI LCD MB1314 is plugged on CN4

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
