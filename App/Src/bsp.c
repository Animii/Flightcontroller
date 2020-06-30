#include "bsp.h"
#include "mpu6050.h"
/*
 * @brief  initialises the sensor
 *
 * @note
 * @retval None
 */
void  BSP_sensor_Init(void)
{
  /* USER CODE BEGIN 6 */
  MPU6050_Init();

  /* USER CODE END 6 */
}


