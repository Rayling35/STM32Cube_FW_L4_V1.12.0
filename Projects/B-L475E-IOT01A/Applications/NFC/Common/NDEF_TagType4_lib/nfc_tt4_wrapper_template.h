/**
  ******************************************************************************
  * @file    nfc_tt4_wrapper_template.h
  * @author  MCD Application Team
  * @brief   This file makes the bridge between middleware generic NCF TagType4 
  *          function calls and the component.
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
#ifndef __NFC_TT4_WRAPPER_H
#define __NFC_TT4_WRAPPER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "component.h"

/** @addtogroup NFC_TT4_WRAPPER
  * @{
  */

/** @defgroup NFC_TT4_WRAPPER_Exported_Constants  NFC_TT4_WRAPPER Exported Constants
  * @{
  */

/** @defgroup NFC_TT4_NDEF_EEPROM_Size_Version
  * @{
  */
/* ---------------------- M24SR properties -----------------------------------*/

/* The maximum size of a NDEF  */
#define NFC_TT4_NDEF_MAX_SIZE          0x2000

/**
  * @}
  */
  
/** @defgroup NFC_TT4_WRAPPER_Status_Code
  * @{
  */
/* ---------------------- status code ----------------------------------------*/
#define NFC_TT4_ACTION_COMPLETED        0x9000
/**
  * @}
  */
  
/** @defgroup NFC_TT4__Flag_to_select_open_session_command
  * @{
  */
#define NFC_TT4_ASK_FOR_SESSION                     0x0000
#define NFC_TT4_TAKE_SESSION                        0xFFFF

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup NFC_TT4_WRAPPER_Exported_FunctionsPrototypes  NFC_TT4_WRAPPER Exported FunctionsPrototypes
  * @{
  */

uint16_t NFC_TT4_Initialization (uint8_t* pCCBuffer, uint8_t size );
uint16_t NFC_TT4_OpenNDEFSession ( uint16_t NDEF_fileID, uint16_t Priority );
uint16_t NFC_TT4_ReadData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData);
uint16_t NFC_TT4_ForceReadData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData);
uint16_t NFC_TT4_WriteData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData);
uint16_t NFC_TT4_CloseNDEFSession ( uint16_t NDEF_fileID );

/**
  * @}
  */
  
/**
  * @}
  */  
#ifdef __cplusplus
}
#endif


#endif /* __NFC_TT4_WRAPPER_H */
 
/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
