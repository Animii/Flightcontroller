#ifndef __MPU6050_PLATFORM_H
#define __MPU6050_PLATFORM_H

#include "mpu6050_def.h"
#include "hw.h"
/**
 * @struct  MPU6050_Dev_t
 * @brief    Generic PAL device type that does link between API and platform abstraction layer
 *
 */
typedef struct {
    MPU6050_DevData_t Data;              

    /*!< user specific field */
    uint8_t I2cDevAddr;                /*!< i2c device address user specific field */
    int16_t nullPoint;
    volatile uint8_t irqFlag;

} MPU6050_Dev_t;


extern MPU6050_Dev_t MPU6050Dev;
/**
 * @brief   Declare the device Handle as a pointer of the structure @a MPU6050_Dev_t.
 *
 */
typedef MPU6050_Dev_t* MPU6050_DEV;

void MPU6050IrqHandler(void *context);

MPU6050_Error MPU6050_Init(void);

MPU6050_Error MPU6050_SetIntIrq(GpioIrqHandler *irqHandler);

void MPU6050_Delay(uint32_t delay);

MPU6050_Error MPU6050_ReadByte(MPU6050_DEV dev, uint8_t index, uint8_t *pdata);

MPU6050_Error MPU6050_ReadBytes(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint32_t count);

MPU6050_Error MPU6050_ReadBit(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint8_t bit);

MPU6050_Error MPU6050_ReadBits(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint8_t bitStart,uint8_t count);

MPU6050_Error MPU6050_WriteByte(MPU6050_DEV dev, uint8_t index, uint8_t data);

MPU6050_Error MPU6050_WriteBytes(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint32_t count);

MPU6050_Error MPU6050_WriteBit(MPU6050_DEV dev, uint8_t index, uint8_t data, uint8_t bit);

MPU6050_Error MPU6050_WriteBits(MPU6050_DEV dev, uint8_t index, uint8_t data, uint8_t bitStart,uint8_t count);

#endif