/**
 ******************************************************************************
 * @file    lb_client_app.c
 * @author  MCD Application Team
 * @brief   Led Button Demo - Routeur Application
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
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
#include "debug.h"

#include "lb_client_app.h"
#include "lb_demo.h"

#include "ble_lib.h"
#include "blesvc.h"
#include "scheduler.h"
#include "stm32l475e_iot01.h"

#if (LB_CLIENT != 0) /**< LED BOUTTON ROUTER APPLICATION  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t                Notification_Button_Status; /* used to chek if smart phone can receive push button information */
  LBR_LedCharValue_t     LedControlRemoteServer;
  uint16_t               connHandleWithserver; 
  uint8_t                connStatusWithServer; 
} LB_Client_Context_t;


/* Private defines -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
 * START of Section BLE_APP_CONTEXT
 */
static LB_Client_Context_t LB_Client_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
/* Private functions ----------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


void LBR_Notification(LBR_ConnHandle_Not_evt_t *pNotification)
{
  switch(pNotification->LBR_Evt_Opcode)
  {
    case LB_SERVER_CONN_HANDLE_EVT:
       LB_Client_Context.connHandleWithserver = pNotification->ConnectionHandle; 
       LB_Client_Context.connStatusWithServer = 0x01; //connected
       
    break;
      
    case LB_SERVER_DISCON_EVT :
      LB_Client_Context.connHandleWithserver = 0x00;
      LB_Client_Context.connStatusWithServer = 0x00; //Not connected
      
      //restart Create Connection
      SCH_SetTask(CFG_IdleTask_ConnDev1);
    break;
  
    default:
      break;
  }

  return;
}

void LBSAPP_Init(void)
{
  /**
   * Initialize LedButton Service
   */
  LB_Client_Context.Notification_Button_Status=0; 
  
  LB_Client_Context.connHandleWithserver=0x00;
  LB_Client_Context.connStatusWithServer=0x00;
  
  LB_Client_Context.LedControlRemoteServer.Device_Led_Selection=0x01;
  LB_Client_Context.LedControlRemoteServer.Led1Control=0x01;
  
  return;
}

void LB_App_Button_Trigger_Received(void)
{

  if(LB_Client_Context.connStatusWithServer == 0x01  ){
    if( LB_Client_Context.LedControlRemoteServer.Led1Control==0x00){
      LB_Client_Context.LedControlRemoteServer.Led1Control=0x01;
    } else {
      LB_Client_Context.LedControlRemoteServer.Led1Control=0x00;
    }
               
        APPL_MESG_DBG("-- APPLICATION CLIENT : WRITE LED CONFIG TO SERVER\n\r");
        LBR_Client_Update_Char( LED_CHAR_UUID, 0, (uint8_t *)&LB_Client_Context.LedControlRemoteServer); 
   
  }
  
}



/* CLIENT LED Button*/
/*-------------------*/
void LBR_Client_App_Notification(LBR_Client_App_Notification_evt_t *pNotification)
{
  switch(pNotification->LBR_Client_Evt_Opcode)
  {
    case LBC_BUTTON_INFO_RECEIVED_EVT:
      {
        switch(pNotification->DataTransfered.pPayload[1]) {
        case 0x00 : 
          BSP_LED_Off(LED2);
          break;
        case 0x01 : 
          BSP_LED_On(LED2);
          break;
        
        default : break;
        }
       
      }
      break;
   
    default:
      break;
 
  }
  return;
}


#endif //LB_CLIENT

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
