/**
 ******************************************************************************
 * @file    lb_demo.h
 * @author  MCD Application Team
 * @brief   Header for lb_demo.c module
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright c 2017 STMicroelectronics International N.V.
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
#ifndef __LB_DEMO_H
#define __LB_DEMO_H

#include "ble_status.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef enum
{
  LBR_Limited,
  LBR_Full,
} LBR_InitMode_t;

 typedef struct{
    uint8_t                                     Device_Led_Selection;
    uint8_t                                     Led1Control;
   
 }LBR_LedCharValue_t;
 
 typedef struct{
    uint8_t                                     Device_Button_Selection;
    uint8_t                                     ButtonStatus;
 }LBR_ButtonCharValue_t;

typedef enum
{
  LB_SERVER_CONN_HANDLE_EVT,
  LB_SERVER_DISCON_EVT,
  LB_CLIENT_CONN_HANDLE_EVT, //used with end device
  LB_CLIENT_DISCON_EVT_EVT,  //used with end device
} LBR_Opcode_Notification_evt_t;

typedef struct
{
  LBR_Opcode_Notification_evt_t               LBR_Evt_Opcode;
  uint16_t                                    ConnectionHandle;
}LBR_ConnHandle_Not_evt_t;


/* Exported types LBR Client Implementation-----------------------------------*/

typedef enum
{  
  LBC_IDLE                            = 0,
  LBC_DISCOVER_SERVICES               = 1,
  LBC_DISCOVER_CHARACS                = 2,
  LBC_DISCOVER_LED_CHAR_DESC          = 3,
  LBC_DISCOVER_BUTTON_CHAR_DESC       = 4,
  LBC_ENABLE_NOTIFICATION_BUTTON_DESC = 5,
  LBC_DISABLE_NOTIFICATION_TX_DESC    = 6,
  LBC_ADV                             = 7,
  LBC_SCAN                            = 8,
  LBC_CONNECTING                      = 9,
  LBC_CONNECTED                       = 10,    
} LBR_Gap_Gatt_State;
  
typedef enum
{
  LBC_START_TIMER_EVT,
  LBC_STOP_TIMER_EVT,
  LBC_BUTTON_INFO_RECEIVED_EVT,
} LBR_Client_Opcode_Notification_evt_t;

typedef struct
{
  uint8_t * pPayload;
  uint8_t     Length;
}LBR_Client_Data_t;  

typedef struct
{
  LBR_Client_Opcode_Notification_evt_t  LBR_Client_Evt_Opcode;
  LBR_Client_Data_t DataTransfered;
  uint8_t   ServiceInstance;
}LBR_Client_App_Notification_evt_t;

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define LBR_CLIENT_LEN_MAX       (20)

/* Exported functions ------------------------------------------------------- */
void LBR_Background( void );
void LBR_Init( LBR_InitMode_t init_mode );
void LBSAPP_Init(void);
void LBR_Notification(LBR_ConnHandle_Not_evt_t *pNotification);
void LBR_App_Key_Button_Action(void);

void LBR_AdvUpdate( void );


void LBR_Adv_Request(void);
void LBR_AppConnReq1(void);
void LBR_AppConnReq2(void);
void LBR_AppStartLimitedDiscReq(void);

void LBR_Client_Init(void);
void LBR_Client_Update_Service(void);
tBleStatus LBR_Client_Update_Char(uint16_t UUID, uint8_t Service_Instance, uint8_t *pPayload);
void LBR_Client_App_Notification(LBR_Client_App_Notification_evt_t *pNotification);
LBR_Gap_Gatt_State LBR_Get_Client_Connection_Status(uint16_t Connection_Handle);


#ifdef __cplusplus
}
#endif

#endif /*__LB_DEMO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
