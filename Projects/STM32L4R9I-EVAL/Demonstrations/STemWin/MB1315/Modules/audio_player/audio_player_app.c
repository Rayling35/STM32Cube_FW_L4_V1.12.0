/**
  ******************************************************************************
  * @file    audioplayer_app.c
  * @author  MCD Application Team  
  * @brief   Audio player application functions
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
#include "audio_player_app.h"

/** @addtogroup AUDIO_PLAYER_MODULE
  * @{
  */

/** @defgroup AUDIO_APPLICATION
  * @brief audio application routines
  * @{
  */


/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static FIL wav_file;


static osMessageQId   AudioEvent = 0;
static osThreadId     AudioThreadId = 0;
static uint8_t muteState = MUTE_OFF;
static uint32_t current_frequency = 0;

/* Private function prototypes -----------------------------------------------*/
static void Audio_Thread(void const * argument);

#if (!defined ( __GNUC__ ))  
__IO uint32_t  AUDIO_EqInstance[SPIRIT_EQ_PERSIST_SIZE_IN_BYTES/4]  ;
TSpiritEQ_Band AUDIO_EQ_Bands[SPIRIT_EQ_MAX_BANDS];
__IO int16_t AUDIO_loudness;

__IO uint32_t AUDIO_LdCtrlPersistance[SPIRIT_LDCTRL_PERSIST_SIZE_IN_BYTES/4];
__IO uint32_t AUDIO_LdCtrlScratch[SPIRIT_LDCTRL_SCRATCH_SIZE_IN_BYTES/4];
TSpiritLdCtrl_Prms AUDIO_LdCtrlInstanceParams;
TSpiritEQ_Band *tmpEqBand;
#endif

#ifndef DEFAULT_AUDIO_OUT_FREQ
#define DEFAULT_AUDIO_OUT_FREQ               BSP_AUDIO_FREQUENCY_48K
#endif
/* Private function prototypes -----------------------------------------------*/
static void Audio_Thread(void const * argument);
static void AUDIO_TransferComplete_CallBack(void);
static void AUDIO_HalfTransfer_CallBack(void);
static void AUDIO_Error_CallBack(void);



/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes audio
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Init(uint8_t volume)
{
#if (!defined ( __GNUC__ ))  
  uint32_t index = 0;
  __IO uint32_t ldness_value;
#endif

  portENTER_CRITICAL();

  /* Try to Init Audio interface in diffrent config in case of failure */
  if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, volume, DEFAULT_AUDIO_OUT_FREQ))
  {
    Error_Handler();
  }
  
  /* Initialize internal audio structure */
  haudio.out.state  = AUDIOPLAYER_STOP;
  haudio.out.mute   = MUTE_OFF;
  haudio.out.volume = volume;  
  current_frequency = 0;
  
  
