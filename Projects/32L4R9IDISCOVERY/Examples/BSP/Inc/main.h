/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm32l4xx_hal.h"
#include "stm32l4r9i_discovery.h"
#include "stm32l4r9i_discovery_io.h"
#include "stm32l4r9i_discovery_audio.h"
#include "stm32l4r9i_discovery_lcd.h"
#include "stm32l4r9i_discovery_ts.h"
#include "stm32l4r9i_discovery_sd.h"
#include "stm32l4r9i_discovery_camera.h"
#include "stm32l4r9i_discovery_ospi_nor.h"
#include "stm32l4r9i_discovery_idd.h"
#include "stm32l4r9i_discovery_psram.h"

/* Macros --------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  void   (*DemoFunc)(void);
  uint8_t DemoName[50];
  uint32_t DemoIndex;
}BSP_DemoTypedef;

typedef enum
{
  IDD_RUN       = 0x00,
  IDD_SLEEP     = 0x01,
  IDD_LPR_2MHZ  = 0x02,
  IDD_LPR_SLEEP = 0x03,
  IDD_STOP2     = 0x04,
  IDD_STANDBY   = 0x05,
  IDD_SHUTDOWN  = 0x06,
  IDD_TEST_NB   = 0x07,
} Idd_StateTypeDef;

/* Exported variables --------------------------------------------------------*/
extern const unsigned char stlogo[];
extern __IO FlagStatus MfxItOccurred;

/* Exported constants --------------------------------------------------------*/

/* Defines for the Audio playing process */
#define PAUSE_STATUS     ((uint32_t)0x00) /* Audio Player in Pause Status */
#define RESUME_STATUS    ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS      ((uint32_t)0x02) /* Audio Player in Idle Status */

#define AUDIO_PLAY_SAMPLE        0
#define AUDIO_PLAY_RECORDED      1

#if defined(LCD_DIMMING)
#define DIMMING_COUNTDOWN       7U     /* Countdown timer until screen is dimmed (in seconds) */
#define BRIGHTNESS_MAX          0xFFU  /* LCD brightness maximum value                        */
#define BRIGHTNESS_MIN          0x44U  /* LCD brightness minimum value (screen dimmed)        */
#if defined(LCD_OFF_AFTER_DIMMING)
#define LCD_OFF_COUNTDOWN       2U     /* Number of RTC wake-up timer counter expirations while
                                          the screen is dimmed before turning off the LCD     */
#endif /* defined(LCD_OFF_AFTER_DIMMING) */
#endif /* defined(LCD_DIMMING) */

/* Exported macro ------------------------------------------------------------*/
#define COUNT_OF_EXAMPLE(x)    (sizeof(x)/sizeof(BSP_DemoTypedef))

/* Exported functions ------------------------------------------------------- */
void Led_demo(void);
void LCD_demo(void);
void Joystick_demo (void);
void AudioPlay_demo(void);
void AudioRecord_demo(void);
void Touchscreen_demo(void);
void SD_demo(void);
void Camera_demo(void);
void OSPI_NOR_demo(void);
void Idd_demo(void);
void PSRAM_demo (void);

void SystemClock_Config(void);
void SystemLowClock_Config(void);
void SystemClock_ConfigFromLowPower(void);

void SystemHardwareInit(void);
void SystemHardwareDeInit(void);
uint32_t SystemRtcBackupRead(void);
void SystemRtcBackupWrite(uint32_t SaveIndex);

void Convert_IntegerIntoChar(uint32_t number, uint16_t *p_tab);

void Mfx_Event(void);
void Toggle_Leds(void);
void Error_Handler(void);

#if defined(LCD_DIMMING)
void Dimming_Timer_Enable(RTC_HandleTypeDef * RTCHandle);
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
