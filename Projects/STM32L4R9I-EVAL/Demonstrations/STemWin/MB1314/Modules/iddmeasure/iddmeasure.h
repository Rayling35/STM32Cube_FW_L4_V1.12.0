/**
  ******************************************************************************
  * @file    iddmeasure.h
  * @author  MCD Application Team   
  * @brief   Idd Measurement functions
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
#ifndef __IDD_MEASURE_H
#define __IDD_MEASURE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>

/** @addtogroup  IDD_MEASURE_MODULE
  * @{
  */

/** @defgroup  IDD_MEASURE

  * @brief Idd Measure routines 
  * @{
  */

/* Exported defines -----------------------------------------------------------*/
#define IDD_VALUE_STRING_SIZE 4
#define IDD_UNIT_STRING_SIZE 2
    
/* Exported typedef -----------------------------------------------------------*/
typedef enum
{
  IDD_RUN = 0,
  IDD_SLEEP,
  IDD_LPR_2MHZ,
  IDD_LPR_SLEEP,
  IDD_STOP2,
  IDD_STANDBY,
  IDD_SHUTDOWN,
  IDD_GETIDD_AFTER_RESET,
}IddAction_t;
    
#define IDD_TEST_NB  (IDD_SHUTDOWN + 1)

typedef struct  
{
  char value[IDD_VALUE_STRING_SIZE + 1];  /* 3 significant digit only */
  char unit[IDD_UNIT_STRING_SIZE + 1];    /* 2 letters */
  uint32_t value_na;                      /* value in nano amps */
  uint8_t error_code;                     /* 0 means no error else see mfx documentation 
                                             In case of error please retry */
} Iddvalue_t;

    
typedef struct
{
  void   (*IddEnter)(void);
  void   (*IddRestore)(void);
  char modeStr[20];
  uint32_t index;
  uint32_t userData1;
}Idd_AppliTypedef;

typedef enum
{
  IDD_STATE_IDLE = 0,
  IDD_STATE_MEASURE_ON_GOING = 1,
  IDD_STATE_MEASURE_OK = 2,
  IDD_STATE_MEASURE_ERROR = 3,
}Idd_StateTypedef;    
    
/* Exported macros ------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
void IddMeasureStart(void);
void IddMeasureGetValue(Iddvalue_t * idd);
Idd_StateTypedef IddMeasureGetState();
uint32_t IddMeasure_isSignature(void); /* Automatically restore index if TRUE */
void IddMeasure_clearSignature(void);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __IDD_MEASURE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