#if (!defined ( __GNUC__ ))  
  /* Enable the Eq */
  SpiritEQ_Init((TSpiritEq *)AUDIO_EqInstance, BSP_AUDIO_FREQUENCY_48K);
  
  
  /* Retreive stored settings and set band params */
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[0], 0 );
  AUDIO_EQ_Bands[0].gainDb = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_EQU1_BKP);
  SET_BAND_PRMS(&AUDIO_EQ_Bands[0], SPIRIT_EQ_FLT_TYPE_SHELVING_LOWPASS , 0, 1000, AUDIO_EQ_Bands[0].gainDb);
  
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[1], 1 );
  AUDIO_EQ_Bands[1].gainDb = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_EQU2_BKP);    
  SET_BAND_PRMS(&AUDIO_EQ_Bands[1], SPIRIT_EQ_FLT_TYPE_PEAKING , 2000, 1000, AUDIO_EQ_Bands[1].gainDb);
  
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[2], 2 );
  AUDIO_EQ_Bands[2].gainDb = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_EQU3_BKP);   
  SET_BAND_PRMS(&AUDIO_EQ_Bands[2], SPIRIT_EQ_FLT_TYPE_PEAKING , 5000, 3000, AUDIO_EQ_Bands[2].gainDb);
  
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[3], 3 );
  AUDIO_EQ_Bands[3].gainDb = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_EQU4_BKP);;  
  SET_BAND_PRMS(&AUDIO_EQ_Bands[3], SPIRIT_EQ_FLT_TYPE_PEAKING , 10000, 6000, AUDIO_EQ_Bands[3].gainDb);
  
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[4], 4 );
  AUDIO_EQ_Bands[4].gainDb = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_EQU5_BKP);  
  SET_BAND_PRMS(&AUDIO_EQ_Bands[4], SPIRIT_EQ_FLT_TYPE_SHELVING_HIPASS , 15000, 2000, AUDIO_EQ_Bands[4].gainDb);
  AUDIO_loudness = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_LOUD_BKP);

  for (index = 0; index < SPIRIT_EQ_MAX_BANDS ; index++)
  {
    tmpEqBand = &AUDIO_EQ_Bands[index];
    SpiritEQ_FltSet((TSpiritEq *)AUDIO_EqInstance, tmpEqBand, index);
  }
  
  /* Enable Loundness Control */
  SpiritLdCtrl_Init((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance, BSP_AUDIO_FREQUENCY_48K);
  SpiritLdCtrl_GetPrms((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance, &AUDIO_LdCtrlInstanceParams);
  ldness_value = k_BkupRestoreParameter(CALIBRATION_AUDIOPLAYER_LOUD_BKP);
  AUDIO_LdCtrlInstanceParams.gainQ8 = PERC_TO_LDNS_DB(ldness_value);
  SpiritLdCtrl_SetPrms((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance, &AUDIO_LdCtrlInstanceParams);
#endif  
  
  /* Register audio BSP drivers callbacks */
  BSP_AUDIO_OUT_RegisterCallbacks(AUDIO_Error_CallBack, 
                                  AUDIO_HalfTransfer_CallBack, 
                                  AUDIO_TransferComplete_CallBack);

  /* Create Audio Queue */
  osMessageQDef(AUDIO_Queue, 1, uint16_t);
  AudioEvent = osMessageCreate (osMessageQ(AUDIO_Queue), NULL); 
  
  /* Create Audio task */
  osThreadDef(osAudio_Thread, Audio_Thread, osPriorityHigh, 0, 512);
  AudioThreadId = osThreadCreate (osThread(osAudio_Thread), NULL);  

  portEXIT_CRITICAL();
  return AUDIOPLAYER_ERROR_NONE;
}

#if (!defined ( __GNUC__ ))  
/**
  * @brief  This function Set the new gain of the equilizer
  * @param  BandNum : equilizer band index
  * @param  NewGainValue : the new band gain.
  * @retval None.
*/
void AUDIO_SetEq(uint8_t BandNum, int16_t NewGainValue)
{
  /* GetBand */
  SpiritEQ_FltGet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[BandNum], BandNum );
  
  /* SetNewValue */
  AUDIO_EQ_Bands[BandNum].gainDb = PERC_TO_EQUI_DB(NewGainValue);
  
  SpiritEQ_FltSet((TSpiritEq *)AUDIO_EqInstance, &AUDIO_EQ_Bands[BandNum], BandNum);
}


/**
  * @brief  This function Set Loudness Control Gain Value.
  * @param  NewGainValue in %.
  * @retval None.
  */
void AUDIO_SetLoudnessGain(int16_t NewGainValue)
{
  /* Get old Gain */
  SpiritLdCtrl_GetPrms((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance, &AUDIO_LdCtrlInstanceParams);
  AUDIO_LdCtrlInstanceParams.gainQ8 = PERC_TO_LDNS_DB (NewGainValue);
  AUDIO_loudness = NewGainValue;
  SpiritLdCtrl_Reset  ((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance);
  SpiritLdCtrl_SetPrms((TSpiritLdCtrl*)AUDIO_LdCtrlPersistance, &AUDIO_LdCtrlInstanceParams);
}

/**
  * @brief  This function Set the new gain of the equilizer
  * @param  BandNum : equilizer band index
  * @param  NewGainValue : the new band gain.
  * @retval None.
*/
void AUDIO_SetEqParams(uint32_t loudness_perc)
{
  
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_EQU1_BKP, AUDIO_EQ_Bands[0].gainDb);
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_EQU2_BKP, AUDIO_EQ_Bands[1].gainDb);
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_EQU3_BKP, AUDIO_EQ_Bands[2].gainDb);
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_EQU4_BKP, AUDIO_EQ_Bands[3].gainDb);
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_EQU5_BKP, AUDIO_EQ_Bands[4].gainDb);
  
  k_BkupSaveParameter(CALIBRATION_AUDIOPLAYER_LOUD_BKP, loudness_perc);
}

/**
  * @brief  This function Set Loudness Control Gain Value.
  * @param  NewGainValue -12 dB to 12 dB.
  * @retval None.
  */
int16_t AUDIOPLAYER_GetLoudnessGain(void)
{
  return (AUDIO_loudness);
}
#endif

/**
  * @brief  Get audio state
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_StateTypdef  AUDIOPLAYER_GetState(void)
{
  return haudio.out.state;
}

/**
  * @brief  Get audio volume
  * @param  None.
  * @retval Audio volume.
  */
