/**
  ******************************************************************************
  * @file    audio_player_res.h
  * @author  MCD Application Team
  * @brief   audio player resources
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

#ifndef GUI_AUDIO_PLAYER_RESOURCES_H__
#define GUI_AUDIO_PLAYER_RESOURCES_H__

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

/*** Genereted bitmaps used for the audio player and the equilizer modules ***/

extern GUI_CONST_STORAGE GUI_BITMAP bmaudio_player_splash;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_background;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_equalizer_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_equalizer_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_minus_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_minus_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_next_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_next_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_pause_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_pause_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_play_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_play_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_plus_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_plus_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_previous_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_previous_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_repeat_all_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_repeat_all_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_repeat_one_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_repeat_one_unpressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_sound_mute;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_speaker_transparent;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon_speaker_white;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_icon;

/* Volume and Playback Progress bar */
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_pb_playback_full;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_pb_playback_niddle;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_pb_volume_bkg;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_pb_volume_empty;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_pb_volume_full;

/* Equalizer */
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_eq_button_equalizer;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_eq_progress_bar_cercle;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_eq_progress_bar_niddle;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_eq_separation;
extern GUI_CONST_STORAGE GUI_BITMAP bmplayer_eq_shape;

#endif  /* Avoid multiple inclusion */
/*************************** End of file ****************************/

