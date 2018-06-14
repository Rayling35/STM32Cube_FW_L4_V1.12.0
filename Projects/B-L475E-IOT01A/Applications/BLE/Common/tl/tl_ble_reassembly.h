/**
 ******************************************************************************
 * @file    tl_ble_reassembly.h
 * @author  MCD Application Team
 * @brief   Header for tl_serial.c module
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
#ifndef __TL_BLE_REASSEMBLY_H
#define __TL_BLE_REASSEMBLY_H


/* Includes ------------------------------------------------------------------*/
#include "tl_types.h"

/* Exported defines -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
  TL_BLE_R_HciAsynchEvt,
  TL_BLE_R_HciCmdEvt
}TL_BLE_R_EvtPacketType_t;

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**
 *********************************************************************************************************************
 * START OF SECTION - PROCESS TO BE CALLED BY THE SCHEDULER
 */

/**
 * @brief  This process shall be called by the scheduler each time it is requested with TL_BLE_R_EvtProcReq()
 *         This process does not send any ACI/HCI command so it can be executed without checking the availability of
 *         the HCI Layer
 *
 * @param  None
 * @retval None
 */
void TL_BLE_R_EvtProc(void);

/**
 * END OF SECTION - PROCESS TO BE CALLED BY THE SCHEDULER
 *********************************************************************************************************************
 */

/**
 * @brief  This callback is triggered when an event is received from the BlueNRG. It requests the process TL_BLE_HCI_UserEvtProc()
 *         to be executed.
 *         It is called from either:
 *         HW_BNRG_DMARxCb - RX DMA interrupt handler
 *         TimerTxRxCallback - RTC interrupt handler
 *         TL_BLE_R_EvtProc() context.
 *
 * @param  None
 * @retval None
 */
void TL_BLE_R_EvtProcReq(void);

void TL_BLE_R_EvtInput(TL_BLE_R_EvtPacketType_t hci_evt_packet_type, uint8_t *hci_evt_buffer);
void TL_BLE_R_Init(TL_CmdPacket_t * cmdbuffer);
void TL_BLE_R_EvtDone(TL_EvtPacket_t * hcievt);

#endif /*__TL_BLE_REASSEMBLY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
