/**
  ******************************************************************************
  * @file    lib_TT4_interface.c
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

/* Includes ------------------------------------------------------------------*/
#include "lib_NDEF_private.h"
#include "lib_TT4_interface.h"

/** @addtogroup NFC_libraries
 *  @{
 */
 
/** @addtogroup TAGTYPE4_NDEF_INTERFACE
 *  @{
 */

/** @defgroup TAGTYPE4_NDEF_INTERFACE_Private_Variables TAGTYPE4 NDEF Variables 
  * @{
  */
  
/**
 * @brief  This buffer contains the data send/received by TAG
 */
uint8_t NDEF_Buffer [NFC_TT4_NDEF_MAX_SIZE];

/**
 * @brief  This structure contains the data of the CC file
 */
sCCFileInfo CCFileStruct;

/**
 * @brief  This structure contains the information encapsuled in the record header
 *         with few more for SW purpose
 */
sRecordInfo RecordStruct;

/**
  * @}
  */

/** @defgroup TAGTYPE4_NDEF_INTERFACE_Private_Functions  TAGTYPE4_NDEF_INTERFACE Private Functions
  * @{
  */

/**
  * @}
  */


/** @defgroup libTT4_Public_Functions
  * @{
  *  @brief  This file is used to access tag type 4.
  */ 

/**
  * @brief  This fonction initialize Tag Type 4
  * @param  None 
  * @retval SUCCESS : Initialization done
  */
uint16_t TT4_Init (void)
{
  uint16_t status = NDEF_SUCCESS;
  uint8_t CCBuffer[15];
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;

  status = NFC_TT4_Initialization( CCBuffer, sizeof(CCBuffer));
  
  if( status == NDEF_SUCCESS)
  {
    pCCFile->NumberCCByte = (uint16_t) ((CCBuffer[0x00]<<8) | CCBuffer[0x01]);
    pCCFile->Version = CCBuffer[0x02];
    pCCFile->MaxReadByte = (uint16_t) ((CCBuffer[0x03]<<8) | CCBuffer[0x04]);
    pCCFile->MaxWriteByte = (uint16_t) ((CCBuffer[0x05]<<8) | CCBuffer[0x06]);
    pCCFile->TField = CCBuffer[0x07];
    pCCFile->LField = CCBuffer[0x08];
    pCCFile->FileID = (uint16_t) ((CCBuffer[0x09]<<8) | CCBuffer[0x0A]);
    pCCFile->NDEFFileMaxSize = (uint16_t) ((CCBuffer[0x0B]<<8) | CCBuffer[0x0C]);
    pCCFile->ReadAccess = CCBuffer[0x0D];
    pCCFile->WriteAccess = CCBuffer[0x0E];  
  }
  
  return status;
}  

/**
  * @brief  This fonction read NDEF file
  * @param  pNDEF : pointer on buffer to fill with NDEF data
  * @retval SUCCESS : NDEF file data have been retrieve
  * @retval ERROR : Not able to get NDEF file data
  */
uint16_t TT4_ReadNDEF(uint8_t *pNDEF)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_ReadNDEF(pNDEF);
    NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file
  * @param  pNDEF : pointer on buffer that contain the NDEF data
  * @retval SUCCESS : NDEF file data have been stored
  * @retval ERROR : Not able to store NDEF file
  */
uint16_t TT4_WriteNDEF(uint8_t *pNDEF)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteNDEF( pNDEF);
    NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as URI
  * @param  pURI : pointer on URI structure to fill with read data
  * @retval SUCCESS : URI structure has been updated
  * @retval ERROR : Not able to fill URI structure
  */
uint16_t TT4_ReadURI(sURI_Info *pURI)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadURI(pRecordStruct, pURI);
    }
    NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file from data given in the URI structure
  * @param  pURI : pointer on URI structure to prepare NDEF
  * @retval SUCCESS : NDEF URI stored
  * @retval ERROR : Not able to store NDEF URI
  */
uint16_t TT4_WriteURI(sURI_Info *pURI)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteURI ( pURI );
    NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as SMS
  * @param  pSMS : pointer on SMS structure to fill with read data
  * @retval SUCCESS : SMS structure has been updated
  * @retval ERROR : Not able to fill MS structure
  */
