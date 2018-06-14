/**
  ******************************************************************************
  * @file    lib_TT4_interface.h
  * @author  MMY Application Team
  * @brief   This file help to manage TagType4 NDEF library.
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
#ifndef __LIB_TT4_INTERFACE_H
#define __LIB_TT4_INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lib_NDEF_URI.h"
#include "lib_NDEF_SMS.h"
#include "lib_NDEF_Email.h"
#include "lib_NDEF_Vcard.h"
#include "lib_NDEF_Geo.h"
#include "lib_NDEF_MyApp.h"   
#include "lib_NDEF_AAR.h"

/** @addtogroup NFC_libraries
  * @{
  */
  
/** @addtogroup TAGTYPE4_NDEF_INTERFACE
  * @{
  */

/**
 * @defgroup TAGTYPE4_NDEF_INTERFACE_Exported_Types             TAGTYPE4_NDEF_INTERFACE Exported Types
 * @{
 */

/**
  * @brief  CCfile structure
  */
typedef struct
{
  uint16_t NumberCCByte;
  uint8_t Version;
  uint16_t MaxReadByte;
  uint16_t MaxWriteByte;
  uint8_t TField;
  uint8_t LField;
  uint16_t FileID;
  uint16_t NDEFFileMaxSize;
  uint8_t ReadAccess;
  uint8_t WriteAccess;
}sCCFileInfo;

/**
  * @brief  Tag type supported
  */
typedef enum 
{
  UNKNOWN_TAG = 0,
  INTERFACE_TAG,
  URI_TAG,
  SMS_TAG,
  GEO_TAG,
  EMAIL_TAG,
  TEXT_TAG,
  BT_TAG,
  WIFI_TAG
} Tag_TypeDef;

/**
  * @}
  */
    
/**
 * @defgroup TAGTYPE4_NDEF_INTERFACE_Exported_FunctionPrototypes             TAGTYPE4_NDEF_INTERFACE Exported FunctionPrototypes
 * @{
 */

uint16_t TT4_Init( void );
uint16_t TT4_ReadNDEF(uint8_t *pNDEF);
uint16_t TT4_WriteNDEF(uint8_t *pNDEF);
uint16_t TT4_ReadURI(sURI_Info *pURI);
uint16_t TT4_WriteURI(sURI_Info *pURI);
uint16_t TT4_ReadSMS(sSMSInfo *pSMS);
uint16_t TT4_WriteSMS(sSMSInfo *pSMS);
uint16_t TT4_ReadEmail(sEmailInfo *pEmailStruct);
uint16_t TT4_WriteEmail(sEmailInfo *pEmailStruct);
uint16_t TT4_ReadVcard(sVcardInfo *pVcard);
uint16_t TT4_WriteVcard(sVcardInfo *pVcard);
uint16_t TT4_ReadGeo(sGeoInfo *pGeo);
uint16_t TT4_WriteGeo(sGeoInfo *pGeo);
uint16_t TT4_ReadMyApp(sMyAppInfo *pMyAppStruct);
uint16_t TT4_WriteMyApp(sMyAppInfo *pMyAppStruct);
uint16_t TT4_AddAAR(sAARInfo *pAAR);
/**
  * @}
  */ 
  
/**
  * @}
  */  
  
/**
  * @}
  */  

#ifdef __cplusplus
}
#endif

#endif /* __LIB_TT4_INTERFACE_H */


/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
