/**
******************************************************************************
* @file    BSP/Src/sensors.c 
* @author  MCD Application Team
* @brief   This example code shows how to use the QSPI Driver
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
* @{
*/

/** @addtogroup BSP
* @{
*/ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int16_t pDataXYZ[3] = {0};
float pGyroDataXYZ[3] = {0};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Test of LPS22HB pressure sensor.
  */
void Pressure_Test(void)
{
  uint32_t ret = 0;
  float press_value = 0;
  
  printf("\n*************************************************************\n");
  printf("\n********************** Pressure Test ************************\n");
  printf("\n*************************************************************\n\n");
  BSP_PSENSOR_Init();
  printf("\n*** Type n or N to get a first Pressure data ***\n\n");
  printf("\n*** Type q or Q to quit Pressure Test ***\n\n");
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      press_value = BSP_PSENSOR_ReadPressure();
      printf("PRESSURE is = %.2f mBar \n", press_value);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Pressure Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      printf("\n*** End of Pressure Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Pressure Test ***\n\n"); 
    }    
  }    
}

/**
  * @brief  Test of HTS221 humidity sensor.
  */
void Humidity_Test(void)
{
  uint32_t ret = 0;
  float humidity_value = 0;
  
  printf("\n*************************************************************\n");
  printf("\n********************** Humidity Test ************************\n");
  printf("\n*************************************************************\n\n");
  BSP_HSENSOR_Init();
  printf("\n*** Type n or N to get a first Humidity data ***\n\n");
  printf("\n*** Type q or Q to quit Humidity Test ***\n\n");
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      humidity_value = BSP_HSENSOR_ReadHumidity();
      printf("HUMIDITY is = %.2f %%\n", humidity_value);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Humidity Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      printf("\n*** End of Humidity Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Humidity Test ***\n\n"); 
    }    
  }    
}

/**
  * @brief  Test of HTS221 and LPS22HB temperature sensors.
  */
void Temperature_Test(void)
{
  uint32_t ret = 0;
  float temp_value = 0;
  
  printf("\n***************************************************************\n");
  printf("\n********************** Temperature Test ***********************\n");
  printf("\n***************************************************************\n\n");
  BSP_TSENSOR_Init();
#ifdef USE_LPS22HB_TEMP
  printf("\n*** Type n or N to get a first Temperature data from LPS22HB sensor ***\n\n"); 
#else /* USE_HTS221_TEMP */
  printf("\n*** Type n or N to get a first Temperature data from HTS221 sensor ***\n\n"); 
#endif
  printf("\n*** Type q or Q to quit Temperature Test ***\n\n");
  
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      temp_value = BSP_TSENSOR_ReadTemp();
      printf("TEMPERATURE is = %.2f °C\n", temp_value);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Temperature Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      printf("\n*** End of Temperature Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Temperature Test ***\n\n"); 
    }    
  }    
}

/**
  * @brief  Test of LSM6DSL accelerometer sensor.
  */
void Accelero_Test(void)
{
  uint32_t ret = 0;
  printf("\n***************************************************************\n");
  printf("\n******************* Accelerometer Test ************************\n");
  printf("\n***************************************************************\n\n");
  BSP_ACCELERO_Init();
  printf("\n*** Type n or N to get a first accelero data ***\n\n");
  printf("\n*** Type q or Q to quit accelerometer Test ***\n\n");
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      BSP_ACCELERO_AccGetXYZ(pDataXYZ);
      printf("ACCELERO_X = %d \n", pDataXYZ[0]);
      printf("ACCELERO_Y = %d \n", pDataXYZ[1]);
      printf("ACCELERO_Z = %d \n", pDataXYZ[2]);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Accelerometer Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      BSP_ACCELERO_DeInit();
      printf("\n*** End of Accelerometer Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Accelerometer Test ***\n\n"); 
    }    
  }    
}

/**
  * @brief  Test of LIS3MDL gyroscope sensor.
  */
void Gyro_Test(void)
{
  uint32_t ret = 0;
  printf("\n***************************************************************\n");
  printf("\n************************* Gyro Test ***************************\n");
  printf("\n***************************************************************\n\n");
  
  BSP_GYRO_Init();
  printf("\n*** Type n or N to get a first gyro data ***\n\n");
  printf("\n*** Type q or Q to quit Gyro Test ***\n\n");
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      BSP_GYRO_GetXYZ(pGyroDataXYZ);
      printf("GYRO_X = %.2f \n", pGyroDataXYZ[0]);
      printf("GYRO_Y = %.2f \n", pGyroDataXYZ[1]);
      printf("GYRO_Z = %.2f \n", pGyroDataXYZ[2]);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Gyro Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      BSP_GYRO_DeInit();
      printf("\n*** End of Gyro Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Gyro Test ***\n\n"); 
    }    
  }    
}

/**
  * @brief  Test of LIS3MDL magnetometer sensor.
  */
void Magneto_Test(void)
{
  uint32_t ret = 0;
  
  printf("\n***************************************************************\n");
  printf("\n************************ Magneto Test *************************\n");
  printf("\n***************************************************************\n\n");
  
  BSP_MAGNETO_Init();
  printf("\n*** Type n or N to get a first magno data ***\n\n"); 
  printf("\n*** Type q or Q to quit Magneto Test ***\n\n"); 
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      BSP_MAGNETO_GetXYZ(pDataXYZ);
      printf("MAGNETO_X = %d \n", pDataXYZ[0]);
      printf("MAGNETO_Y = %d \n", pDataXYZ[1]);
      printf("MAGNETO_Z = %d \n", pDataXYZ[2]);
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Magneto Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      BSP_MAGNETO_DeInit();
      printf("\n*** End of Magneto Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Type n or N to get a new data ***\n\n"); 
      printf("\n*** Type q or Q to quit Magneto Test ***\n\n"); 
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
