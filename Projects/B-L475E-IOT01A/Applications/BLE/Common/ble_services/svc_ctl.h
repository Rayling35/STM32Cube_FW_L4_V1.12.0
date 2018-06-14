
/**
 ******************************************************************************
 * @file    svc_ctl.h
 * @author  MCD Application Team
 * @brief   Header for ble_controller.c module
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

/**
 * The BLE Controller supports the application to handle services and clients.
 * It provides an API to initialize the BlueNRG Device and a handler mechanism to rout the GATT/GAP events to the
 * application. When the ble_controller is used (recommended), the application shall register a callback for each
 * Service and each Client implemented. This is already done with the Services and Clients provided in that delivery.
 *  + A GATT event is relevant to only one Service and/or one Client. When a GATT event is received, it is notified to
 *    the registered handlers to the BLE controller. When no registered handler acknowledges positively the GATT event,
 *    it is reported to the application.
 *  + A GAP event is not relevant to either a Service or a Client. It is sent to the application
 *  + In case the application does not want to take benefit from the ble_controller, it could bypass it. In that case,
 *  the application shall:
 *    - call  SVCCTL_Init() to initialize the BlueNRG device (or implement on its own what is inside that function
 *    - implement TLHCI_UserEvtRx() which is the notification from the HCI layer to report all events (GATT/GAP).
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SVCCTL_H
#define __SVCCTL_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  typedef enum
  {
    SVCCTL_EvtNotAck,
    SVCCTL_EvtAck,
  } SVCCTL_EvtAckStatus_t;

  typedef SVCCTL_EvtAckStatus_t (*SVC_CTL_p_EvtHandler_t)(void *p_evt);

  /* Exported constants --------------------------------------------------------*/
  /* External variables --------------------------------------------------------*/
  /* Exported macros -----------------------------------------------------------*/

  /* Exported functions ------------------------------------------------------- */
  /**
   * @brief  It initializes the BlueNRG Driver and sends some commands to initialize the BlueNRG device
   *         It shall be called before any BLE operation
   *
   * @param  None
   * @retval None
   */
  void SVCCTL_Init( void );

  /**
   * @brief  This API registers a handler to be called when a GATT user event is received from the BlueNRG device. When
   *         a Service is created, it shall register a callback to be notified when a GATT event is received from the
   *         BlueNRG device. When a GATT event is received, it shall be checked in the handler if the GATT events belongs
   *         to the Service or not. The handler shall return the correct status depending on the result. As soon as one
   *         Service handler registered acknowledges positively the GATT event, the ble_controller stops calling the
   *         registered Service handlers.
   *         This handler is called in the TL_BLE_HCI_UserEvtProc() context
   *
   * @param  pfBLE_SVC_Service_Event_Handler: This is the Service handler that the ble_controller calls to report a GATT
   *         event received. If the GATT event belongs to that Service, the callback shall return positively with
   *         SVCCTL_EvtAck.
   * @retval None
   */
  void SVCCTL_RegisterSvcHandler(SVC_CTL_p_EvtHandler_t pfBLE_SVC_Service_Event_Handler);

  /**
   * @brief  This API registers a handler to be called when a GATT user event is received from the BlueNRG device. When
   *         a Client is created, it shall register a callback to be notified when a GATT event is received from the
   *         BlueNRG device. When a GATT event is received, it shall be checked in the handler if the GATT events belongs
   *         to the Client or not. The handler shall return the correct status depending on the result. As soon as one
   *         Client handler registered acknowledges positively the GATT event, the ble_controller stops calling the
   *         registered Client handlers.
   *         This handler is called in the TL_BLE_HCI_UserEvtProc() context
   *
   * @param  pfBLE_SVC_Client_Event_Handler: This is the Client handler that the ble_controller calls to report a GATT
   *         event received. If the GATT event belongs to that Client, the callback shall return positively with
   *         SVCCTL_EvtAck.
   * @retval None
   */
  void SVCCTL_RegisterCltHandler(SVC_CTL_p_EvtHandler_t pfBLE_SVC_Client_Event_Handler);

  /**
   * @brief This callback is triggered when either
   *          + a GAP event is received from the BlueNRG device.
   *          + a GATT event that has not been positively acknowledged by the registered handler is received from the
   *            BlueNRG device.
   *        The event is returned in a HCI packet. The full HCI packet is stored in a single buffer and is available when
   *        this callback is triggered. However, an ACI event may be longer than a HCI packet and could be fragmented over
   *        several HCI packets. The HCI layer only handles HCI packets so when an ACI packet is split over several HCI
   *        packets, this callback is triggered for each HCI fragment. It is the responsibility of the application to
   *        reassemble the ACI event.
   *        This callback is triggered in the TL_BLE_HCI_UserEvtProc() context
   *
   * @param  pckt: The user event received from the BlueNRG device
   * @retval None
   */
  void SVCCTL_App_Notification(void *pckt);
  
/**
 * @brief This callback is triggered when an user event is received from the BlueNRG device. The event is returned in
 *        a HCI packet. The full HCI packet is stored in a single buffer and is available when this callback is triggered.
 *        However, an ACI event may be longer than a HCI packet and could be fragmented over several HCI packets.
 *        The HCI layer only handles HCI packets so when an ACI packet is split over several HCI packets, this callback
 *        is triggered for each HCI fragment. It is the responsibility of the application to reassemble the ACI event.
 *        This callback is triggered in the TL_BLE_HCI_UserEvtProc() context
 *
 * @param  pckt: The user event received from the BlueNRG device
 * @retval None
 */
  void SVCCTL_HCI_UserEvtRx(void *pckt);  

  /**
   * @brief Request the BLE BD Address from the application
   *        The content of the reference shall not be changed after this API is called
   *
   * @param  None
   * @retval Reference of the LSB of the BD Address
   * @note  The application can overload this function for example 
            in case it needs to retrieve the value from OTP 
            instead of using the harcoded value in the config.h
   */
  const uint8_t* SVCCTL_GetBdAddress( void );



#ifdef __cplusplus
}
#endif

#endif /*__SVCCTL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
