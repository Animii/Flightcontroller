/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_I2C_H
#define __HW_I2C_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */
#define I2C_TIMEOUT 1000
/* USER CODE END Private defines */

void HW_I2C_Init(void);
void HW_I2C_IoInit(void);

/* USER CODE BEGIN Prototypes */
uint8_t HW_I2C_IsI2CDeviceReady(uint8_t devAddr);

HAL_StatusTypeDef HW_I2C_ReadWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);
HAL_StatusTypeDef HW_I2C_Read32bits(uint8_t devAddr, uint8_t regAddr, uint32_t *data);

HAL_StatusTypeDef HW_I2C_ReadBytes(uint8_t deviceAdd,uint8_t regAdd,uint8_t *data,uint8_t size);
HAL_StatusTypeDef HW_I2C_ReadByte(uint8_t deviceAdd,uint8_t regAdd,uint8_t *data);
HAL_StatusTypeDef HW_I2C_ReadBits(uint8_t deviceAdd,uint8_t regAdd,uint8_t *data, uint8_t bitStart, uint8_t size);
HAL_StatusTypeDef HW_I2C_ReadBit(uint8_t deviceAdd,uint8_t regAdd,uint8_t *data,uint8_t bit);

HAL_StatusTypeDef HW_I2C_WriteBytes(uint8_t deviceAdd,uint8_t regAdd,uint8_t *data,uint8_t size);
HAL_StatusTypeDef HW_I2C_WriteByte(uint8_t deviceAdd,uint8_t regAdd,uint8_t data);
HAL_StatusTypeDef HW_I2C_WriteBits(uint8_t deviceAdd, uint8_t regAdd,uint8_t data, uint8_t bitStart, uint8_t size);
HAL_StatusTypeDef HW_I2C_WriteBit(uint8_t deviceAdd, uint8_t regAdd, uint8_t bitNum,uint8_t data);
HAL_StatusTypeDef HW_I2C_WriteWord(uint8_t deviceAdd, uint8_t regAdd, uint16_t data);
HAL_StatusTypeDef HW_I2C_Write32Bits(uint8_t deviceAdd, uint8_t regAdd, uint32_t data);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__HW_I2C_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
