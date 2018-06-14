/**
 ******************************************************************************
 * @file    tl_ble_io.h
 * @author  MCD Application Team
 * @brief   buttom wrapper to abstract TL from HW and SCHeduler
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

#ifndef __TL_BLE_IO_H_
#define __TL_BLE_IO_H_


/* Exported Types -----------------------------------------------------------*/
typedef enum
{
  TL_BLE_HCI_CmdBusy,
  TL_BLE_HCI_CmdAvailable
} TL_BLE_HCI_CmdStatus_t;

typedef enum
{
  TL_BLE_HCI_InitLimited,
  TL_BLE_HCI_InitFull,
} TL_BLE_HCI_InitMode_t;


/**
 * HCI LE Vendor Specific functions definition
 */

/**
 * @brief Informs to the application about the status of the TL (busy/available).
 *        The applicaiton shall not send a new command when the status is set to TL_BLE_HCI_CmdBusy.
 *        At least, TL_BLE_HCI_UserEvtProc shall not be executed while the TL remains busy
 *        This __WEAK function has to be OVERLOADED by the application, because only the application
 *        knows which TASKs are currently running and should be paused/resumed 
 * @param status
 * @retval None
 */
void TL_BLE_HCI_StatusNot(TL_BLE_HCI_CmdStatus_t status);

/**
 * @brief  This callback is triggered when a user event is received from the BlueNRG. It requests the process
 *         TL_BLE_HCI_UserEvtProc() to be executed.
 *         It is called from TL_BLE_R_EvtProc() context.
 *
 * @param  p_userevt_queue: The queue where the user event are posted
 * @retval None
 */
void TL_BLE_HCI_UserEvtProcReq(TL_PacketHeader_t *p_userevt_queue);

/**
 * @brief  This callback is triggered when an ACI/HCI command is sent and the response is waited from the BlueNRG
 *         The application shall implement a mechanism to not return for that callback until the waited event is received
 *         This is notified to the application with TL_BLE_HCI_RxCmdResp()
 *         It is called from the same context the HCI command has been sent.
 *
 * @param  None
 * @retval None
 */
void TL_BLE_HCI_WaitCmdResp(void);

/**
 * @brief  This callback is triggered when an ACI/HCI command is sent and the response is waited from the BlueNRG
 *         The application shall implement a mechanism to not return for that callback until the waited event is received
 *         This is notified to the application with TL_BLE_HCI_RxCmdResp()
 *         It is called from either:
 *         The RTC handler context - (This only happens when there is a HCI Layer Timeout).
 *         TL_BLE_R_EvtProc() context
 *
 * @param  None
 * @retval None
 */
void TL_BLE_HCI_RxCmdResp(void);

/**
 * @brief  This callback is triggered when there is a HCI Layer Timeout. The HCI Layer Timeout occurs each time the
 *         HCI Layer is not available in time after a command has been sent. The default timeout is DEFAULT_TIMEOUT (33s)
 *         from hci.c
 *         It is called from the RTC handler context.
 *
 * @param  None
 * @retval None
 */
void TL_BLE_HCI_ToNot(void);


/**
 * @brief  It requests a Timer to be created an started with the given parameter. It shall not be restarted when the
 *         timeout occurs. This timer is used to timeout all ACI/HCI command sent to the BlueNRG coprocessor.
 *
 *         It is called each time an ACI/HCI command is sent to the BlueNRG. The context is the same than the context
 *         from where the command has been sent.
 *
 * @param  expiryTime: The timeout of the timer
 * @param  timercb: The callback to be called when the timer expires
 * @param  timerID: The Id of the timer to be used to Stop the timer if needed
 * @retval None
 */
void TL_BLE_HCI_TimStart(uint32_t expiryTime, void(*timercb)(void), uint8_t *timerID);

/**
 * @brief  It requests the timer to be deleted. The timer is deleted each time the BlueNRG coprocessor replied to the
 *         command before the timeout.
 *
 *         It is called each time an ACI/HCI command is sent to the BlueNRG. The context is the same than the context
 *         from where the command has been sent.
 *
 * @param  timerID: The Id of the timer to be used to Stop the timer if needed
 * @retval None
 */
void TL_BLE_HCI_TimStop(uint8_t timerID);


/**
 * @brief  This process shall be called by the scheduler each time it is requested with TL_BLE_HCI_UserEvtProcReq()
 *         This process may send an ACI/HCI command when the svc_ctl.c module is used
 *
 * @param  None
 * @retval None
 */

void TL_BLE_HCI_UserEvtProc(void);

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
void TL_BLE_HCI_UserEvtRx(void *pckt);  

#endif /* __TL_BLE_IO_H_ */
