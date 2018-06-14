/**
  ******************************************************************************
  * @file    hrs_app.c
  * @author  MCD Application Team
  * @brief   Heart Rate Service Application
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
#include "hw.h"

#include "hrs_app.h"
#include "ble_lib.h"
#include "blesvc.h"
#include "scheduler.h"

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  HRS_BodySensorLocation_t BodySensorLocationChar;
  HRS_MeasVal_t MeasurementvalueChar;
  uint8_t ResetEnergyExpended;
  uint8_t TimerMeasurement_Id;

} HRSAPP_Context_t;


/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define HRSAPP_MEASUREMENT_INTERVAL   (1000000/CFG_TS_TICK_VAL)  /**< 1s */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */
static HRSAPP_Context_t HRSAPP_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void HrMeas( void );
static uint32_t HRSAPP_Read_RTC_SSR_SS( void );

/* Functions Definition ------------------------------------------------------*/
/* Private functions ----------------------------------------------------------*/

static void HrMeas( void )
{
  /**
   * The code shall be executed in the background as aci command may be sent
   * The background is the only place where the application can make sure a new aci command
   * is not sent if there is a pending one
   */
  SCH_SetTask(CFG_IdleTask_MeasReq);

  return;
}

static uint32_t HRSAPP_Read_RTC_SSR_SS ( void )
{
  return (LL_RTC_TIME_GetSubSecond( RTC ));
}

/* Public functions ----------------------------------------------------------*/

void HRS_Notification(HRS_NotCode_t Notification)
{
  switch(Notification)
  {
#if (BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG != 0)
    case HRS_RESET_ENERGY_EXPENDED_EVT:
      HRSAPP_Context.MeasurementvalueChar.EnergyExpended = 0;
      HRSAPP_Context.ResetEnergyExpended = 1;
      break;
#endif
      
    case HRS_NOTIFICATION_ENABLED:
      /**
       * It could be the enable notification is received twice without the disable notification in between
       */
      HW_TS_Stop(HRSAPP_Context.TimerMeasurement_Id);
      HW_TS_Start(HRSAPP_Context.TimerMeasurement_Id, HRSAPP_MEASUREMENT_INTERVAL);
      break;

    case HRS_NOTIFICATION_DISABLED:
      HW_TS_Stop(HRSAPP_Context.TimerMeasurement_Id);
      break;

   default:
      break;
  }

  return;
}

void HRSAPP_Init(void)
{
  /**
   * Set Body Sensor Location
   */
  HRSAPP_Context.ResetEnergyExpended = 0;
  HRSAPP_Context.BodySensorLocationChar = HRS_BODY_SENSOR_LOCATION_HAND;
  HRS_UpdateChar(SENSOR_LOCATION_UUID, (uint8_t *)&HRSAPP_Context.BodySensorLocationChar);


  /**
   * Set Flags for measurement value
   */
/*  HRSAPP_Context.MeasurementvalueChar.Flags = (HRS_HRM_VALUE_FORMAT_UINT16 | 
                                                 HRS_HRM_SENSOR_CONTACT_PRESENT);
*/
  HRSAPP_Context.MeasurementvalueChar.Flags = (   HRS_HRM_SENSOR_CONTACT_PRESENT   | 
                                                  HRS_HRM_SENSOR_CONTACT_SUPPORTED |
                                                  HRS_HRM_ENERGY_EXPENDED_PRESENT  |
                                                  HRS_HRM_RR_INTERVAL_PRESENT );

#if (BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG != 0)
  if(HRSAPP_Context.MeasurementvalueChar.Flags & HRS_HRM_ENERGY_EXPENDED_PRESENT)
    HRSAPP_Context.MeasurementvalueChar.EnergyExpended = 10;
#endif
  
#if (BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG != 0)
  if(HRSAPP_Context.MeasurementvalueChar.Flags & HRS_HRM_RR_INTERVAL_PRESENT)
  {
    uint8_t i;
    
    HRSAPP_Context.MeasurementvalueChar.NbreOfValidRRIntervalValues = BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG;
    for(i = 0; i < BLE_CFG_HRS_ENERGY_RR_INTERVAL_FLAG; i++)
      HRSAPP_Context.MeasurementvalueChar.aRRIntervalValues[i] = 1024;
  }
#endif
  
  /**
   * Create timer for Heart Rate Measurement
   */
  HW_TS_Create(CFG_TimProcID_isr, &(HRSAPP_Context.TimerMeasurement_Id), hw_ts_Repeated, HrMeas);

  return;
}

void HRSAPP_Measurement(void)
{
  uint32_t measurement;

  measurement = ((HRSAPP_Read_RTC_SSR_SS()) & 0x07) + 65;

  HRSAPP_Context.MeasurementvalueChar.MeasurementValue = measurement;
#if (BLE_CFG_HRS_ENERGY_EXPENDED_INFO_FLAG != 0)
  if((HRSAPP_Context.MeasurementvalueChar.Flags & HRS_HRM_ENERGY_EXPENDED_PRESENT) &&
     (HRSAPP_Context.ResetEnergyExpended == 0))
    HRSAPP_Context.MeasurementvalueChar.EnergyExpended += 5;
  else if(HRSAPP_Context.ResetEnergyExpended == 1)
    HRSAPP_Context.ResetEnergyExpended = 0;
#endif

  if(HRSAPP_Context.MeasurementvalueChar.Flags & HRS_HRM_SENSOR_CONTACT_SUPPORTED)
  {
    if(HRSAPP_Context.MeasurementvalueChar.Flags & HRS_HRM_SENSOR_CONTACT_PRESENT)
    {
      HRSAPP_Context.MeasurementvalueChar.Flags &= ~HRS_HRM_SENSOR_CONTACT_PRESENT;
    }
    else
    {
      HRSAPP_Context.MeasurementvalueChar.Flags |= HRS_HRM_SENSOR_CONTACT_PRESENT;
    }
  }
  HRS_UpdateChar(HEART_RATE_MEASURMENT_UUID, (uint8_t *)&HRSAPP_Context.MeasurementvalueChar);

  return;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
