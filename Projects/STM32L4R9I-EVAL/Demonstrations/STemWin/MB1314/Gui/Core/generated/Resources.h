/**
  ******************************************************************************
  * @file    Resources.h
  * @author  MCD Application Team
  * @brief   common resources
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
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

#ifndef GUI_COMMON_RESOURCES_H__
#define GUI_COMMON_RESOURCES_H__

/*********************************************************************
*
*       Includes
*
**********************************************************************
*/
#include <stdlib.h>

#include "GUI.h"

/*********************************************************************
*
*       Exported constants
*
**********************************************************************
*/
#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/*********************************************************************
*
*       Exported variables
*
**********************************************************************
*/

/*** Bitmaps ***/

/*** Genereted bitmaps used by all modules ***/

extern GUI_CONST_STORAGE GUI_BITMAP bmbackground;
extern GUI_CONST_STORAGE GUI_BITMAP bmround_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmreflection_cover;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_back;
extern GUI_CONST_STORAGE GUI_BITMAP bmback_button_bkg;
extern GUI_CONST_STORAGE GUI_BITMAP bmmodule_entry_icon;

/*** Genereted Fonts used by all modules ***/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontLucidaSansUnicode25;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRoboto_C_Regular35;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRoboto_C_regular100;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRoboto_Light31;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRoboto_Light100;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoC_bold22;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoC_regular22;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoCn_bold27;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoCondensed_light25;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoRegular50;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontRobotoCnBold48;

#endif  /* Avoid multiple inclusion */
/*************************** End of file ****************************/
