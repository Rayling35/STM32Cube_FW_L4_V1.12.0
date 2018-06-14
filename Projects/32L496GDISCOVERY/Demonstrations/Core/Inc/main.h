/**
  ******************************************************************************
  * @file    main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"

#include "stm32l496g_discovery.h"
#include "stm32l496g_discovery_lcd.h"
#include "stm32l496g_discovery_ts.h"
   
/* DISCO includes component */
#include "stm32l496g_discovery_audio.h"
#include "stm32l496g_discovery_sd.h"
#include "stm32l496g_discovery_qspi.h"
   
/* CMSIS OS includes component */
#include "cmsis_os.h"   

/* FatFs includes components */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

#include "usbd_core.h"
   
/* GUI includes components */
#include "GUI.h"
#include "DIALOG.h"
#include "ST_GUI_Addons.h"
 
/* Kernel includes components */
#include "k_module.h"
#include "k_storage.h"
#include "k_rtc.h"    
#include "k_bsp.h"   
#include "k_calibration.h"
#include "k_mfx.h"
   
/* utilities and standard includes components */   
#include "cpu_utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


   
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  ULP_STOP2    = 0x00,
  ULP_STANDBY  = 0x01,
  ULP_OFF      = 0x02
} ULPMode;

typedef enum
{
  HWINIT_ERROR    = 0x00,
  HWINIT_STARTUP  = 0x01,
  HWINIT_IDD      = 0x02,
  HWINIT_STOP2    = 0x03,
  HWINIT_STANDBY  = 0x04
} HwInitMode;


typedef enum
{
  BACKUP_IDD        = 0x00,  /* IDD application backup data     */
  BACKUP_SETTINGS   = 0x01   /* Kernel settings backup data     */
} DemoBackupId;

typedef struct
{
  uint32_t mode;  
} IddBackupData_TypeDef;


typedef struct
{
  uint32_t lpmode;
} SettingsBackupData_TypeDef;

typedef struct
{
  /* IDD application */
  IddBackupData_TypeDef      idd;
  /* Global settings */
  SettingsBackupData_TypeDef settings;
} DemoBackupData_TypeDef;

typedef struct
{
  uint32_t       demo_id;
    unsigned char  demo_descr[50];
} Demo_Header_t;

/* Exported variables --------------------------------------------------------*/
extern FlagStatus DemoDebugMode;
extern FlagStatus WakeUpFromStandby;
extern FlagStatus WakeUpFromShutdown;
/* Exported constants --------------------------------------------------------*/
#define CALIBRATION_GENERAL_SETTINGS_BKP    RTC_BKP_DR2
#define DEMO_HOME_ADDRESS           0x08000000   

   
   
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void      SystemClock_Config(void);
void      SystemLowClock_Config(void);
void      SystemHardwareInit(HwInitMode Mode);
void      SystemHardwareDeInit(HwInitMode Mode);
void      SystemPeripheralClockEnable(void);
void      SystemPeripheralClockDisable(void);
void      EnterStop2Mode(void);
void      ExitStop2Mode(void);
void      Error_Handler(void);



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
