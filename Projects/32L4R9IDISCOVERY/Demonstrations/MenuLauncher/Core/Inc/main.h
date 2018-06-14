/**
  ******************************************************************************
  * @file    main.h 
  * @author  MCD Application Team 
  * @brief   Header for main.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#ifndef GUI_SIMULATOR
#include "stm32l4xx_hal.h"

/* DISCOVERY includes component */
#include "stm32l4r9i_discovery.h"
#include "stm32l4r9i_discovery_io.h"
#include "stm32l4r9i_discovery_lcd.h"
#include "stm32l4r9i_discovery_ts.h"
#include "stm32l4r9i_discovery_ospi_nor.h"
#include "stm32l4r9i_discovery_idd.h"
#include "stm32l4r9i_discovery_sd.h"

/* CMSIS OS includes component */
#include "cmsis_os.h"

/* FatFs includes components */
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio_dma.h"
#endif /* !GUI_SIMULATOR */

/* GUI includes components */
#include "GUI.h"
#include "DIALOG.h"
#include "LCDConf.h"

#ifndef GUI_SIMULATOR
/* Kernel includes components */
#include "ts.h"
#include "mfx.h"
#include "storage.h"
#include "bsp.h"
#endif /* !GUI_SIMULATOR */

/* standard includes components */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

/* Exported variables --------------------------------------------------------*/
/* Flag to indicate whether or not software is coming back from a software reset */
extern uint32_t software_reset_flag;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
