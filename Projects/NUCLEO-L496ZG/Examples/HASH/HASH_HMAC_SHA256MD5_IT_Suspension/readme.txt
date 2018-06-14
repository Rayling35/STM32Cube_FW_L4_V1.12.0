/**
  @page HASH_HMAC_SHA256MD5_IT_Suspension HMAC digest calculation suspension example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    HASH/HASH_HMAC_SHA256MD5_IT_Suspension/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the HMAC digest calculation suspension using MD5 and SHA-256 example.
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

This example describes how to suspend the HMAC digest computation when data are fed 
in Interrupt mode.

The example first computes the HMAC MD5 digest of a low priority block in entering 
input data in interrupt mode.

The processing is suspended in order to process a higher priority block to
compute its SHA-256 digest. For the higher priority block, data are entered in
interrupt mode as well.
Suspension request is triggered by an interrupts counter which is incremented each time
a 512-bit long block has been fed to the IP. Once the counter has reached an arbitrary
value, the low priority block processing is suspended.

It is shown how to save then how to restore later on the low priority block
context to resume its processing.
For both the low and high priority blocks, the computed digests are compared with
the expected ones.


LED1 is turned on when correct digest values are calculated.
In case of digest computation or initialization issue, LED3 is turned on. 

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Inc/main.h                  Header for main.c module  
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Src/stm32l4xx_it.c          Interrupt handlers
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Src/main.c                  Main program
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - HASH/HASH_HMAC_SHA256MD5_IT_Suspension/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L4A6xx devices.
  
  - This example has been tested with a STM32L4A6ZG mounted on a 
    Nucleo (144 pins) board and can be easily tailored to any other supported 
    device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 