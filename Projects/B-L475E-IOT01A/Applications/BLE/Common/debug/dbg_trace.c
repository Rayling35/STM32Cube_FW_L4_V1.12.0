/**
 ******************************************************************************
 * @file    dbg_trace.c
 * @author  MCD Application Team
 * @brief   This file contains the Interface with BLNRG Drivers functions.
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

#include "queue.h"
#include "dbg_trace.h"

#if (CFG_DEBUG_TRACE == 1)

/** @addtogroup TRACE
 * @{
 */


/** @defgroup TRACE_LOG
 * @brief TRACE Logging functions
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup TRACE Log private typedef 
 * @{
 */

/**
 * @}
 */

/* Private defines -----------------------------------------------------------*/
/** @defgroup TRACE Log private defines 
 * @{
 */


#if 0
/* Definition for USARTx clock resources */
#define DBG_TRACE_UART_BR                       2000000
#define DBG_TRACE_UART_STOPBITS                 UART_STOPBITS_1
#define DBG_TRACE_UART_PARITY                   UART_PARITY_NONE
#define DBG_TRACE_UART_WORDLENGTH               USART_WORDLENGTH_8B
#define DBG_TRACE_UART_HWCONTROL                UART_HWCONTROL_CTS
#define DBG_TRACE_UART_MODE                     UART_MODE_TX
#define DBG_TRACE_UART_OVERSAMPLING             UART_OVERSAMPLING_8

#define DBG_TRACE_UART_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define DBG_TRACE_UART_DMA_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()
#define DBG_TRACE_UART_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 
#define DBG_TRACE_UART_CTS_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()

/* Definition for USARTx Pins */
#define DBG_TRACE_UART_TX_PIN                    GPIO_PIN_9
#define DBG_TRACE_UART_TX_GPIO_PORT              GPIOA
#define DBG_TRACE_UART_TX_AF                     GPIO_AF7_USART1

#define DBG_TRACE_UART_CTS_PIN                   GPIO_PIN_11
#define DBG_TRACE_UART_CTS_GPIO_PORT             GPIOA
#define DBG_TRACE_UART_CTS_AF                    GPIO_AF7_USART1

/* Definition for USARTx's DMA */
#define DBG_TRACE_UART_TX_DMA_CHANNEL            DMA_REQUEST_2
#define DBG_TRACE_UART_TX_DMA_STREAM             DMA1_Channel4

/* Definition for USARTx's NVIC */
#define DBG_TRACE_UART_DMA_TX_IRQn               DMA1_Channel4_IRQn
#define DBG_TRACE_UART_DMA_TX_IRQHandler         DMA1_Channel4_IRQHandler

#define DBG_TRACE_UART_IRQn                      USART1_IRQn
#define DBG_TRACE_UART_IRQHandler                USART1_IRQHandler
#endif

#define DBG_TRACE_MSG_QUEUE_SIZE 4092
#define MAX_DBG_TRACE_MSG_SIZE 1024
/**
 * @}
 */

/* Private macros ------------------------------------------------------------*/
/** @defgroup TRACE Log private macros 
 * @{
 */
/**
 * @}
 */

/* Private variables ---------------------------------------------------------*/
/** @defgroup TRACE Log private variables 
 * @{
 */

#if (DBG_TRACE_OUTPUT == DBG_TRACE_OUTPUT_UART)
#ifdef DBG_TRACE_UART_USE_CIRCULAR_QUEUE
static queue_t MsgDbgTraceQueue;
static uint8_t MsgDbgTraceQueueBuff[DBG_TRACE_MSG_QUEUE_SIZE];
#endif
static UART_HandleTypeDef DbgTraceUartHandle;
__IO ITStatus DbgTraceUartReady = RESET;
#endif
/**
 * @}
 */

/* Global variables ----------------------------------------------------------*/
/** @defgroup TRACE Log Global variable
 * @{
 */
