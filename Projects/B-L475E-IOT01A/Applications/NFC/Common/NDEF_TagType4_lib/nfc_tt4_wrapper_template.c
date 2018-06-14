/**
  ******************************************************************************
  * @file    nfc_tt4_wrapper_template.c
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

/* Includes ------------------------------------------------------------------*/
#include "nfc_tt4_wrapper_template.h"

/** @addtogroup NFC_TT4_WRAPPER
  * @{
  */

/** @defgroup NFC_TT4_WRAPPER
  * @{
  *  @brief  This is the library to interface with the COMPONENT dynamic tag.
  *         This layer simplify the use of the COMPONENT driver by sequencing 
  *         some commands.
  */

  /** @defgroup NFC_TT4_WRAPPER_Private_Defines  NFC_TT4_WRAPPER Private Defines
  * @{
  */
#define NDEF_SESSION_CLOSED                 0xDEADBEEF
/* COMPONENT buffer size is 0xF6 can be retrieve dynamicaly in CC file */
#define COMPONENT_READ_MAX_NBBYTE               0xF6 
#define COMPONENT_WRITE_MAX_NBBYTE              0xF6
/**
  * @}
  */
  
/** @defgroup NFC_TT4_WRAPPER_Private_Variables   NFC_TT4_WRAPPER Private Global Variables
  * @{
  */
  
uint8_t I2CPassword[16]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static uint32_t NDEFSessionOpenID=NDEF_SESSION_CLOSED;


/**
  * @}
  */


/** @defgroup NFC_TT4_WRAPPER_Private_Macros  NFC_TT4_WRAPPER Private Macros
  * @{
  */

/** @brief Check return statement of function
  * @param  fCall function result to check 
  * @retval COMPONENT_ACTION_COMPLETED or jump to dedicated Error management
  */ 
#ifndef errorchk
#define errorchk(fCall) if (status = (fCall), status != COMPONENT_ACTION_COMPLETED) \
  {goto Error;} else
#endif

/**
  * @}
  */

/** @defgroup NFC_TT4_WRAPPER_Private_Functions
  * @{
  */

/**
  * @}
  */


/** @defgroup NFC_TT4_WRAPPER_Exported_Functions   NFC_TT4_WRAPPER Exported Functions 
  * @{
  */

/**
  * @brief  This fonction initialize the COMPONENT
  * @param  CCBuffer : pointer on the buffer to store CC file
  * @param  size : number of byte of data to read
  * @retval SUCCESS : Initalization done
  * @retval ERROR : Not able to Initialize. 
  */
uint16_t NFC_TT4_Initialization ( uint8_t* CCBuffer, uint8_t size )
{
    return SUCCESS;
}




/**
  * @brief  This fonction configure the COMPONENT to access NDEF message by I2C
  * @param  NDEF_fileID : NDEF identification to select NDEF in COMPONENT
  * @param  Priority: 2 options: check if COMPONENT available to open session (no RF session on going)
  *                               Kill RF session and open I2C sesssion.
  * @retval SUCCESS : Session is opened
  * @retval ERROR : Not able to open session. 
  */
uint16_t NFC_TT4_OpenNDEFSession ( uint16_t NDEF_fileID, uint16_t Priority )
{
    return SUCCESS;
}

/**
  * @brief  This fonction close the NDEF Session.
  * @param  NDEF_fileID : NDEF identification to select NDEF in COMPONENT
  * @retval SUCCESS : Session is closed
  * @retval ERROR : Not able to close session. 
  */
uint16_t NFC_TT4_CloseNDEFSession ( uint16_t NDEF_fileID )
{
    return SUCCESS;
}

/**
  * @brief  This fonction read the data stored in COMPONENT at defined offset
  * @param  Offset : Offset in the NDEF file in COMPONENT
  * @param  DataSize : Number of byte to read
  * @param  pData : pointer on buffer to store read data
  * @retval Status (SW1&SW2) : Status of the operation. 
  */
uint16_t NFC_TT4_ReadData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData)
{
    return SUCCESS;
}

/**
  * @brief  This fonction read the data stored in COMPONENT at defined offset without NDEF concideration
  * @param  Offset : Offset in the NDEF file in COMPONENT
  * @param  DataSize : Number of byte to read
  * @param  pData : pointer on buffer to store read data
  * @retval Status (SW1&SW2) : Status of the operation.  
  */
uint16_t NFC_TT4_ForceReadData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData)
{
    return SUCCESS;
}

/**
  * @brief  This fonction write data in COMPONENT at defined offset
  * @param  Offset : Offset in the NDEF file in COMPONENT
  * @param  DataSize : Number of byte to read
  * @param  pData : pointer on buffer to copy in COMPONENT
  * @retval Status (SW1&SW2) : Status of the operation.  
  */
uint16_t NFC_TT4_WriteData ( uint16_t Offset , uint16_t DataSize , uint8_t* pData)
{
    return SUCCESS;
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


