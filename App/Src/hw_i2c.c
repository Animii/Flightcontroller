/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw_i2c.h"
#include <string.h>
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void HW_I2C_Init(void)
{
    HW_I2C_IoInit();

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}

void HW_I2C_IoInit(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* USER CODE BEGIN I2C1_MspInit 0 */

    /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* USER CODE BEGIN I2C1_MspInit 1 */

    /* USER CODE END I2C1_MspInit 1 */
}

void HW_I2C_MspDeInit(I2C_HandleTypeDef *i2cHandle)
{

    if (i2cHandle->Instance == I2C1)
    {
        /* USER CODE BEGIN I2C1_MspDeInit 0 */

        /* USER CODE END I2C1_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**I2C1 GPIO Configuration    
        PB6     ------> I2C1_SCL
        PB7     ------> I2C1_SDA 
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);

        /* USER CODE BEGIN I2C1_MspDeInit 1 */

        /* USER CODE END I2C1_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

uint8_t HW_I2C_IsI2CDeviceReady(uint8_t devAddr)
{
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, devAddr << 1, 1, HAL_MAX_DELAY);

    return (status == HAL_OK);
}

HAL_StatusTypeDef HW_I2C_ReadWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data)
{
    uint8_t temp[4];
    HAL_StatusTypeDef status = HW_I2C_ReadBytes(devAddr, regAddr, (uint8_t *)temp, 2);
    *data = (((uint16_t)temp[0]) << 8) | (temp[1]);
    return status;
}

HAL_StatusTypeDef HW_I2C_Read32bits(uint8_t devAddr, uint8_t regAddr, uint32_t *data)
{
    uint8_t temp[8];
    HAL_StatusTypeDef status = HW_I2C_ReadBytes(devAddr, regAddr, (uint8_t *)temp, 4);
    *data = ((uint32_t)temp[0]) << 24;
    *data |= ((uint32_t)temp[1]) << 16;
    *data |= ((uint32_t)temp[2]) << 8;
    *data |= ((uint32_t)temp[3]);
    return status;
}

HAL_StatusTypeDef HW_I2C_ReadBytes(uint8_t deviceAdd, uint8_t regAdd, uint8_t *data, uint8_t size)
{
    return HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(deviceAdd << 1), (uint16_t)regAdd, I2C_MEMADD_SIZE_8BIT, data, size, I2C_TIMEOUT);
    //HAL_StatusTypeDef status =  HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)deviceAdd << 1,&regAdd,1,I2C_TIMEOUT);
    //if(status != HAL_OK)
    // {
    //  return status;
    // }
    //return HAL_I2C_Master_Receive(&hi2c1, (uint16_t)deviceAdd << 1,data, size, I2C_TIMEOUT);
}

HAL_StatusTypeDef HW_I2C_ReadByte(uint8_t deviceAdd, uint8_t regAdd, uint8_t *data)
{
    return HW_I2C_ReadBytes(deviceAdd, regAdd, data, 1);
}

HAL_StatusTypeDef HW_I2C_ReadBits(uint8_t deviceAdd, uint8_t regAdd, uint8_t *data, uint8_t bitStart, uint8_t size)
{
    uint8_t b = 0;
    HAL_StatusTypeDef returnSatus = HW_I2C_ReadByte(deviceAdd, regAdd, &b);
    uint8_t mask = ((1 << size) - 1) << (bitStart - size + 1);
    b &= mask;
    b >>= (bitStart - size + 1);
    *data = b;

    return returnSatus;
}

HAL_StatusTypeDef HW_I2C_ReadBit(uint8_t deviceAdd, uint8_t regAdd, uint8_t *data, uint8_t bit)
{
    return HW_I2C_ReadBits(deviceAdd, regAdd, data, bit, 1);
}

HAL_StatusTypeDef HW_I2C_WriteBytes(uint8_t deviceAdd, uint8_t regAdd, uint8_t *data, uint8_t size)
{
    uint8_t buffer[size + 1];
    buffer[0] = regAdd;
    memcpy((buffer + 1), data, size);
    //return HAL_I2C_Master_Transmit(&hi2c1,deviceAdd << 1,buffer,size + 1,I2C_TIMEOUT);
    return HAL_I2C_Mem_Write(&hi2c1, deviceAdd << 1, regAdd, I2C_MEMADD_SIZE_8BIT, data, size, I2C_TIMEOUT);
}

HAL_StatusTypeDef HW_I2C_WriteByte(uint8_t deviceAdd,uint8_t regAdd,uint8_t data)
{
    return HW_I2C_WriteBytes(deviceAdd, regAdd, &data, 1);
}

HAL_StatusTypeDef HW_I2C_WriteBits(uint8_t deviceAdd, uint8_t regAdd, uint8_t data, uint8_t bitStart, uint8_t size)
{
    uint8_t b = 0;
    HW_I2C_ReadByte(deviceAdd, regAdd, &b);
    uint8_t mask = ((1 << size) - 1) << (bitStart - size + 1);

    data <<= (bitStart - size + 1); // shift data into correct position
    data &= mask;                   // zero all non-important bits in data
    b &= ~(mask);                   // zero all important bits in existing byte
    b |= data;                      // combine data with existing byte

    return HW_I2C_WriteByte(deviceAdd, regAdd, data);
}

HAL_StatusTypeDef HW_I2C_WriteBit(uint8_t deviceAdd, uint8_t regAdd, uint8_t bitNum, uint8_t data)
{
    uint8_t tmp = 0;
    HW_I2C_ReadByte(deviceAdd, regAdd, &tmp);
    tmp = (data != 0) ? (tmp | (1 << bitNum)) : (tmp & ~(1 << bitNum));
    return HW_I2C_WriteByte(deviceAdd, regAdd, tmp);
}

HAL_StatusTypeDef HW_I2C_WriteWord(uint8_t deviceAdd, uint8_t regAdd, uint16_t data)
{
    uint8_t towrite[2];
    towrite[0] = (uint8_t)(data >> 8); //MSB
    towrite[1] = (uint8_t)data;        //LSB
    HW_I2C_WriteBytes(deviceAdd, regAdd, (uint8_t *)towrite, 2);
    return HAL_OK;
}
HAL_StatusTypeDef HW_I2C_Write32Bits(uint8_t deviceAdd, uint8_t regAdd, uint32_t data)
{
    uint8_t towrite[4];
    towrite[0] = (uint8_t)(data >> 24); //MSB
    towrite[1] = (uint8_t)(data >> 16);
    towrite[2] = (uint8_t)(data >> 8);
    towrite[3] = (uint8_t)data;
    HW_I2C_WriteBytes(deviceAdd, regAdd, (uint8_t *)towrite, 4);
    return HAL_OK;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
