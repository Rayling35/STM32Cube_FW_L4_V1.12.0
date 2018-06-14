/**
 ******************************************************************************
 * @file    ble_config_template.h
 * @author  MCD Application Team
 * @brief   BLE configuration file
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
#ifndef __BLE_CONFIG_H
#define __BLE_CONFIG_H


/******************************************************************************
 *
 * BLE SERVICES CONFIGURATION
 * blesvc
 *
 ******************************************************************************/
/**
 * This setting shall be set to '1' if the device needs to support the Peripheral Role
 * In the MS configuration, both BLE_CFG_PERIPHERAL and BLE_CFG_CENTRAL shall be set to '1'
 */
#define BLE_CFG_PERIPHERAL                                                             1

/**
 * This setting shall be set to '1' if the device needs to support the Central Role
 * In the MS configuration, both BLE_CFG_PERIPHERAL and BLE_CFG_CENTRAL shall be set to '1'
 */
#define BLE_CFG_CENTRAL                                                                1


#define BLE_CFG_DATA_ROLE_MODE                    2

#define BLE_CFG_MENU_DEVICE_INFORMATION           0
/**
 * There is one handler per service enabled
 * Note: There is no handler for the Device Information Service
 *
 * This shall take into account all registered handlers
 * (from either the provided services or the custom services)
 */
#define BLE_CFG_SVC_MAX_NBR_CB      5

#define BLE_CFG_CLT_MAX_NBR_CB      0

/******************************************************************************
 * Device Information Service (DIS)
 ******************************************************************************/
/**< Number of characteristic added by the user */
#define BLE_CFG_DIS_NUMBER_OF_CUSTOM_CHAR                      0

/**< Options: Supported(1) or Not Supported(0) */
#define BLE_CFG_DIS_MANUFACTURER_NAME_STRING                                       1
#define BLE_CFG_DIS_MODEL_NUMBER_STRING                                            0
#define BLE_CFG_DIS_SERIAL_NUMBER_STRING                                           0
#define BLE_CFG_DIS_HARDWARE_REVISION_STRING                                       0
#define BLE_CFG_DIS_FIRMWARE_REVISION_STRING                                       0
#define BLE_CFG_DIS_SOFTWARE_REVISION_STRING                                       0
#define BLE_CFG_DIS_SYSTEM_ID                                                      0
#define BLE_CFG_DIS_IEEE_CERTIFICATION                                             0
#define BLE_CFG_DIS_PNP_ID                                                         0

/**
 * device information service characteristic lengths
 */
#define BLE_CFG_DIS_SYSTEM_ID_LEN_MAX                                                   (8)
#define BLE_CFG_DIS_MODEL_NUMBER_STRING_LEN_MAX                                         (32)
#define BLE_CFG_DIS_SERIAL_NUMBER_STRING_LEN_MAX                                        (32)
#define BLE_CFG_DIS_FIRMWARE_REVISION_STRING_LEN_MAX                                    (32)
#define BLE_CFG_DIS_HARDWARE_REVISION_STRING_LEN_MAX                                    (32)
#define BLE_CFG_DIS_SOFTWARE_REVISION_STRING_LEN_MAX                                    (32)
#define BLE_CFG_DIS_MANUFACTURER_NAME_STRING_LEN_MAX                                    (32)
#define BLE_CFG_DIS_IEEE_CERTIFICATION_LEN_MAX                                          (32)
#define BLE_CFG_DIS_PNP_ID_LEN_MAX                                                      (7)

/******************************************************************************
 * Heart Rate Service (HRS)
 ******************************************************************************/
#define BLE_CFG_HRS_NUMBER_OF_CUSTOM_CHAR    0 /**< Number of characteristic added by the user */

#define BLE_CFG_HRS_BODY_SENSOR_LOCATION_CHAR           1 /**< BODY SENSOR LOCATION CHARACTERISTIC */
#define BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG           1 /**< ENERGY EXTENDED INFO FLAG */
#define BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG             1 /**< Max number of RR interval values - Shall not be greater than 9 */


#endif /*__BLE_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