uint32_t  AUDIOPLAYER_GetVolume(void)
{
  return haudio.out.volume;
}

/**
  * @brief  Set audio volume
  * @param  Volume: Volume level to be set in percentage from 0% to 100% (0 for 
  *         Mute and 100 for Max volume level).
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SetVolume(uint32_t volume)
{
  if(BSP_AUDIO_OUT_SetVolume(volume) == AUDIO_OK)
  {
    haudio.out.volume = volume;
    return AUDIOPLAYER_ERROR_NONE;    
  }
  else
  {
    return AUDIOPLAYER_ERROR_HW;
  }
}

/**
  * @brief  Play audio stream
  * @param  frequency: Audio frequency used to play the audio stream.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Play(uint32_t frequency)
{
  uint32_t numOfReadBytes;
  haudio.out.state = AUDIOPLAYER_PLAY;
  
    /* Fill whole buffer @ first time */
    if(f_read(&wav_file, 
              &haudio.buff[0], 
              AUDIO_OUT_BUFFER_SIZE, 
              (void *)&numOfReadBytes) == FR_OK)
    { 
      if(numOfReadBytes != 0)
      {
        // BSP_AUDIO_OUT_Pause();
      if(current_frequency != frequency)
      {
        current_frequency = frequency;
        if (BSP_AUDIO_OUT_SetFrequency(frequency))
        {
          Error_Handler();
        }
      }

        osThreadResume(AudioThreadId);

        if (BSP_AUDIO_OUT_Play((uint16_t*)&haudio.buff[0], AUDIO_OUT_BUFFER_SIZE/2))
        {
          Error_Handler();
        }        
        
        AUDIOPLAYER_Mute(MUTE_OFF);
        
        return AUDIOPLAYER_ERROR_NONE;
      }
    }
  return AUDIOPLAYER_ERROR_IO;

}

/**
  * @brief  Audio player process
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Process(void)
{
  if((AudioEvent == 0) || (AudioThreadId == 0))
  {
    /* Not yet initialized or already stopped */
    return AUDIOPLAYER_ERROR_NONE;
  }

  switch(haudio.out.state)
  {
  case AUDIOPLAYER_START:
    AUDIOPLAYER_Mute(MUTE_OFF);
    haudio.out.state = AUDIOPLAYER_PLAY;
    break;    

  case AUDIOPLAYER_EOF:
     AUDIOPLAYER_NotifyEndOfFile();
    break;    
    
  case AUDIOPLAYER_ERROR:
     AUDIOPLAYER_Stop();
    break;
    
  case AUDIOPLAYER_STOP:
  case AUDIOPLAYER_PLAY:    
  default:
    break;
  }
  
  return AUDIOPLAYER_ERROR_NONE;
}

/**
  * @brief  Audio player DeInit
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_DeInit(void)
{
  if((AudioEvent == 0) || (AudioThreadId == 0))
  {
    /* Not yet initialized or already stopped */
    return AUDIOPLAYER_ERROR_NONE;
  }

  portENTER_CRITICAL();

  if(haudio.out.state != AUDIOPLAYER_STOP)
  {    
    haudio.out.state = AUDIOPLAYER_STOP; 
    if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW))
    {
      Error_Handler();
    }
    f_close(&wav_file);
    f_size(&wav_file) = 0;
  }
  
  if (BSP_AUDIO_OUT_DeInit())
  {
    Error_Handler();
  }
  
  if(AudioEvent != 0)
  {
    vQueueDelete(AudioEvent); 
    AudioEvent = 0;
  }
  if(AudioThreadId != 0)
  {
    osThreadTerminate(AudioThreadId);
    AudioThreadId = 0;
  }

#if (!defined ( __GNUC__ ))
  AUDIO_SetEqParams(AUDIO_loudness);
#endif

  portEXIT_CRITICAL();
  return AUDIOPLAYER_ERROR_NONE;
}

