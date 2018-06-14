/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : SIMConf.c
Purpose     : Windows Simulator configuration
---------------------------END-OF-HEADER------------------------------
*/
/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
#ifdef WIN32

#include <windows.h>
#include <stdio.h>

#include "LCD_SIM.h"
#include "GUI_SIM_Win32.h"
//#include "Sim.h"

  /*******************************************************************
  *
  *       Static data
  *
  ********************************************************************
  */
static int _Pressed = 0;

/*******************************************************************
*
*       Static code
*
********************************************************************
*/
/*******************************************************************
*
*       _cbShutDown
*
* Function description
*   Callback for the shutdown-key
*/
static void _cbShutDown(int key, int state) {
	GUI_USE_PARA(key);
	if (state && !_Pressed) {

		_Pressed = state;
	}
	else if (!state && _Pressed) {
		//
		// Exit emWin simulation
		//
		SIM_GUI_Exit();
		exit(0);
	}
}

/*******************************************************************
*
*       _cbScreenShot
*
* Function description
*   Callback for the shutdown-key
*/
static void _cbScreenShot(int key, int state) {
	GUI_USE_PARA(key);
	if (state) {

		//SIM_GUI_SaveCompositeBMP();
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       SIM_X_Config
*
* Purpose:
*   Called during the initialization process in order to configure
*   the simulator.
*/
void SIM_X_Config() {
  //
  // Set callback routine for hardkey
  //
  SIM_HARDKEY_SetCallback(0, _cbShutDown);
  SIM_HARDKEY_SetCallback(1, _cbScreenShot);

  SIM_GUI_SetTransColor(0x0000FF);     // Define the transparent color
  SIM_GUI_SetTransMode(0, /*GUI_TRANSMODE_PIXELALPHA*/GUI_TRANSMODE_ZERO);
  SIM_GUI_UseCustomBitmaps();
  SIM_GUI_SetLCDPos(10, 10);
}

#else

void SIMConf_C(void); // Avoid empty object files
void SIMConf_C(void) {}

#endif

/*************************** End of file ****************************/
