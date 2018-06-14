/**
  @page DMA2D_MemToMemWithPFC DMA2D Memory to Memory with PFC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    DMA2D/DMA2D_MemToMemWithPFC/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DMA2D Memory to Memory with PFC example.
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
  @endverbatim

@par Example Description

  This example provides a description of how to configure DMA2D peripheral for transfer 
  in Memory_to_Memory with Pixel Format Conversion (PFC) Mode.

  At the beginning of the main program the HAL_Init() function is called to reset 
  all the peripherals, initialize the Flash interface and the systick.
  Then the SystemClock_Config() function is used to configure the system
  clock (SYSCLK) to run at 80 MHz.
 
  In this basic example the goal is to explain the different fields of the DMA2D 
  structure in the case of Memory_to_Memory with pixel format conversion (PFC) transfer mode
  and the difference between pixel coded on 32bits (ARGB8888 format) and coded on 16bits (RGB565 format).
  
  An image is transferred with DMA2D from the Flash memory to the LCD and during the transfer,
  a pixel format conversion is applied from ARGB8888 (32 bpp) to RGB565 (16 bpp).   
  
 How to convert pixel format from ARGB8888 to RGB565 ?
 => transparency information is discarded 
 => only the five MSBs (for R and B) and six MSBs (for G) are taken into account 
 eg : 0x A7..A0  B7..B0 C7..C0 D7..D0 -->  B7..B3 C7..C2 D7..D3    
          |_|     |_|    |_|    |_|         |_|    |_|    |_|
           A       R      G      B           R      G      B  
         
Generally speaking, 
 => if the number of bits per pixel in source data is more then the number of 
    bits per pixel in destination data, only the MSB are taken into account
    
 => else, if the number of bits per pixel in source data is less then the number 
    of bits per pixel in destination data, a bit replication of MSB in LSB is applied
    
    eg : from ARGB1555 to ARGB8888       PFC
    0xAB35 --> 0b1 01010 11001 10101   -------> 0b11111111 01010010 11001110 10101101     
                 A   R     G     B          --> 0xFF       52       CE       AD

STM32L496G-Discovery board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when there is an initialization or a DMA2D transfer error.
 - LED2 is ON when the DMA2D transfer is complete.
         
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents
  
    - DMA2D/DMA2D_MemToMemWithPFC/Inc/main.h                      Main configuration file
    - DMA2D/DMA2D_MemToMemWithPFC/Inc/stm32l4xx_it.h              Interrupt handlers header file
    - DMA2D/DMA2D_MemToMemWithPFC/Inc/stm32l4xx_hal_conf.h        HAL configuration file
    - DMA2D/DMA2D_MemToMemWithPFC/Inc/ARGB8888_300x120.h          image to be converted and transferred by DMA2D. 
    - DMA2D/DMA2D_MemToMemWithPFC/Src/main.c                      Main program  
    - DMA2D/DMA2D_MemToMemWithPFC/Src/stm32l4xx_it.c              Interrupt handlers
    - DMA2D/DMA2D_MemToMemWithPFC/Src/stm32l4xx_hal_msp.c         HAL MSP module    
    - DMA2D/DMA2D_MemToMemWithPFC/Src/system_stm32l4xx.c          STM32L4xx system clock configuration file

@par Hardware and Software environment  

  - This example runs on STM32L496xx devices.
  
  - This example has been tested with STM32L496G-Discovery boards and can be easily 
    tailored to any other supported device and development board. 


@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
            
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
                                   