/**
  * @brief  Stop audio stream.
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Stop(void)
{
  AUDIOPLAYER_ErrorTypdef  ErrorCode = AUDIOPLAYER_ERROR_NONE;
  
  if(AudioThreadId != 0)
  {  
    osThreadSuspend(AudioThreadId); 
  }

  if(haudio.out.state != AUDIOPLAYER_STOP)
  {
    AUDIOPLAYER_Mute(MUTE_ON);

    haudio.out.state = AUDIOPLAYER_STOP;

    if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW))
    {
      ErrorCode = AUDIOPLAYER_ERROR_HW;
    }

    f_close(&wav_file);
    f_size(&wav_file) = 0;
  }

  return ErrorCode;
}


/**
  * @brief  Pause Audio stream
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Pause(void)
{
  AUDIOPLAYER_ErrorTypdef  ErrorCode = AUDIOPLAYER_ERROR_NONE;

  if(AudioThreadId != 0)
  {
    osThreadSuspend(AudioThreadId); 
  }

  if(haudio.out.state == AUDIOPLAYER_PLAY)
  {
    if (BSP_AUDIO_OUT_Pause())
    {
      ErrorCode = AUDIOPLAYER_ERROR_HW;
    }
    else
    {
      haudio.out.state = AUDIOPLAYER_PAUSE;
    }
  }

  return ErrorCode;
}


/**
  * @brief  Resume Audio stream
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Resume(void)
{
  AUDIOPLAYER_ErrorTypdef  ErrorCode = AUDIOPLAYER_ERROR_NONE;

  if(AudioThreadId != 0)
  {  
    osThreadResume(AudioThreadId);  
  }

  if(haudio.out.state == AUDIOPLAYER_PAUSE)
  {
    if (BSP_AUDIO_OUT_Resume())
    {
      ErrorCode = AUDIOPLAYER_ERROR_HW;
    }
    else
    {
      haudio.out.state = AUDIOPLAYER_PLAY;
      if(muteState)
      {
        if (BSP_AUDIO_OUT_SetMute(muteState))
        {
          ErrorCode = AUDIOPLAYER_ERROR_HW;
        }
      }
    }
  }

  return ErrorCode;
}
/**
  * @brief  Sets audio stream position
  * @param  position: stream position.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SetPosition(uint32_t position)
{
  uint8_t resume = 0;
  long file_pos;
  
  file_pos = f_size(&wav_file) / AUDIO_OUT_BUFFER_SIZE / 100;
  file_pos *= (position * AUDIO_OUT_BUFFER_SIZE);
  if(haudio.out.state == AUDIOPLAYER_PLAY)
  {
    resume = 1;
    AUDIOPLAYER_Pause(); 
  }
  f_lseek(&wav_file, file_pos);
  if(resume)
  {
    AUDIOPLAYER_Resume();
  }
  
  return AUDIOPLAYER_ERROR_NONE;
}

/**
  * @brief  Sets the volume at mute
  * @param  state: could be MUTE_ON to mute sound or MUTE_OFF to unmute 
  *                the codec and restore previous volume level.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Mute(uint8_t state)
{
  AUDIOPLAYER_ErrorTypdef  ErrorCode = AUDIOPLAYER_ERROR_NONE;

  if((AudioEvent == 0) || (AudioThreadId == 0))
  {
    /* Not yet initialized or already stopped */
    return AUDIOPLAYER_ERROR_NONE;
  }

  if(muteState != state)
  {
    if (BSP_AUDIO_OUT_SetMute(state))
    {
      ErrorCode = AUDIOPLAYER_ERROR_HW;
    }
    else
    {
      muteState = state;
    }
  }

   return ErrorCode;
}

/**
  * @brief  Get the wav file information.
  * @param  file: wav file.
  * @param  info: pointer to wav file structure
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_GetFileInfo(char* file, WAV_InfoTypedef* info)
{
  uint32_t numOfReadBytes;
  AUDIOPLAYER_ErrorTypdef ret = AUDIOPLAYER_ERROR_IO;
  FIL fsfile;
  
  if( f_open(&fsfile, file, FA_OPEN_EXISTING | FA_READ) == FR_OK) 
  {
    /* Fill the buffer to Send */
    if(f_read(&fsfile, info, sizeof(WAV_InfoTypedef), (void *)&numOfReadBytes) == FR_OK)
    {
      if((info->ChunkID == 0x46464952) && (info->AudioFormat == 1))
      {
        ret = AUDIOPLAYER_ERROR_NONE;
      }
    }
    f_close(&fsfile);
  }
  return ret;
}

/**
  * @brief  Select wav file.
  * @param  file: wav file.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SelectFile(char* file)
{
  AUDIOPLAYER_ErrorTypdef ret = AUDIOPLAYER_ERROR_IO;
  if( f_open(&wav_file, file, FA_OPEN_EXISTING | FA_READ) == FR_OK) 
  {
    f_lseek(&wav_file, sizeof(WAV_InfoTypedef));
    ret = AUDIOPLAYER_ERROR_NONE;
  }
  return ret;  
}

/**
  * @brief  Get wav file progress.
  * @param  None
  * @retval file progress.
  */
uint32_t AUDIOPLAYER_GetProgress(void)
{
  return (wav_file.fptr);
}

