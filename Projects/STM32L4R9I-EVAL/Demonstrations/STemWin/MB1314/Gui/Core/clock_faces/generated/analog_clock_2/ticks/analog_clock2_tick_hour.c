/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.40.                      *
*        Compiled Mar 17 2017, 15:33:27                              *
*                                                                    *
*        (c) 1998 - 2017 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: analog_clock2_tick_hour                               *
* Dimensions:  6 * 118                                               *
* NumColors:   32bpp: 16777216 + 256                                 *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_tick_hour;

#if defined ( __ICCARM__ )
#pragma location="ExtFlashSection" 
#else
__attribute__((section(".ExtFlashSection")))  
#endif
static GUI_CONST_STORAGE unsigned long _acanalog_clock2_tick_hour[] = {
#if (GUI_USE_ARGB == 1)
  0x010000FF, 0x760061FF, 0xE10061FF, 0xEB0062FF, 0x940062FF, 0x0A0066FF,
  0x600062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0x900061FF,
  0xB60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE60062FF,
  0xCE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF,
  0xCE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFE0062FF,
  0xCF0063FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFE0062FF,
  0xCF0063FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFD0062FF,
  0xD00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFD0062FF,
  0xD00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFC0062FF,
  0xD10062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFC0062FF,
  0xD10062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFB0062FF,
  0xD20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFB0062FF,
  0xD20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFA0062FF,
  0xD20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFA0062FF,
  0xD30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFA0062FF,
  0xD30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF90062FF,
  0xD40061FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF90062FF,
  0xD40061FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF80062FF,
  0xD50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF80062FF,
  0xD50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF70062FF,
  0xD60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF70062FF,
  0xD60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF60062FF,
  0xD60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF60062FF,
  0xD70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF60062FF,
  0xD70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF50062FF,
  0xD80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF50062FF,
  0xD80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF40062FF,
  0xD90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF40062FF,
  0xD90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF30062FF,
  0xDA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF30062FF,
  0xDA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF20062FF,
  0xDA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF20062FF,
  0xDB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF20062FF,
  0xDB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF10062FF,
  0xDC0063FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF10062FF,
  0xDC0063FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF00062FF,
  0xDD0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xF00062FF,
  0xDD0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEF0062FF,
  0xDE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEF0062FF,
  0xDE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEE0062FF,
  0xDE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEE0062FF,
  0xDF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEE0062FF,
  0xDF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xED0062FF,
  0xE00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xED0062FF,
  0xE00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEC0062FF,
  0xE10061FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEC0062FF,
  0xE10061FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEB0062FF,
  0xE20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEB0062FF,
  0xE20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEA0062FF,
  0xE20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEA0062FF,
  0xE30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xEA0062FF,
  0xE30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE90062FF,
  0xE40062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE90062FF,
  0xE40062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE80062FF,
  0xE50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE80062FF,
  0xE50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE70062FF,
  0xE60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE70062FF,
  0xE60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE60062FF,
  0xE60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE60062FF,
  0xE70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE60062FF,
  0xE70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE50062FF,
  0xE80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE50062FF,
  0xE80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE40062FF,
  0xE90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE40062FF,
  0xE90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE30062FF,
  0xEA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE30062FF,
  0xEA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE20062FF,
  0xEB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE20062FF,
  0xEB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE10061FF,
  0xEB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE10061FF,
  0xEC0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE10061FF,
  0xEC0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE00062FF,
  0xED0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xE00062FF,
  0xED0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDF0062FF,
  0xEE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDF0062FF,
  0xEE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDE0062FF,
  0xEF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDE0062FF,
  0xEF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDD0062FF,
  0xEF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDD0062FF,
  0xF00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDD0062FF,
  0xF00062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDC0063FF,
  0xF10062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDC0063FF,
  0xF10062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDB0062FF,
  0xF20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDB0062FF,
  0xF20062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDA0062FF,
  0xF30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xDA0062FF,
  0xF30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD90062FF,
  0xF30062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD90062FF,
  0xF40062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD90062FF,
  0xF40062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD80062FF,
  0xF50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD80062FF,
  0xF50062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD70062FF,
  0xF60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD70062FF,
  0xF60062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD60062FF,
  0xF70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD60062FF,
  0xF70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD50062FF,
  0xF70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD50062FF,
  0xF80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD50062FF,
  0xF80062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD40061FF,
  0xF90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD40061FF,
  0xF90062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD30062FF,
  0xFA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD30062FF,
  0xFA0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD20062FF,
  0xFB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD20062FF,
  0xFB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD10062FF,
  0xFB0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD10062FF,
  0xFC0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD10062FF,
  0xFC0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD00062FF,
  0xFD0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xD00062FF,
  0xFD0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCF0063FF,
  0xFE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCF0063FF,
  0xFE0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCE0062FF,
  0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCE0062FF,
  0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCD0062FF,
  0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xCD0062FF,
  0xE70062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xB30062FF,
  0x910062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0xFF0062FF, 0x5D0063FF,
  0x090055FF, 0x940062FF, 0xEA0062FF, 0xE00062FF, 0x740063FF, 0x010000FF
#else
  0xFEFF0000, 0x89FF6100, 0x1EFF6100, 0x14FF6200, 0x6BFF6200, 0xF5FF6600,
  0x9FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x6FFF6100,
  0x49FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x19FF6200,
  0x31FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200,
  0x31FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x01FF6200,
  0x30FF6300, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x01FF6200,
  0x30FF6300, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x02FF6200,
  0x2FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x02FF6200,
  0x2FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x03FF6200,
  0x2EFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x03FF6200,
  0x2EFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x04FF6200,
  0x2DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x04FF6200,
  0x2DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x05FF6200,
  0x2DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x05FF6200,
  0x2CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x05FF6200,
  0x2CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x06FF6200,
  0x2BFF6100, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x06FF6200,
  0x2BFF6100, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x07FF6200,
  0x2AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x07FF6200,
  0x2AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x08FF6200,
  0x29FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x08FF6200,
  0x29FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x09FF6200,
  0x29FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x09FF6200,
  0x28FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x09FF6200,
  0x28FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0AFF6200,
  0x27FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0AFF6200,
  0x27FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0BFF6200,
  0x26FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0BFF6200,
  0x26FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0CFF6200,
  0x25FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0CFF6200,
  0x25FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0DFF6200,
  0x25FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0DFF6200,
  0x24FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0DFF6200,
  0x24FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0EFF6200,
  0x23FF6300, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0EFF6200,
  0x23FF6300, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0FFF6200,
  0x22FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x0FFF6200,
  0x22FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x10FF6200,
  0x21FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x10FF6200,
  0x21FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x11FF6200,
  0x21FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x11FF6200,
  0x20FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x11FF6200,
  0x20FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x12FF6200,
  0x1FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x12FF6200,
  0x1FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x13FF6200,
  0x1EFF6100, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x13FF6200,
  0x1EFF6100, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x14FF6200,
  0x1DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x14FF6200,
  0x1DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x15FF6200,
  0x1DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x15FF6200,
  0x1CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x15FF6200,
  0x1CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x16FF6200,
  0x1BFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x16FF6200,
  0x1BFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x17FF6200,
  0x1AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x17FF6200,
  0x1AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x18FF6200,
  0x19FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x18FF6200,
  0x19FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x19FF6200,
  0x19FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x19FF6200,
  0x18FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x19FF6200,
  0x18FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1AFF6200,
  0x17FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1AFF6200,
  0x17FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1BFF6200,
  0x16FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1BFF6200,
  0x16FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1CFF6200,
  0x15FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1CFF6200,
  0x15FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1DFF6200,
  0x14FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1DFF6200,
  0x14FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1EFF6100,
  0x14FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1EFF6100,
  0x13FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1EFF6100,
  0x13FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1FFF6200,
  0x12FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x1FFF6200,
  0x12FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x20FF6200,
  0x11FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x20FF6200,
  0x11FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x21FF6200,
  0x10FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x21FF6200,
  0x10FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x22FF6200,
  0x10FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x22FF6200,
  0x0FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x22FF6200,
  0x0FFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x23FF6300,
  0x0EFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x23FF6300,
  0x0EFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x24FF6200,
  0x0DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x24FF6200,
  0x0DFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x25FF6200,
  0x0CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x25FF6200,
  0x0CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x26FF6200,
  0x0CFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x26FF6200,
  0x0BFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x26FF6200,
  0x0BFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x27FF6200,
  0x0AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x27FF6200,
  0x0AFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x28FF6200,
  0x09FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x28FF6200,
  0x09FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x29FF6200,
  0x08FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x29FF6200,
  0x08FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2AFF6200,
  0x08FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2AFF6200,
  0x07FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2AFF6200,
  0x07FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2BFF6100,
  0x06FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2BFF6100,
  0x06FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2CFF6200,
  0x05FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2CFF6200,
  0x05FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2DFF6200,
  0x04FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2DFF6200,
  0x04FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2EFF6200,
  0x04FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2EFF6200,
  0x03FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2EFF6200,
  0x03FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2FFF6200,
  0x02FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x2FFF6200,
  0x02FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x30FF6300,
  0x01FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x30FF6300,
  0x01FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x31FF6200,
  0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x31FF6200,
  0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x32FF6200,
  0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x32FF6200,
  0x18FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x4CFF6200,
  0x6EFF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0x00FF6200, 0xA2FF6300,
  0xF6FF5500, 0x6BFF6200, 0x15FF6200, 0x1FFF6200, 0x8BFF6300, 0xFEFF0000
#endif
};

GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_tick_hour = {
  6, // xSize
  118, // ySize
  24, // BytesPerLine
  32, // BitsPerPixel
  (unsigned char *)_acanalog_clock2_tick_hour,  // Pointer to picture data
  NULL,  // Pointer to palette
#if (GUI_USE_ARGB == 1)
  GUI_DRAW_BMPM8888I
#else
  GUI_DRAW_BMP8888
#endif
};

/*************************** End of file ****************************/
