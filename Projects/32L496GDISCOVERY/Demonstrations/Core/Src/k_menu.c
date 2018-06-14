/**
  ******************************************************************************
  * @file    k_menu.c
  * @author  MCD Application Team 
  * @brief   This file provides the kernel menu functions 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2017 STMicroelectronics International N.V. 
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
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_MENU
  * @brief Kernel menu routines
  * @{
  */


/* External variables --------------------------------------------------------*/
extern int status;
extern GUI_CONST_STORAGE GUI_BITMAP bmwarning;

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define ID_ICONVIEW_MENU               (GUI_ID_USER + 0x00)

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 WM_HWIN hIcon;
 WM_HWIN hWin ;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  callback routine of main menu.
  * @param  None.
  * @retval None
  */
static void cbWin(WM_MESSAGE * pMsg) {

  /* Animation */
  uint32_t NCode, Id;
  static uint8_t sel = 0;  
  switch (pMsg->MsgId) 
  {      
  case WM_PAINT:
    break;
      
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);     
    NCode = pMsg->Data.v;  
    
    switch (NCode) 
    {  
    case WM_NOTIFICATION_CLICKED:   

      if (Id == ID_ICONVIEW_MENU)
      { 
        sel = ICONVIEW_GetSel(pMsg->hWinSrc);
      }    
      
      break;
      
    case WM_NOTIFICATION_RELEASED:
        if (Id == ID_ICONVIEW_MENU)
        {
          if(sel < 4)
          {
            module_prop[sel].in_use = 1;
            
            module_prop[sel].module->startup(pMsg->hWin, 0, 0);       
            
            sel = 0;
          }
        }      
      
    default:
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  set the GUI profile
  * @param  None.
  * @retval None.
  */
void k_SetGuiProfile(void) 
{
  BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
  DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
  
  FRAMEWIN_SetDefaultTextColor(0, GUI_WHITE);
  FRAMEWIN_SetDefaultTextColor(1, GUI_WHITE);      
  
  FRAMEWIN_SetDefaultBarColor(0, GUI_STCOLOR_LIGHTBLUE);
  FRAMEWIN_SetDefaultBarColor(1, GUI_STCOLOR_LIGHTBLUE);
  
  FRAMEWIN_SetDefaultFont(&GUI_Font32_ASCII);
  
  FRAMEWIN_SetDefaultClientColor(GUI_WHITE);  
  FRAMEWIN_SetDefaultTitleHeight(35);
  FRAMEWIN_SetDefaultTextAlign(GUI_TA_HCENTER);
  
  WINDOW_SetDefaultBkColor(GUI_WHITE);

  GUI_SetDefaultFont(&GUI_Font20_ASCII);
  
  TEXT_SetDefaultTextColor(GUI_STCOLOR_LIGHTBLUE);
  TEXT_SetDefaultFont(&GUI_Font20_ASCII);
}

/**
  * @brief  Initializes the menu.
  * @param  None.
  * @retval None
  */
void k_InitMenu(void) 
{
  uint8_t i = 0;
  
  WM_SetCallback(WM_GetDesktopWindowEx(0), cbWin);
  
  hWin = WM_CreateWindowAsChild(0, 0, LCD_GetXSize(), LCD_GetYSize(), WM_GetDesktopWindowEx(0),
                                WM_CF_SHOW, cbWin, 0);  
  
  hIcon = ICONVIEW_CreateEx(0, 
                            0, 
                            LCD_GetXSize(), 
                            LCD_GetYSize(), 
                            hWin, 
                            WM_CF_SHOW,
                            0,
                            ID_ICONVIEW_MENU, 
                            110, 
                            110);
  
  
  ICONVIEW_SetSpace(hIcon, GUI_COORD_Y, 10);
  ICONVIEW_SetFrame(hIcon, GUI_COORD_Y, 5);
  ICONVIEW_SetSpace(hIcon, GUI_COORD_X, 10);
  ICONVIEW_SetFrame(hIcon, GUI_COORD_X, 5);  
  
  ICONVIEW_SetBkColor(hIcon, ICONVIEW_CI_BK, GUI_BLACK);
    
  for (i = 0; i < 4; i++)
  {
    if (ICONVIEW_AddBitmapItem(hIcon,module_prop[i].module->icon, (char *)module_prop[i].module->name)) {
      Error_Handler();
    }
  }  
}  

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