/**
 * @}
 */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup TRACE Log private function prototypes 
 * @{
 */
void DbgTrace_UART_TxCpltCallback(void);


/**
 * @}
 */


/* Private Functions Definition ------------------------------------------------------*/
/** @defgroup TRACE Log Private function 
 * @{
 */


/* Functions Definition ------------------------------------------------------*/
/** @defgroup TRACE Log APIs 
 * @{
 */

/**
 * @brief  DbgTraceGetFileName: Return filename string extracted from full path information
 * @param  *fullPath Fullpath string (path + filename)
 * @retval char* Pointer on filename string
 */

const char *DbgTraceGetFileName(const char *fullpath)
{
  const char *ret = fullpath;

  if (strrchr(fullpath, '\\') != NULL)
  {
    ret = strrchr(fullpath, '\\') + 1;
  }
  else if (strrchr(fullpath, '/') != NULL)
  {
    ret = strrchr(fullpath, '/') + 1;
  }

  return ret;
}


/**
 * @brief  DbgTrace: Output Trace information to output Stream
 * @param  strFormat  Format string as expected by "printf" function
 * @param  ...        Paremeters to be "formatted" in strFormat string (if any)
 * @retval None
 */

void DbgTrace(const char *strFormat, ...)
{
  va_list arglist;
  va_start(arglist, strFormat);
  vprintf(strFormat, arglist);
  va_end(arglist);
}

/**
 * @brief  DbgTraceBuffer: Output buffer content information to output Stream
 * @param  *pBuffer  Pointer on buffer to be output
 * @param  u32Length buffer Size
 * @paramt strFormat string as expected by "printf" function. Used to desrcibe buffer content information.
 * @param  ...       Paremeters to be "formatted" in strFormat string (if any)
 * @retval None
 */

void DbgTraceBuffer(const void *pBuffer, uint32_t u32Length, const char *strFormat, ...)
{
  va_list vaArgs;
  uint32_t u32Index;
  va_start(vaArgs, strFormat);
  vprintf(strFormat, vaArgs);
  va_end(vaArgs);
  for (u32Index = 0; u32Index < u32Length; u32Index ++)
  {
    printf(" %02X", ((const uint8_t *) pBuffer)[u32Index]);
  }
}


/**
 * @brief  DbgTraceAssert: Output fatal error message to output stream. enter in infinite while loop.
 * @param  file souce code filename
 * @param  file function name where error ocuured
 * @param  line line number in "filenenme" where error occurred.
 * @retval none
 */
void DbgTraceAssert(const char *file, const char *function, uint32_t line, const char *condition)
{
  DbgTrace("** FATAL ** [%s][%s][%d] %s\r\n", file, function, line, condition);
  while (1);
}

#if (DBG_TRACE_OUTPUT == DBG_TRACE_OUTPUT_UART)
#if 0
/**
 * @brief  USART MSP Init.
 * @param  husart: pointer to a USART_HandleTypeDef structure that contains
 *                the configuration information for the specified USART module.
 * @retval None
 */
void DbgTrace_UART_MspInit(UART_HandleTypeDef *huart)
{
  static DMA_HandleTypeDef hdma_tx;

  GPIO_InitTypeDef  GPIO_InitStruct;

  if (huart->Instance == DBG_TRACE_UART)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO clock */
    DBG_TRACE_UART_TX_GPIO_CLK_ENABLE();
    DBG_TRACE_UART_CTS_GPIO_CLK_ENABLE();
    /* Enable USART clock */
    DBG_TRACE_UART_CLK_ENABLE();
    /* Enable DMA clock */
    DBG_TRACE_UART_DMA_CLK_ENABLE();  

    /*##-2- Configure peripheral GPIO ##########################################*/ 
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin = DBG_TRACE_UART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = DBG_TRACE_UART_TX_AF;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DBG_TRACE_UART_CTS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = DBG_TRACE_UART_CTS_AF;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*##-3- Configure the DMA streams ##########################################*/
    /* Configure the DMA handler for Transmission process */
    hdma_tx.Instance                 = DBG_TRACE_UART_TX_DMA_STREAM;

    hdma_tx.Init.Request             = DBG_TRACE_UART_TX_DMA_CHANNEL;
    hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_tx.Init.Mode                = DMA_NORMAL;
    hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

    HAL_DMA_Init(&hdma_tx);  

    /* Associate the initialized DMA handle to the UART handle */
    __HAL_LINKDMA(huart, hdmatx, hdma_tx);


    /*##-4- Configure the NVIC for DMA & UART #########################################*/
    /* NVIC configuration for DMA transfer complete interrupt  */
    HAL_NVIC_SetPriority(DBG_TRACE_UART_DMA_TX_IRQn, 0, 0/*1*/ );
    HAL_NVIC_EnableIRQ(DBG_TRACE_UART_DMA_TX_IRQn);

    /* NVIC configuration for EOT USART Irq */
    HAL_NVIC_SetPriority(DBG_TRACE_UART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DBG_TRACE_UART_IRQn);

    DbgTraceUartReady = SET;
  }
}
#endif


/**
 * @brief  DBG_TRACE USART Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   Indicate the end of the transmission of a DBG_TRACE trace buffer to DBG_TRACE USART. If queue
 *         contains new trace data to transmit, start a new transmission.
 * @retval None
 */
void DbgTrace_UART_TxCpltCallback(void)
{
#ifdef DBG_TRACE_UART_USE_CIRCULAR_QUEUE    
  uint8_t* buf;
  uint16_t bufSize;
  uint32_t uwPRIMASK_Bit;  


  uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */
  __disable_irq();			/**< Disable all interrupts by setting PRIMASK bit on Cortex*/        
  /* Remove element just sent to UART */
  CircularQueue_Remove(&MsgDbgTraceQueue,&bufSize);

  /* Sense if new data to be sent */
  buf=CircularQueue_Sense(&MsgDbgTraceQueue,&bufSize);


  if ( buf != NULL) 
  {
    HW_UART_Transmit_DMA(CFG_CONSOLE_TRACE, (uint8_t*)buf, bufSize, DbgTrace_UART_TxCpltCallback);
    
    __set_PRIMASK(uwPRIMASK_Bit);
  } 
  else
  {
    DbgTraceUartReady = SET;
    __set_PRIMASK(uwPRIMASK_Bit);
  }

#else
  uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */
  __disable_irq();			/**< Disable all interrupts by setting PRIMASK bit on Cortex*/        
  DbgTraceUartReady = SET;
  __set_PRIMASK(uwPRIMASK_Bit);  
#endif
}
#endif

