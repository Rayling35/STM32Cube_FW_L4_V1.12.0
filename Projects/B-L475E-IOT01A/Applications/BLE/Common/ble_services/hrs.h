/**
  ******************************************************************************
  * @file    hrs.h
  * @author  MCD Application Team
  * @brief   Header for stm32xx_heartrate.c module
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
#ifndef __HRS_H
#define __HRS_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  typedef enum
  {
    HRS_HRM_VALUE_FORMAT_UINT16 = 1,
    HRS_HRM_SENSOR_CONTACT_PRESENT = 2,
    HRS_HRM_SENSOR_CONTACT_SUPPORTED = 4,
    HRS_HRM_ENERGY_EXPENDED_PRESENT = 8,
    HRS_HRM_RR_INTERVAL_PRESENT = 0x10
  } HRS_HrmFlags_t;

  typedef enum
  {
    HRS_BODY_SENSOR_LOCATION_OTHER = 0,
    HRS_BODY_SENSOR_LOCATION_CHEST = 1,
    HRS_BODY_SENSOR_LOCATION_WRIST = 2,
    HRS_BODY_SENSOR_LOCATION_FINGER = 3,
    HRS_BODY_SENSOR_LOCATION_HAND = 4,
    HRS_BODY_SENSOR_LOCATION_EAR_LOBE = 5,
    HRS_BODY_SENSOR_LOCATION_FOOT = 6
  } HRS_BodySensorLocation_t;

  typedef enum
  {
    HRS_RESET_ENERGY_EXPENDED_EVT,
    HRS_NOTIFICATION_ENABLED,
    HRS_NOTIFICATION_DISABLED,
  } HRS_NotCode_t;

  typedef struct{
    uint16_t    MeasurementValue;
#if (BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG == 1)
    uint16_t    EnergyExpended;
#endif
#if (BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG != 0)
    uint16_t    aRRIntervalValues[BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG + BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG];
    uint8_t     NbreOfValidRRIntervalValues;
#endif
    uint8_t     Flags;
  }HRS_MeasVal_t;

  /* Exported constants --------------------------------------------------------*/
  /* External variables --------------------------------------------------------*/
  /* Exported macros -----------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */
  void HRS_Init(void);
  tBleStatus HRS_UpdateChar(uint16_t uuid, uint8_t *p_payload);
  void HRS_Notification(HRS_NotCode_t notification);

#ifdef __cplusplus
}
#endif

#endif /*__HRS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