/**
  * @brief  Manages the DMA Transfer complete interrupt.
  * @param  None
  * @retval None
  */

static void AUDIO_TransferComplete_CallBack(void)
{
  if(haudio.out.state == AUDIOPLAYER_PLAY)
  {
#ifdef DEBUG_AUDIO_APP
    if (osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_FULL, 0) != osOK)
    {
      /* Fifo underflow !!! */
      Error_Handler();
    }
#else
    osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_FULL, 0);    
#endif
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
static void AUDIO_HalfTransfer_CallBack(void)
{ 
  if(haudio.out.state == AUDIOPLAYER_PLAY)
  {
#ifdef DEBUG_AUDIO_APP
    if (osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_HALF, 0) != osOK)
    {
      /* Fifo underflow !!! */
      Error_Handler();
    }
#else
    osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_HALF, 0);    
#endif
  }
}

/**
  * @brief  Manages the DMA FIFO error interrupt.
  * @param  None
  * @retval None
  */
static void AUDIO_Error_CallBack(void)
{
    haudio.out.state = AUDIOPLAYER_ERROR;
  AUDIOPLAYER_Mute(MUTE_ON);
}

/**
  * @brief  Audio task
  * @param  argument: pointer that is passed to the thread function as start argument.
  * @retval None
  */
static void Audio_Thread(void const * argument)
{
  uint32_t numOfReadBytes;    
  osEvent event;  
  for(;;)
  {
    event = osMessageGet(AudioEvent, osWaitForever );
    
    if( event.status == osEventMessage )
    {
      if(haudio.out.state == AUDIOPLAYER_PLAY)
      {
        switch(event.value.v)
        {
        case PLAY_BUFFER_OFFSET_HALF:
          if(f_read(&wav_file, 
                    &haudio.buff[0], 
                    AUDIO_OUT_BUFFER_SIZE/2, 
                    (void *)&numOfReadBytes) == FR_OK)
          { 
            if(numOfReadBytes == 0)
            {  
              haudio.out.state = AUDIOPLAYER_EOF;
              AUDIOPLAYER_Mute(MUTE_ON);
            } 
            
#if (!defined ( __GNUC__ )) 
            SpiritEQ_Apply((void *)AUDIO_EqInstance,
                           /* NB_Channel */2, 
                           (int16_t *)&haudio.buff[0], 
                           numOfReadBytes  / 4);
            
            /* Apply Loudness settings */
            SpiritLdCtrl_Apply((TSpiritLdCtrl *)AUDIO_LdCtrlPersistance,
                               /* NB_Channel */ 2, 
                               (int16_t *)&haudio.buff[0], 
                               numOfReadBytes / 4, 
                               (void *)AUDIO_LdCtrlScratch);            
            
#endif
          }
          else
          {
              haudio.out.state = AUDIOPLAYER_ERROR;    
          }
          break;  
          
        case PLAY_BUFFER_OFFSET_FULL:
          if(f_read(&wav_file, 
                    &haudio.buff[AUDIO_OUT_BUFFER_SIZE/2], 
                    AUDIO_OUT_BUFFER_SIZE/2, 
                    (void *)&numOfReadBytes) == FR_OK)
          { 
            if(numOfReadBytes == 0)
            { 
              haudio.out.state = AUDIOPLAYER_EOF;                     
              AUDIOPLAYER_Mute(MUTE_ON);
            } 
#if (!defined ( __GNUC__ ))            
            SpiritEQ_Apply((void *)AUDIO_EqInstance,
                           /* NB_Channel */2, 
                           (int16_t *)&haudio.buff[AUDIO_OUT_BUFFER_SIZE /2], 
                           numOfReadBytes  / 4);
            
            
            /* Apply Loudness settings */
            SpiritLdCtrl_Apply((TSpiritLdCtrl *)AUDIO_LdCtrlPersistance,
                               /* NB_Channel */ 2, 
                               (int16_t *)&haudio.buff[AUDIO_OUT_BUFFER_SIZE /2], 
                               numOfReadBytes / 4, 
                               (void *)AUDIO_LdCtrlScratch);                
#endif   
          }
          else
          {
              haudio.out.state = AUDIOPLAYER_ERROR;   
          }
          break;   
          
        default:
          break;
        }
      }
      
    }
  }
}

/**
  * @brief  Notify end of playing.
  * @param  None
  * @retval None
  */
__weak AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_NotifyEndOfFile(void)
{
  return AUDIOPLAYER_ERROR_NONE;
}

/**
  * @brief  Notify audio error.
  * @param  None
  * @retval None
  */
__weak AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_NotifyError(void)
{
  return AUDIOPLAYER_ERROR_NONE;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
