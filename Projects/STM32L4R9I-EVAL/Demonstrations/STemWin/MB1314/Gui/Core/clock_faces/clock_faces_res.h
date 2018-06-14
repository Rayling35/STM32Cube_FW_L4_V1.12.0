/**
  ******************************************************************************
  * @file    clock_faces_res.h
  * @author  MCD Application Team
  * @brief   clock faces ressources
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

#ifndef GUI_CLOCK_FACES_RESOURCES_H__
#define GUI_CLOCK_FACES_RESOURCES_H__

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

/*** Genereted bitmaps used for the clock faces module ***/

/* Analog Clock 1 */
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1_cercle;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1_tick_hour;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1_tick_minute;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock1_tick_second;

/* Analog Clock 2 */
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_cercle;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_tick_hour;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_tick_minute;
extern GUI_CONST_STORAGE GUI_BITMAP bmanalog_clock2_tick_second;

/* Digital Clock 1 */
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock1_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock1_background_day;

/* Digital Clock 2 */
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock2_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock2_cercle_1_half;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock2_cercle_1;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock2_cercle_2;
extern GUI_CONST_STORAGE GUI_BITMAP bmdigital_clock2_white_cercle;

/* Commands */
extern GUI_CONST_STORAGE GUI_BITMAP bmbackground_low_oppacity;
extern GUI_CONST_STORAGE GUI_BITMAP bmback_arrow;
extern GUI_CONST_STORAGE GUI_BITMAP bmbkc_setalarm;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock_blue_cercle_date;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock_white_cercle_date;
extern GUI_CONST_STORAGE GUI_BITMAP bmshape_button_back;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat_cercle_date;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat_selected;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmic_settings_selected;
extern GUI_CONST_STORAGE GUI_BITMAP bmsettings_blue_cercle_selected;
extern GUI_CONST_STORAGE GUI_BITMAP bmsettings_white_cercle_selected;
extern GUI_CONST_STORAGE GUI_BITMAP bmshape_settings;
extern GUI_CONST_STORAGE GUI_BITMAP bmic_settings_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmsettings_blue_cercle_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmnew_alarm_icon;
extern GUI_CONST_STORAGE GUI_BITMAP bmnew_alarm_icon_cercle;
extern GUI_CONST_STORAGE GUI_BITMAP bmnew_alarm_icon_selected;
extern GUI_CONST_STORAGE GUI_BITMAP bmscreen_clock_ic_date;
extern GUI_CONST_STORAGE GUI_BITMAP bmscreen_clock_time;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_cercle_new_alarm;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_cercle_new_alarm_disabled;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_ic_new_alarm;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_ic_remove_alarm;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_locked;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_alarm_unlocked;
extern GUI_CONST_STORAGE GUI_BITMAP bmshape_alarms;
extern GUI_CONST_STORAGE GUI_BITMAP bmset_time_shape;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock1_small;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock2_small;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock3_small;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock4_small;
extern GUI_CONST_STORAGE GUI_BITMAP bmswipe_up_arrow;
extern GUI_CONST_STORAGE GUI_BITMAP bmswipe_up_arrow_up;
extern GUI_CONST_STORAGE GUI_BITMAP bmswipe_up_settings_background;

extern GUI_CONST_STORAGE GUI_BITMAP bmmo_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmtu_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmwe_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmth_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmfr_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmsa_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmsu_text;
extern GUI_CONST_STORAGE GUI_BITMAP bmAlarmList;

extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_alert_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_alert_blue;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_dismiss_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_snooze3_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_snooze5_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_snooze7_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmbutton_snooze10_unselected;
extern GUI_CONST_STORAGE GUI_BITMAP bmsnooze_text;

extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_alert_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmic_alarm_repeat_alarm;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_10;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_20;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_30;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_40;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_50;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_60;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_70;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_80;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_90;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation1_100;

extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_10;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_20;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_30;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_40;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_50;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_60;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_70;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_80;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_90;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation2_100;


extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_10;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_20;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_30;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_40;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_50;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_60;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_70;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_80;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_90;
extern GUI_CONST_STORAGE GUI_BITMAP bmalarm_animation3_100;

extern GUI_CONST_STORAGE GUI_BITMAP bmsmall_blue_bell;
extern GUI_CONST_STORAGE GUI_BITMAP bmsmall_white_bell;

#endif  /* Avoid multiple inclusion */
/*************************** End of file ****************************/

