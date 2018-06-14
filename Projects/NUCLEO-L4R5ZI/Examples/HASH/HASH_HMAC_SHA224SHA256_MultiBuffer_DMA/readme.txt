/**
  @page HASH_HMAC_SHA224SHA256_MultiBuffer_DMA  HASH and HMAC multi-buffer digest calculation using SHA224 and SHA256 example with DMA transfer
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/readme.txt
  * @author  MCD Application Team
  * @brief   Description of HASH and HMAC multi-buffer digest calculation using SHA224 and SHA256 example with DMA transfer.
  ******************************************************************************
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
  @endverbatim

@par Example Description 

This example describes how to handle text messages larger than the maximum DMA 
transfer length. In this case, the input data have to be split into several buffers 
with sizes within the DMA limit, and the buffers must be consecutively fed to the 
HASH peripheral.

It is shown how to use the HASH peripheral to hash multi buffer data using SHA-224, 
HMAC SHA-224 and HMAC SHA-256 algorithms with DMA transfer.

The same text message is split in several buffers and is processed by the following 
algorithms and multi buffers configurations:
- SHA-224, the message is split in 5 buffers that are successively fed to the IP.
- HMAC SHA-224, the message is split in 5 buffers that are successively fed to the IP.
- HMAC SHA-256, the message is split in 2 buffers that are successively fed to the IP.

The key used is long type (2088 bit = 261 bytes).
The HASH and HMAC SHA-224 message digest result is a 224-bit (28-byte) data and the 
HMAC SHA-256 message digest result is a 256-bit (32-byte) data.

When HASH SHA-224 and HMAC SHA-224 (respectively HMAC SHA-256) digest computations are successful, 
LED1 (resp. LED2) is turned on.
In case of digest computation or initialization issue, LED3 is turned on. 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Inc/main.h                  Header for main.c module  
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Src/stm32l4xx_it.c          Interrupt handlers
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Src/main.c                  Main program
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - HASH/HASH_HMAC_SHA224SHA256_MultiBuffer_DMA/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L4S5xx devices.
  
  - This example has been tested with a STM32L4S5xx mounted on a 
    Nucleo (144 pins) board and can be easily tailored to any other supported 
    device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 