/**
 ******************************************************************************
 * @file    dis_app.c
 * @author  MCD Application Team
 * @brief   Device Information Service Application
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
#include "common.h"

#include "ble_lib.h"
#include "blesvc.h"
#include "dis_app.h"



/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if ((BLE_CFG_DIS_SYSTEM_ID != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
static const uint8_t system_id[BLE_CFG_DIS_SYSTEM_ID_LEN_MAX] = 
{
  (uint8_t)((DISAPP_MANUFACTURER_ID & 0xFF0000) >> 16),
  (uint8_t)((DISAPP_MANUFACTURER_ID & 0x00FF00) >> 8),
  (uint8_t)(DISAPP_MANUFACTURER_ID & 0x0000FF),
  0xFE,
  0xFF,
  (uint8_t)((DISAPP_OUI & 0xFF0000) >> 16),
  (uint8_t)((DISAPP_OUI & 0x00FF00) >> 8),
  (uint8_t)(DISAPP_OUI & 0x0000FF)
};
#endif

#if ((BLE_CFG_DIS_IEEE_CERTIFICATION != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
static const uint8_t ieee_id[BLE_CFG_DIS_IEEE_CERTIFICATION_LEN_MAX] = 
{
  0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 
  0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 
  0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 
  0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 
};
#endif
#if ((BLE_CFG_DIS_PNP_ID != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
static const uint8_t pnp_id[BLE_CFG_DIS_PNP_ID_LEN_MAX] = 
{
  0x1,
  0xAD, 0xDE,
  0xDE, 0xDA, 
  0x01, 0x00
};
#endif

/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
/* Private functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

void DISAPP_Init(void)
{
  DIS_Data_t dis_information_data;

#if ((BLE_CFG_DIS_MANUFACTURER_NAME_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update MANUFACTURER NAME Information
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_MANUFACTURER_NAME;
  dis_information_data.Length = sizeof(DISAPP_MANUFACTURER_NAME);
  DIS_UpdateChar(MANUFACTURER_NAME_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_MODEL_NUMBER_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update MODEL NUMBERInformation
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_MODEL_NUMBER; 
  dis_information_data.Length = sizeof(DISAPP_MODEL_NUMBER);
  DIS_UpdateChar(MODEL_NUMBER_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_SERIAL_NUMBER_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update SERIAL NUMBERInformation
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_SERIAL_NUMBER;
  dis_information_data.Length = sizeof(DISAPP_SERIAL_NUMBER);
  DIS_UpdateChar(SERIAL_NUMBER_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_HARDWARE_REVISION_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update HARDWARE REVISION NUMBERInformation
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_HARDWARE_REVISION_NUMBER;
  dis_information_data.Length = sizeof(DISAPP_HARDWARE_REVISION_NUMBER);
  DIS_UpdateChar(HARDWARE_REVISION_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_FIRMWARE_REVISION_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update FIRMWARE REVISION NUMBERInformation
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_FIRMWARE_REVISION_NUMBER;
  dis_information_data.Length = sizeof(DISAPP_FIRMWARE_REVISION_NUMBER);
  DIS_UpdateChar(FIRMWARE_REVISION_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_SOFTWARE_REVISION_STRING != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))
  /**
   * Update SOFTWARE REVISION NUMBERInformation
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t*) DISAPP_SOFTWARE_REVISION_NUMBER;
  dis_information_data.Length = sizeof(DISAPP_SOFTWARE_REVISION_NUMBER);
  DIS_UpdateChar(SOFTWARE_REVISION_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_SYSTEM_ID != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))

  /**
   * Update SYSTEM ID Information
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t *)system_id;
  dis_information_data.Length = BLE_CFG_DIS_SYSTEM_ID_LEN_MAX;
  DIS_UpdateChar(SYSTEM_ID_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_IEEE_CERTIFICATION != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))

  /**
   * Update IEEE CERTIFICATION ID Information
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t *)ieee_id;
  dis_information_data.Length = BLE_CFG_DIS_IEEE_CERTIFICATION_LEN_MAX;
  DIS_UpdateChar(IEEE_CERTIFICATION_UUID, &dis_information_data);
#endif

#if ((BLE_CFG_DIS_PNP_ID != 0) || (BLE_CFG_MENU_DEVICE_INFORMATION != 0))

  /**
   * Update PNP ID Information
   *
   * @param UUID
   * @param pPData
   * @return
   */
  dis_information_data.pPayload = (uint8_t *)pnp_id;
  dis_information_data.Length = BLE_CFG_DIS_PNP_ID_LEN_MAX;
  DIS_UpdateChar(PNP_ID_UUID, &dis_information_data);
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
