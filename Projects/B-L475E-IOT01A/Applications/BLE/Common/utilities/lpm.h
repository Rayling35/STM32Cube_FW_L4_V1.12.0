/**
 ******************************************************************************
 * @file    lpm.h
 * @author  MCD Application Team
 * @brief   Header for stm32xx_lpm.c module
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
#ifndef __LPM__H
#define __LPM__H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
  /* Exported types ------------------------------------------------------------*/
  /**
   * MCU Off Mode Selection
   */
  typedef enum
  {
    LPM_OffMode_Dis,  /** Restart from where it stops on wakeup */
    LPM_OffMode_En    /** Restart from reset on wakeup */
  } LPM_OffModeSel_t;

  /**
   * System clock Selection
   */
  typedef enum
  {
    LPM_StopMode_Dis, /** Sysclock is disabled when in low power mode */
    LPM_StopMode_En   /** Sysclock is kept enabled when in low power mode */
  } LPM_StopModeSel_t;

  /**
   * Low Power Mode selected
   */
  typedef enum
  {
    LPM_SleepMode,
    LPM_StopMode,
    LPM_OffMode,
  } LPM_ModeSelected_t;

  /**
   * Low Power Mode configuration
   */
  typedef struct
  {
    uint32_t Stop_Mode_Config;
    uint32_t OFF_Mode_Config;
  } LPM_Conf_t;

  /* Exported constants --------------------------------------------------------*/
  /* External variables --------------------------------------------------------*/
  /* Exported macros -----------------------------------------------------------*/
  /* Exported functions ------------------------------------------------------- */
  /**
   * @brief  This API returns the Low Power Mode selected that will be applied when the system will enter low power mode
   *         if there is no update between the time the mode is read with this API and the time the system enters
   *         low power mode.
   * @param  None
   * @retval LPM_ModeSelected_t
   */
  LPM_ModeSelected_t LPM_ReadModeSel(void);

  /**
   * @brief  This API notifies the low power manager if the specified user allows the Off mode or not.
   *         When the application does not require the system clock, it enters Stop Mode if at least one user disallow
   *         Off Mode. Otherwise, it enters Off Mode.
   *         The default mode selection for all users is Off mode enabled
   * @param  id: process Id - value shall be between 0 and 31
   * @param  mode: mode selected
   * @retval None
   */
  void LPM_SetOffMode(uint32_t id, LPM_OffModeSel_t mode);

  /**
   * @brief  This API notifies the low power manager if the specified user allows the System clock to be switched Off
   *         or not when entering low power mode. When the System clock is requested by at least one user, the system
   *         enters Sleep mode. Otherwise, it enters either Stop Mode or Off Mode.
   *         The default System clock request for all users is set to System clock switched Off
   * @param  id: process Id - value shall be between 0 and 31
   * @param  mode: System Clock Activty
   * @retval None
   */
  void LPM_SetStopMode(uint32_t id, LPM_StopModeSel_t mode);

  /**
   * @brief  This API shall be used by the application when there is no more code to execute so that the system may
   *         enter low-power mode. The mode selected depends on the information received from LPM_SetOffMode() and
   *         LPM_SetStopMode()
   *         This function shall be called in critical section
   * @param  None
   * @retval None
   */
  void LPM_EnterModeSelected(void);

  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before entering Sleep Mode
   * @param  None
   * @retval None
   */
  void LPM_EnterSleepMode(void);

  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before getting out from Sleep Mode
   * @param  None
   * @retval None
   */
  void LPM_ExitSleepMode(void);

  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before entering Stop Mode
   * @param  None
   * @retval None
   */
  void LPM_EnterStopMode(void);

  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before getting out from Stop Mode. This is where the application
   *         should reconfigure the clock tree when needed
   * @param  None
   * @retval None
   */
  void LPM_ExitStopMode(void);

  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before entering Off mode. This is where the application could save
   *         data in the retention memory as the RAM memory content will be lost
   * @param  None
   * @retval None
   */
  void LPM_EnterOffMode(void);


  /**
   * @brief  This API is called by the low power manager in a critical section (PRIMASK bit set) to allow the
   *         application to implement dedicated code before getting out from Off mode. This can only happen when the
   *         Off mode is finally not entered. In that case, the application may reverse some configurations done before
   *         entering Off mode. When Off mode is successful, the system is reset when getting out from this low-power mode
   * @param  None
   * @retval None
   */
  void LPM_ExitOffMode(void);

  /**
   * @brief  This API shall be called by the application.
   *         It sets the configuration mode requested to be applied in Stop Mode and Off Mode.
   * @param  p_conf: configuration
   * @retval None
   */
  void LPM_SetConf(LPM_Conf_t *p_conf);



#ifdef __cplusplus
}
#endif

#endif /*__LPM__H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
