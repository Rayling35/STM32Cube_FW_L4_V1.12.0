/**
 ******************************************************************************
 * @file    DispTools.h
 * @author  MCD Application Team
 * @brief   Header file for functions for creating MMI on a terminal.
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


#ifndef __DISP_TOOLS_H__
#define __DISP_TOOLS_H__

#include "common.h"

/*
 ************************************************************************
 * *****    Define & Macro declaration.                 *****
 ************************************************************************
 */

  /* Errors definition */
#define CONSOLE_MENU_NO_ERR 0
#define CONSOLE_MENU_USART_ERR 1

#define MAX_MENU 10                  /* Max number of Menu that can be created */

#undef                  FALSE
#undef                  TRUE
#define     FALSE           0
#define     TRUE            1
// -- For Menu Management --
#define     HOME            0x00FE
#define     EXIT            0x00FF
#define     SIGN            16
#define     DEL             0x7F
#define     BKSP            0x08

#define     RIGHT           0xC3
#define     LEFT            0xC4
#define     UP              0xC1
#define     DOWN            0xC2
#define     ESC             0x1b
#define     ENTER           0x0d

#define     MAX_BUFF_SIZE   80
#define     MAX_TAB_CONV    22

// -- For Menu Display --
#define   RECREATE                      1
#undef    DISPLAY
#define   DISPLAY             2
#undef    CAPTURE
#define   CAPTURE             4
#undef    REFRESH
#define   REFRESH             8
#define   CAPTURE_NON_BLOCKING          16
#define   DRAW_WINDOW                   32

/* Flag in MSB byte of returned Item number of RunMenu API. Used  to indicate User Action */

#define ESC_FLAG   0x100
#define ENTER_FLAG 0x200
#define ITEM_CHANGED 0x400


// -- For Title Display --
#define   BLOCK_RESULT  0x01
#define   TESTCASE_RESULT 0x02
#define   SUBTEST_RESULT  0x03


// -- For ReadPcStr function --
#define     INS             0
#define     OVERSTK         1

// -- For Memory Test Functions --
#define   ACCESS_8    0
#define   ACCESS_16   1
#define   ACCESS_32   2


// -- For ReadPcStr function --
#define     SNUM            1
#define     UNUM            2


// -- For PrintCrt, PrintPcCrt function --
#define     FREE_FLAG            1
#define     BUSY_FLAG            2

#define MAXCOLNB      8 // max column
#define MAXITEMNB     50  // max items in table


/*
 ************************************************************************
 * *****    Structure & Enum declaration.           *****
 ************************************************************************
 */

/**
 ******************************************************************************
 * @typedef POINT_T
 * @author  Gilles Spinelli
 * @brief   Describe a point on display terminal : X (or col) & Y (or line).
 ******************************************************************************
 **/
typedef struct point
{
  uint8_t line;     //!< Line or Y position on display.
  uint8_t col;      //!< Column or X position on display.
} POINT_T;


enum _type_menu
{
  TOGGLE = 1,     //!< Toggle and store value. Value (U16) can be 0 or 1.
  SEL_NUM,      //!< SELECTBOX and store value. Value (U16) between 0 to N.
  SEL_TXT,      //!< SELECTNUMBERBOX and store value. Value (U16) between 0 to N.
  STRTAB,     //!< Display string from table (no edit). Value (U16) between 0 to N.
  NUM16,      //!< GETNUMBER and store value. Number entry on (U16).
  NUM32,      //!< GETNUMBER and store value. Number entry on (U32).
  VAL16,      //!< (U16) Number display. Inactive cell
  VAL32,      //!< (U32) Number display. Inactive cell
  SVAL32,     //!< (S32) Number display. Inactive cell.
  TITLE,      //!< Display Item & Msg on a Inactive cell. (U16).
  ACTION,     //!< Display Item & Msg on an Active cell. No direct action. (U16).
  FUNCT       //!< Run function.
};


/**
 ******************************************************************************
 * @typedef STRUCTMENU
 * @author  Gilles Spinelli
 * @brief   Describe Menu.
 ******************************************************************************
 **/
typedef struct
{
  char *Item;     //!< Pointer on ASCII chain, display on Menu before "select arrow".
  void *Var;      //!< Pointer on variable to display/get, in function of "Type" Value.
  int8_t Type;      //!< Type of Menu line. Describe in "_type_menu" enum.
  void *Msg;      //!< Pointer on SelectBox, or ASCII chain that display on Menu after "select arrow".
} STRUCTMENU_T;

typedef struct
{
  void *MinValue;   // Minimum allowed value
  void *MaxValue;   // Maximum allowed value
} STRUCTRANGE_T;

typedef struct
{
  void *CapValue;   // Minimum allowed value
  void *MinValue;   // Minimum allowed value
  void *MaxValue;   // Maximum allowed value
} STRUCTCAPTUREVAL_T;

/*
 ************************************************************************
 * *****    Global Functions declaration.           *****
 ************************************************************************
 */

uint16_t UartTransmitStr (char *StrToDisp);

void ConsoleMenu_Init (void);
int8_t CreateMenu(STRUCTMENU_T * menu, uint8_t x, uint8_t y, int8_t flag, int8_t menuhandle);
uint16_t DisplayMenu (char *menu[], uint8_t lineNumb, uint8_t x, uint8_t y);
uint16_t RunMenu(uint8_t MenuHandle, uint16_t ItemNumb, uint8_t x, uint8_t y, uint8_t flag);
void DeleteMenu(int8_t MenuHandle);

void DisplayTitle (uint8_t iY, char *szTitle, char *szVersion);
void DisplaySubTitle(int y, char *title, char dispVer);
void ClearScreen ();


#endif // __TOOLS_P_H__
