/**
  ******************************************************************************
  * @file    audio_player_app.c
  * @author  MCD Application Team
  * @brief   Audio player application functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2017 STMicroelectronics International N.V. 
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
#include "stm32l496g_discovery_audio.h"
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

//#define DEBUG_AUDIO_APP

/* Private function prototypes -----------------------------------------------*/
static void Audio_Thread(void const * argument);

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
  
  /* Register audio BSP drivers callbacks */
  BSP_AUDIO_OUT_RegisterCallbacks(AUDIO_Error_CallBack, 
                                  AUDIO_HalfTransfer_CallBack, 
                                  AUDIO_TransferComplete_CallBack);
    
  /* Create Audio Queue */
  osMessageQDef(AUDIO_Queue, 1, uint16_t);
  AudioEvent = osMessageCreate (osMessageQ(AUDIO_Queue), NULL); 
  
  /* Create Audio task */
  osThreadDef(osAudio_Thread, Audio_Thread, osPriorityRealtime, 0, 512);
  AudioThreadId = osThreadCreate (osThread(osAudio_Thread), NULL);  

  portEXIT_CRITICAL();
 
  return AUDIOPLAYER_ERROR_NONE;
}

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
  * @param  frequency: Audio frequency and nb of channel used to play the audio stream.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Play(uint32_t frequency, uint32_t nbrChannels)
{
  uint32_t numOfReadBytes;
  uint32_t mode = BSP_AUDIO_OUT_STEREOMODE;
  haudio.out.state = AUDIOPLAYER_PLAY;
  
    /* Fill whole buffer @ first time */
    if(f_read(&wav_file, 
              &haudio.buff[0], 
              AUDIO_OUT_BUFFER_SIZE, 
              (void *)&numOfReadBytes) == FR_OK)
    { 
      if(numOfReadBytes != 0)
      {
        if (BSP_AUDIO_OUT_Pause())
        {
          Error_Handler();
        }        

        if (nbrChannels == 1)
        {
          mode = BSP_AUDIO_OUT_MONOMODE;
        }
        else if (nbrChannels == 2)
        {
          mode = BSP_AUDIO_OUT_STEREOMODE;
        }
        else
        {
          Error_Handler();
        }
        
        BSP_AUDIO_OUT_ChangeAudioConfig(mode | BSP_AUDIO_OUT_CIRCULARMODE);
        
        if (BSP_AUDIO_OUT_SetFrequency(frequency))
        {
          Error_Handler();
        }        
        
        osThreadResume(AudioThreadId);
        
        if (BSP_AUDIO_OUT_Play((uint16_t*)&haudio.buff[0], AUDIO_OUT_BUFFER_SIZE_HALF_WORD))   
        {
          Error_Handler();
        }        
        
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
  switch(haudio.out.state)
  {
  case AUDIOPLAYER_START:
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
  if(haudio.out.state != AUDIOPLAYER_STOP)
  {
    haudio.out.state = AUDIOPLAYER_STOP; 
    if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW))
    {
      Error_Handler();
    }
    f_close(&wav_file); 
  }
    
  if (BSP_AUDIO_OUT_DeInit())
  {
    Error_Handler();
  }        

  f_close(&wav_file); 
  
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
  
  return AUDIOPLAYER_ERROR_NONE;  
}

/**
  * @brief  Stop audio stream.
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Stop(void)
{

  if(haudio.out.state != AUDIOPLAYER_STOP)
  {
    haudio.out.state = AUDIOPLAYER_STOP; 
    if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW))
    {
      Error_Handler();
    }
  }  
  
  f_close(&wav_file);
  if(AudioThreadId != 0)
  {  
    osThreadSuspend(AudioThreadId); 
  }
  return AUDIOPLAYER_ERROR_NONE;
}


/**
  * @brief  Pause Audio stream
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Pause(void)
{
  if(AudioThreadId != 0)
  {
    osThreadSuspend(AudioThreadId); 
  }
  haudio.out.state = AUDIOPLAYER_PAUSE;
  if(BSP_AUDIO_OUT_Pause())
  {
    Error_Handler();
  }        
  return AUDIOPLAYER_ERROR_NONE;
}


/**
  * @brief  Resume Audio stream
  * @param  None.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Resume(void)
{
  if(AudioThreadId != 0)
  {  
    osThreadResume(AudioThreadId);  
  }
  haudio.out.state = AUDIOPLAYER_PLAY;
  if(BSP_AUDIO_OUT_Resume())
  {
    Error_Handler();
  }        
return AUDIOPLAYER_ERROR_NONE;
}
/**
  * @brief  Sets audio stream position
  * @param  position: stream position.
  * @retval Audio state.
  */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SetPosition(uint32_t position)
{
  long file_pos;
  
  file_pos = f_size(&wav_file) / AUDIO_OUT_BUFFER_SIZE / 100; 
  file_pos *= (position * AUDIO_OUT_BUFFER_SIZE);
  AUDIOPLAYER_Pause(); 
  f_lseek(&wav_file, file_pos);
  AUDIOPLAYER_Resume(); 
  
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
   if (BSP_AUDIO_OUT_SetMute(state))
   {
     Error_Handler();
   }        

   return AUDIOPLAYER_ERROR_NONE;
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
    if osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_FULL, 0) != osOK)
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
    if osMessagePut ( AudioEvent, PLAY_BUFFER_OFFSET_HALF, 0) != osOK)
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
    event = osMessageGet(AudioEvent, 100 );
    
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
              if (BSP_AUDIO_OUT_SetMute(MUTE_ON))
              {
                Error_Handler();
              }
            }
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
              if (BSP_AUDIO_OUT_SetMute(MUTE_ON))
              {
                Error_Handler();
              }
            }  
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
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