/**
 * @brief	DbgTraceInit Initialie Logging feature.
 * @retval uint8_t error status
 */

uint8_t DbgTraceInit()
{
  uint8_t ret = DBG_TRACE_NO_ERR;
#if (DBG_TRACE_OUTPUT == DBG_TRACE_OUTPUT_UART)
  HW_UART_Init(CFG_CONSOLE_TRACE);
#ifdef DBG_TRACE_UART_USE_CIRCULAR_QUEUE
  CircularQueue_Init(&MsgDbgTraceQueue, MsgDbgTraceQueueBuff, DBG_TRACE_MSG_QUEUE_SIZE, 0);	
#endif 
  HW_UART_Transmit_DMA(CFG_CONSOLE_TRACE, (uint8_t*)&MsgDbgTraceQueueBuff, 1, DbgTrace_UART_TxCpltCallback);
#endif
  return ret;
}


#if (DBG_TRACE_OUTPUT == DBG_TRACE_OUTPUT_UART)
#if defined(DBG_TRACE_USE_MY_PRINTF)

/**
 * @brief	MyPrintf Alternative function for printf style logging ouput.
 * @param	fmt: format string
 * @param	...: arguments to be formatted in format string
 * @retval none
 */

void MyPrintf(char *fmt, ...)
{
  uint16_t buf_size;
  va_list arg_ptr;
  static uint8_t TempMsgBuf[MAX_DBG_TRACE_MSG_SIZE];
  uint32_t uwPRIMASK_Bit;
  uint8_t* buffer;


  va_start(arg_ptr, fmt); 
  buf_size=vsnprintf((char *) TempMsgBuf, MAX_DBG_TRACE_MSG_SIZE, fmt, arg_ptr);

  uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */
  __disable_irq();		        	/**< Disable all interrupts by setting PRIMASK bit on Cortex*/       
  buffer=CircularQueue_Add(&MsgDbgTraceQueue,(uint8_t*)TempMsgBuf, buf_size,1);		
  if (buffer && DbgTraceUartReady)
  {  
    DbgTraceUartReady = RESET;
    if (HW_UART_Transmit_DMA(CFG_CONSOLE_TRACE, (uint8_t*)buffer, buf_size)!= HAL_OK)
    {
      /* Manage error ? */
    }
  }  
  __set_PRIMASK(uwPRIMASK_Bit);      
  va_end(arg_ptr);
}
#endif


/**
 * @brief	__write: override the __write standard lib function to redirect printf to USART.
 * @param	handle output handle (STDIO, STDERR...)
 * @param	buf buffer to write
 * @param	bufsize buffer size
 * @param	...: arguments to be formatted in format string
 * @retval none
 */

size_t __write(int handle, const unsigned char * buf,size_t bufSize) 
{
  size_t chars_written = 0;
  uint32_t uwPRIMASK_Bit;
  uint8_t* buffer;

  /* Ignore flushes */
  if ( handle == -1 )
  {
    chars_written = ( size_t ) 0;
  }
  /* Only allow stdout/stderr output */
  else if ( ( handle != 1 ) && ( handle != 2 ) )
  {
    chars_written = ( size_t ) - 1;
  }
  /* Parameters OK, call the low-level character output routine */
  else if (bufSize != 0)
  {
    chars_written = bufSize;
    /* If queue emepty and TX free, send directly */
    /* CS Start */  	

#ifdef DBG_TRACE_UART_USE_CIRCULAR_QUEUE
    uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */
    __disable_irq();			/**< Disable all interrupts by setting PRIMASK bit on Cortex*/    
    buffer=CircularQueue_Add(&MsgDbgTraceQueue,(uint8_t*)buf, bufSize,1);		
    if (buffer && DbgTraceUartReady)
    {  
      DbgTraceUartReady = RESET;
      if (HW_UART_Transmit_DMA(CFG_CONSOLE_TRACE, (uint8_t*)buffer, bufSize, DbgTrace_UART_TxCpltCallback) != hw_uart_ok)
      {
        /* Manage error ? */
      }
    }  
    __set_PRIMASK(uwPRIMASK_Bit);                
#else
    DbgTraceUartReady = RESET;
    CFG_CONSOLE_TRACE(CFG_CONSOLE_TRACE, (uint8_t*)buf, bufSize);
    while (!DbgTraceUartReady);
#endif
    /* CS END */
  }
  return ( chars_written );

}

#endif /* DBG_TRACE_OUTPUT_UART */

#endif


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
