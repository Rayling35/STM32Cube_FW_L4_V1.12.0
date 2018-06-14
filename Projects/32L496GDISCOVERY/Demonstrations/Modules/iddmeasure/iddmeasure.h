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

/* Includes ------------------------------------------------------------------*/

#undef GLOBAL
#ifdef __LOWPOWER_APP_C
#define GLOBAL
#else
#define GLOBAL extern
#endif

/** @addtogroup  IDD_MEASURE_MODULE
  * @{
  */

/** @defgroup  IDD_MEASURE

  * @brief Idd Measure routines 
  * @{
  */

/* Exported typedef -----------------------------------------------------------*/
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

/* Exported defines -----------------------------------------------------------*/
#define IDD_RUN        0
#define IDD_SLEEP      IDD_RUN + 1
#define IDD_LPR_2MHZ   IDD_SLEEP + 1
#define IDD_LPR_SLEEP  IDD_LPR_2MHZ + 1
#define IDD_STOP2      IDD_LPR_SLEEP + 1
#define IDD_STANDBY    IDD_STOP2 + 1
#define IDD_SHUTDOWN   IDD_STANDBY + 1

#define IDD_TEST_NB  (IDD_SHUTDOWN + 1)

/* Exported macros ------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
GLOBAL uint32_t MfxFwVersion;
GLOBAL Idd_AppliTypedef IddTest[IDD_TEST_NB];
GLOBAL uint32_t iddTestIndex;
GLOBAL Idd_StateTypedef IddMeasureState;

/* Exported functions ---------------------------------------------------------*/
char* IddMeasureGetIDD(void);
void  IddMeasureDeInit(void);
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

