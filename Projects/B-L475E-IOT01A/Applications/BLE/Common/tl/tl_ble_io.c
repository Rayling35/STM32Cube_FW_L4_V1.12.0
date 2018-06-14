/**
 ******************************************************************************
 * @file    tl_io.c
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

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "tl_types.h"
#include "tl_ble_io.h"
#include "hw.h"
#include "scheduler.h"
#include "svc_ctl.h"


/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Pubblic Functions Definition ----------------------------------------------*/



void TL_BLE_R_EvtProcReq(void)
{
  SCH_SetTask(CFG_IdleTask_TlEvt);

  return;
}

void TL_BLE_HCI_RxCmdResp()
{
  SCH_SetEvt(CFG_IdleEvt_HciCmdEvtResp);

  return;
}

void TL_BLE_HCI_ToNot(void)
{
  return;
}

void TL_BLE_HCI_WaitCmdResp(void)
{
  SCH_WaitEvt(CFG_IdleEvt_HciCmdEvtResp);

  return;
}

void TL_BLE_HCI_TimStop(uint8_t timerID)
{
  HW_TS_Delete(timerID);

  return;
}

void TL_BLE_HCI_TimStart(uint32_t expiryTime, void(*timercb)(void), uint8_t *timerID)
{
  HW_TS_Create(CFG_TimProcID_isr, timerID, hw_ts_SingleShot, (HW_TS_pTimerCb_t) timercb);
  HW_TS_Start(*timerID, expiryTime*1000/CFG_TS_TICK_VAL);

  return;
}


/**
 * @brief  This process shall be called by the scheduler each time it is requested with TL_BLE_HCI_UserEvtProcReq()
 *         This process may send an ACI/HCI command when the svc_ctl.c module is used
 *
 * @param  None
 * @retval None
 */
void TL_BLE_HCI_UserEvtProcReq( TL_PacketHeader_t *p_userevt_queue )
{
  SCH_SetTask(CFG_IdleTask_HciAsynchEvt);

  return;
}

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
void TL_BLE_HCI_UserEvtRx(void *pckt)
{
  SVCCTL_HCI_UserEvtRx(pckt);
}


/* __WEAK functions: The application can overload this function  if needed ----*/
/* ----------------------------------------------------------------------------*/

/**
 * @brief Informs to the application about the status of the TL (busy/available).
 *        The applicaiton shall not send a new command when the status is set to TL_BLE_HCI_CmdBusy.
 *        At least, TL_BLE_HCI_UserEvtProc shall not be executed while the TL remains busy
 *        This __WEAK function has to be OVERLOADED by the application, because only the application
 *        knows which TASKs are currently running and should be paused/resumed 
 * @param status
 * @retval None
 */
__weak void TL_BLE_HCI_StatusNot(TL_BLE_HCI_CmdStatus_t status)
{
  switch(status)
  {
    case TL_BLE_HCI_CmdBusy: 
      /* 
      Only the application knows which TASKs are currently running and should be paused   
      SCH_PauseTask( CFG_IdleTask_XXXX );
      SCH_PauseTask( CFG_IdleTask_YYYY );
      */
      SCH_PauseTask( CFG_IdleTask_HciAsynchEvt );
      break;

    case TL_BLE_HCI_CmdAvailable:
      /* 
      Only the application knows which TASKs are currently running and should be resumed   
      SCH_ResumeTask( CFG_IdleTask_XXXX );
      SCH_ResumeTask( CFG_IdleTask_YYYY );
      */
      SCH_ResumeTask( CFG_IdleTask_HciAsynchEvt );
      break;

    default:
      break;
  }
  return;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
