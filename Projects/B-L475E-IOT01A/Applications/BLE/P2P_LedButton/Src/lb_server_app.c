/**
 ******************************************************************************
 * @file    lb_server_app.c
 * @author  MCD Application Team
 * @brief   Led Button End Device Application
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

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "debug.h"

#include "lb_server_app.h"
#include "lb_demo.h"

#include "ble_lib.h"
#include "blesvc.h"
#include "scheduler.h"
#include "stm32l475e_iot01.h"


#if (LB_SERVER != 0) /**< LED BOUTTON END DEVICE APPLICATION  */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  uint8_t       Notification_Button_Status; // used to chek if LB Router can received push button information
  LBR_ButtonCharValue_t      ButtonStatusToClient;
  uint16_t connHandleWithLbRouteur; //Smart Phone 1
} LB_End_Dev_Context_t;

/* Private defines -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
 * START of Section BLE_APP_CONTEXT
 */
static LB_End_Dev_Context_t LB_End_Dev_Context;

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
    case LB_CLIENT_CONN_HANDLE_EVT :
      LB_End_Dev_Context.connHandleWithLbRouteur = pNotification->ConnectionHandle;
      break;

    case LB_CLIENT_DISCON_EVT_EVT :
      LB_End_Dev_Context.connHandleWithLbRouteur =  0x00;
      SCH_SetTask(CFG_IdleTask_StartAdv);
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
  LB_End_Dev_Context.Notification_Button_Status=0; 
  LB_End_Dev_Context.connHandleWithLbRouteur =  0x00;
 // LB_End_Dev_Context.LedControlEndDevice1.Device_Led_Selection=0x01; // device1
//  LB_End_Dev_Context.LedControlEndDevice1.Led1Control=0x00; //led OFF
  LB_End_Dev_Context.ButtonStatusToClient.Device_Button_Selection=0x01; //Device1
  LB_End_Dev_Context.ButtonStatusToClient.ButtonStatus=0x00;

  return;
}

void LB_App_Button_Trigger_Received(void)
{
  
  //UPDATE BUTTON CHARACTERISTICS VALUES

  if(LB_End_Dev_Context.ButtonStatusToClient.ButtonStatus==0x01){
  LB_End_Dev_Context.ButtonStatusToClient.ButtonStatus=0x00;}
  else {
  LB_End_Dev_Context.ButtonStatusToClient.ButtonStatus=0x01;  
  }
  LB_End_Dev_Context.ButtonStatusToClient.Device_Button_Selection=0x01; //Button1 pushed
  APPL_MESG_DBG("\r\n\r ");
  APPL_MESG_DBG("-- APPLICATION : BUTTON PUSHED - CHECK NOTIFICATION \n ");
 
   if(LB_End_Dev_Context.Notification_Button_Status){ 
    APPL_MESG_DBG("-- APPLICATION : INFORM ROUTEUR BUTTON 1 PUSHED \n ");
    BLE_SVC_LedButton_Update_Char(BUTTON_CHAR_UUID, (uint8_t *)&LB_End_Dev_Context.ButtonStatusToClient);
   } else {
    APPL_MESG_DBG("-- APPLICATION : CAN'T INFORM ROUTEUR -  NOTIFICATION DISABLED\n "); 
   }

  return;
}


/* ******************************************************************************/
/* ******  Exported functions to OVERLOAD __weak defined in /Common modules *****/
/* ******************************************************************************/

/**
  * @brief  This function implement the application action when app notification
  *         It OVERLOADS the __WEAK function defined in lbs_stm.h/c
  *         When this function is called meas that the "Button characteristic"
  *         has been enabled or disabled. The application can take 
  *         correspondent action
  * @param  pNotification: LBS notification.
  * @retval None
 */ 
void LBS_App_Notification(LBS_App_Notification_evt_t *pNotification)
{
  switch(pNotification->LBS_Evt_Opcode)
  {
    case BUTTON_NOTIFY_ENABLED_EVT:
      LB_End_Dev_Context.Notification_Button_Status = 1;
      APPL_MESG_DBG("-- APPLICATION END DEVICE : BUTTON NOTIFICATION ENABLED\n");      
      break;

    case BUTTON_NOTIFY_DISABLED_EVT:
      LB_End_Dev_Context.Notification_Button_Status = 0;
      APPL_MESG_DBG("-- APPLICATION END DEVICE : BUTTON NOTIFICATION DISABLED\n");
      break;

    case ST_SVC_LED_READ_EVT:
      /*Create Function to respond to Client-LB Routeur the status of each Led*/
      break;

    case ST_SVC_LED_WRITE_EVT:
      /* create function to switch ON/OFF Leds on selected device. */
      if(pNotification->DataTransfered.pPayload[0] == 0x01){ 
        if(pNotification->DataTransfered.pPayload[1] == 0x01)
        {
          BSP_LED_On(LED2);
          APPL_MESG_DBG("-- APPLICATION END DEVICE 1 : LED1 ON\n"); 
        }
        if(pNotification->DataTransfered.pPayload[1] == 0x00)
        {
          BSP_LED_Off(LED2);
          APPL_MESG_DBG("-- APPLICATION END DEVICE 1 : LED1 OFF\n"); 
        }
      }
      break;

    default:
      break;
  }
  return;
}

#endif //END_DEVICE

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