uint16_t TT4_ReadSMS(sSMSInfo *pSMS)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadSMS(pRecordStruct, pSMS);
    }
    NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file from data given in the SMS structure
  * @param  pSMS : pointer on SMS structure to prepare NDEF
  * @retval SUCCESS : NDEF SMS stored
  * @retval ERROR : Not able to store NDEF SMS
  */
uint16_t TT4_WriteSMS(sSMSInfo *pSMS)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteSMS ( pSMS );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as eMail
  * @param  pEmailStruct : pointer on eMail structure to fill with read data
  * @retval SUCCESS : eMail structure has been updated
  * @retval ERROR : Not able to fill eMail structure
  */
uint16_t TT4_ReadEmail (sEmailInfo *pEmailStruct)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadEmail(pRecordStruct, pEmailStruct);
    }
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;    
}

/**
  * @brief  This fonction write NDEF file from data given in the eMail structure
  * @param  pEmailStruct : pointer on eMail structure to prepare NDEF
  * @retval SUCCESS : NDEF eMail stored
  * @retval ERROR : Not able to store NDEF eMail
  */
uint16_t TT4_WriteEmail(sEmailInfo *pEmailStruct)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteEmail ( pEmailStruct );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as Vcard
  * @param  pVcard : pointer on Vcard structure to fill with read data
  * @retval SUCCESS : Vcard structure has been updated
  * @retval ERROR : Not able to fill Vcard structure
  */
uint16_t TT4_ReadVcard(sVcardInfo *pVcard)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {  
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadVcard(pRecordStruct, pVcard);
    }
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file from data given in the Vcard structure
  * @param  pVcard : pointer on Vcard structure to prepare NDEF
  * @retval SUCCESS : NDEF Vcard stored
  * @retval ERROR : Not able to store NDEF Vcard
  */
uint16_t TT4_WriteVcard(sVcardInfo *pVcard)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteVcard ( pVcard );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as geolocation information
  * @param  pGeo : pointer on geo structure to fill with read data
  * @retval SUCCESS : geo structure has been updated
  * @retval ERROR : Not able to fill geo structure
  */
uint16_t TT4_ReadGeo(sGeoInfo *pGeo)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadGeo(pRecordStruct, pGeo);
    }
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file from data given in the geo structure
  * @param  pGeo : pointer on geo structure to prepare NDEF
  * @retval SUCCESS : NDEF geo stored
  * @retval ERROR : Not able to store NDEF geo
  */
uint16_t TT4_WriteGeo(sGeoInfo *pGeo)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteGeo ( pGeo );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction read NDEF file if NDEF is identified as expected private application
  * @param  pMyAppStruct : pointer on structure to fill with read data
  * @retval SUCCESS : structure has been updated
  * @retval ERROR : Not able to fill structure
  */
uint16_t TT4_ReadMyApp(sMyAppInfo *pMyAppStruct)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  sRecordInfo *pRecordStruct;
  
  pCCFile = &CCFileStruct;
  pRecordStruct = &RecordStruct;
  
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_TAKE_SESSION) == NDEF_SUCCESS)
  {
    if(NDEF_IdentifyNDEF( pRecordStruct, NDEF_Buffer) == NDEF_SUCCESS)
    {
      status = NDEF_ReadMyApp(pRecordStruct, pMyAppStruct);
    }
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction write NDEF file from data given in the structure
  * @param  pMyAppStruct : pointer on structure to prepare NDEF
  * @retval SUCCESS : NDEF stored
  * @retval ERROR : Not able to store NDEF
  */
uint16_t TT4_WriteMyApp(sMyAppInfo *pMyAppStruct)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_WriteMyApp ( pMyAppStruct );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @brief  This fonction add AAR (Android Application Record) in the tag
  * @param  pAAR : pointer on structure that contain AAR information
  * @retval SUCCESS : AAR added
  * @retval ERROR : Not able to add AAR
  */
uint16_t TT4_AddAAR(sAARInfo *pAAR)
{
  uint16_t status = NDEF_ERROR;
  sCCFileInfo *pCCFile;
  
  pCCFile = &CCFileStruct;
  
  if(NFC_TT4_OpenNDEFSession(pCCFile->FileID, NFC_TT4_ASK_FOR_SESSION) == NDEF_SUCCESS)
  {
    status = NDEF_AddAAR ( pAAR );
     NFC_TT4_CloseNDEFSession(pCCFile->FileID);
  }
  
  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

