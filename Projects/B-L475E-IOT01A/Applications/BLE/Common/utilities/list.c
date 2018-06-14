/**
 ******************************************************************************
 * @file    list.c
 * @author  MCD Application Team
 * @brief   TCircular Linked List Implementation.
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

/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "common.h"
#include "list.h"

/******************************************************************************
 * Function Definitions 
 ******************************************************************************/
void LST_init_head (tListNode * listHead)
{
  listHead->next = listHead;
  listHead->prev = listHead;
}

uint8_t LST_is_empty (tListNode * listHead)
{
  uint32_t primask_bit;
  uint8_t return_value;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/
  if(listHead->next == listHead)
  {
    return_value = TRUE;
  }
  else
  {
    return_value = FALSE;
  }
  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/

  return return_value;
}

void LST_insert_head (tListNode * listHead, tListNode * node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  node->next = listHead->next;
  node->prev = listHead;
  listHead->next = node;
  (node->next)->prev = node;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_insert_tail (tListNode * listHead, tListNode * node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  node->next = listHead;
  node->prev = listHead->prev;
  listHead->prev = node;
  (node->prev)->next = node;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_remove_node (tListNode * node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  (node->prev)->next = node->next;
  (node->next)->prev = node->prev;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_remove_head (tListNode * listHead, tListNode ** node )
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  *node = listHead->next;
  LST_remove_node (listHead->next);

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_remove_tail (tListNode * listHead, tListNode ** node )
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  *node = listHead->prev;
  LST_remove_node (listHead->prev);

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_insert_node_after (tListNode * node, tListNode * ref_node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  node->next = ref_node->next;
  node->prev = ref_node;
  ref_node->next = node;
  (node->next)->prev = node;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void LST_insert_node_before (tListNode * node, tListNode * ref_node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  node->next = ref_node;
  node->prev = ref_node->prev;
  ref_node->prev = node;
  (node->prev)->next = node;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


int list_get_size (tListNode * listHead)
{
  int size = 0;
  tListNode * temp;
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  temp = listHead->next;
  while (temp != listHead)
  {
    size++;
    temp = temp->next;
  }

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/

  return (size);
}

void list_get_next_node (tListNode * ref_node, tListNode ** node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  *node = ref_node->next;

  __set_PRIMASK(primask_bit);     /**< Restore PRIMASK bit*/
}


void list_get_prev_node (tListNode * ref_node, tListNode ** node)
{
  uint32_t primask_bit;

  primask_bit = __get_PRIMASK();  /**< backup PRIMASK bit */
  __disable_irq();                  /**< Disable all interrupts by setting PRIMASK bit on Cortex*/

  *node = ref_node->prev;

  __set_PRIMASK(primask_bit);      /**< Restore PRIMASK bit*/
}

