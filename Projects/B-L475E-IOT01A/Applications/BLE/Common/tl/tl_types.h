/**
 ******************************************************************************
 * @file    tl_types.h
 * @author  MCD Application Team
 * @brief   Header for tl module
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
#ifndef __TL_TYPES_H
#define __TL_TYPES_H


/* Includes ------------------------------------------------------------------*/
/* Exported defines -----------------------------------------------------------*/
#define TL_BLECMD_PKT_TYPE  ( 0x01 )
#define TL_SYSCMD_PKT_TYPE  ( 0x10 )
#define TL_EVT_PKT_TYPE     ( 0x04 )

#define TL_EVT_HDR_SIZE     (3)
#define TL_EVT_CC_HDR_SIZE  (3)

#define TL_EVT_CC_OPCODE    (0x0E)
#define TL_EVT_CS_OPCODE    (0x0F)

#define TL_BLE_EVENT_FRAME_SIZE ( TL_EVT_HDR_SIZE + CFG_TLBLE_MOST_EVENT_PAYLOAD_SIZE )


/* Exported types ------------------------------------------------------------*/
#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint32_t *next;
  uint32_t *prev;
} TL_PacketHeader_t;


/*******************************************************************************
 * Event type
 */

/**
 * This the the payload of TL_Evt_t
 */
#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint8_t   status;
  uint8_t   numcmd;
  uint16_t  cmdcode;
} TL_CsEvt_t;

/**
 * This the the payload of TL_Evt_t
 */
#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint8_t   numcmd;
  uint16_t  cmdcode;
  uint8_t   payload[1];
} TL_CcEvt_t;

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint8_t   evtcode;
  uint8_t   plen;
  uint8_t   payload[1];
} TL_Evt_t;

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint8_t   type;
  TL_Evt_t  evt;
} TL_EvtSerial_t;

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  TL_PacketHeader_t  header;
  TL_EvtSerial_t     evtserial;
} TL_EvtPacket_t;

/*****************************************************************************************
 * Command type
 */

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint16_t   cmdcode;
  uint8_t   plen;
  uint8_t   payload[255];
} TL_Cmd_t;

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  uint8_t   type;
  TL_Cmd_t  cmd;
} TL_CmdSerial_t;

#ifdef __GNUC__
typedef struct __packed {
#else
typedef __packed struct{
#endif
  TL_PacketHeader_t  header;
  TL_CmdSerial_t     cmdserial;
} TL_CmdPacket_t;


#endif /*__TL_TYPES_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
