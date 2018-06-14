/**
 ******************************************************************************
 * @file    tl_ble_hci.h
 * @author  MCD Application Team
 * @brief   Constants and functions for HCI layer. See Bluetooth Core
 *          v 4.0, Vol. 2, Part E.
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

#ifndef __TL_BLE_HCI_H_
#define __TL_BLE_HCI_H_

#include "tl_ble_io.h"

/* Exported Types -----------------------------------------------------------*/

typedef struct
{
  uint16_t ogf;
  uint16_t ocf;
  int32_t  event;
  void     *cparam;
  int32_t  clen;
  void     *rparam;
  int32_t  rlen;
} TL_BLE_HCI_Cmd_t;


/**
 * @brief  This API sends a HCI Command
 *
 * @param  p_cmd: Command definition
 * @retval int32_t: 0 when successful, -1 when the command times out
 */
int32_t TL_BLE_HCI_SendCmd( TL_BLE_HCI_Cmd_t *p_cmd );

/**
 * HCI LE Vendor Specific functions definition
 */

/**
 *********************************************************************************************************************
 * START OF SECTION - INTERFACES USED BY THE BLUENRG_BLE_DRIVER
 */

void TL_BLE_HCI_Init(TL_BLE_HCI_InitMode_t initmode, TL_CmdPacket_t * p_cmdbuffer, uint8_t *p_evtpool, uint32_t evtpoolsize);



/**
 * END OF SECTION - INTERFACES USED BY TBLUENRG_BLE_DRIVER
 *********************************************************************************************************************
 */

#endif /* __TL_BLE_HCI_H_ */
