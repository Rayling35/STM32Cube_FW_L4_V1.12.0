/**
 ******************************************************************************
 * @file    memory_manager.c
 * @author  MCD Application Team
 * @brief   Memory Manager
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
#include "memory_manager.h"
#include "list.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t QueueSize;
static tListNode BufferPool;
static MM_pCb_t BufferFreeCb;

/* Global variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
/**
 * @brief  Initialize the Pools
 * @param  p_pool: The pool of memory to manage
 * @param  pool_size: The size of the pool
 * @param  elt_size: The size of one element in the pool
 * @retval None
 */
void MM_Init(uint8_t *p_pool, uint32_t pool_size,  uint32_t elt_size)
{
  uint32_t elt_size_corrected;

  QueueSize = 0;
  elt_size_corrected = 4*DIVC( elt_size, 4 );

  /**
   *  Initialize list
   */
  LST_init_head (&BufferPool);

  /**
   *  Initialize the queue
   */
  while(pool_size >= elt_size_corrected)
  {
    LST_insert_tail(&BufferPool, (tListNode *)p_pool);
    p_pool += elt_size_corrected;
    QueueSize++;
    pool_size -= elt_size_corrected;
  }

  return;
}

/**
 * @brief  Provide a buffer
 * @note   The buffer allocated to the user shall be at least sizeof(tListNode) bytes
 *         to store the memory manager chaining information
 *
 * @param  size: The size of the buffer requested
 * @param  cb: The callback to be called when a buffer is made available later on
 *                   if there is no buffer currently available when this API is called
 * @retval The buffer address when available or NULL when there is no buffer
 */
MM_pBufAdd_t MM_GetBuffer( uint32_t size, MM_pCb_t cb )
{
  MM_pBufAdd_t buffer_address;
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/
  if ( QueueSize )
  {
    QueueSize--;
    BufferFreeCb = 0;
    LST_remove_head( &BufferPool, ( tListNode ** )&buffer_address );
  }
  else
  {
    BufferFreeCb = cb;
    buffer_address = 0;
  }
  __set_PRIMASK( primask_bit );     /**< Restore PRIMASK bit*/

  return buffer_address;
}

/**
 * @brief  Release a buffer
 * @param  p_buffer: The data buffer address
 * @retval None
 */
void MM_ReleaseBuffer( MM_pBufAdd_t p_buffer )
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/
  LST_insert_tail( &BufferPool, ( tListNode * )p_buffer );
  QueueSize++;
  __set_PRIMASK( primask_bit );     /**< Restore PRIMASK bit*/
  if( BufferFreeCb )
  {
    /**
     * The application is waiting for a free buffer
     */
    BufferFreeCb();
  }

  return;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
