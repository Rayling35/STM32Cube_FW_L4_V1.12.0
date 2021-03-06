/**
  ******************************************************************************
  * @file    main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2017 STMicroelectronics International N.V. 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"

/* EVAL includes component */
#include "stm32l4r9i_eval.h"
#include "stm32l4r9i_eval_io.h"
#include "stm32l4r9i_eval_lcd.h"
#include "stm32l4r9i_eval_ts.h"
#include "stm32l4r9i_eval_ospi_nor.h"
#include "stm32l4r9i_eval_idd.h"
#include "stm32l4r9i_eval_audio.h"
#include "stm32l4r9i_eval_sd.h"

/* CMSIS OS includes component */
#include "cmsis_os.h"
   
/* FatFs includes component */
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/* Kernel includes components */
#include "gui.h"
#include "k_module.h"
#include "k_menu.h"
#include "k_storage.h"
#include "k_mfx.h"
#include "k_rtc.h"
#include "k_bsp.h"
#include "ts.h"
#endif /* !WIN32 */

/* GUI includes components */
#include "GUI.h"
#include "DIALOG.h"
#include "LCDConf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

   
/* Exported constants --------------------------------------------------------*/
#define NUM_DISK_UNITS       1
#define MSD_DISK_UNIT        0
#define AUDIO_DEFAULT_VOLUME 70

#define CALIBRATION_BKP0                     RTC_BKP_DR0
#define CALIBRATION_BKP1                     RTC_BKP_DR1
#define CALIBRATION_BKP2                     RTC_BKP_DR2
#define CALIBRATION_BKP3                     RTC_BKP_DR3
#define CALIBRATION_IMAGE_SETTINGS_BKP       RTC_BKP_DR4
#define CALIBRATION_AUDIOPLAYER_SETTING_BKP  RTC_BKP_DR5
#define CALIBRATION_AUDIORECODER_SETTING_BKP RTC_BKP_DR6
#define CALIBRATION_IDDMEASURE_SETTING_BKP   RTC_BKP_DR7

#define TS_INTERRUPT_MODE_ENABLED

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
extern void Error_Handler(void);

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t       demo_id;
  unsigned char  demo_descr[50];
} Demo_Header_t;

typedef enum
{
  DEMO_ID_0,
  DEMO_ID_1,
  DEMO_ID_2,
  DEMO_ID_NB,
} Demo_Id_t;

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
