#include "mpu6050_platform.h"
#include "mpu6050.h"
#include "hw.h"

MPU6050_Dev_t MPU6050Dev;

void MPU6050IrqHandler(void *context)
{
    //vcom_Trace((uint8_t*)"Test",5);
}

MPU6050_Error MPU6050_Init(void)
{
    MPU6050_Error status = MPU6050_ERROR_NONE;
    int16_t acc[3];
    MPU6050Dev.Data.gscale = GFS_250DPS;
    MPU6050Dev.Data.ascale = AFS_2G;
    MPU6050Dev.irqFlag = false;
    MPU6050Dev.I2cDevAddr = MPU6050_ADDRESS;

    // wake up device-don't need this here if using calibration function below
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
    MPU6050_Delay(100); // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt

    // get stable time source
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, PWR_MGMT_1, 0x01); // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

    // Configure Gyro and Accelerometer
    // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
    // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
    // Maximum delay time is 4.9 ms corresponding to just over 200 Hz sample rate
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, CONFIG, 0x03);

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, SMPLRT_DIV, 0x00); // Use a 200 Hz rate; the same rate set in CONFIG above

    // Set gyroscope full scale range
    // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    uint8_t c = 0;
    HW_I2C_ReadByte(MPU6050Dev.I2cDevAddr, GYRO_CONFIG, &c);
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, GYRO_CONFIG, c & ~0xE0);                       // Clear self-test bits [7:5]
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, GYRO_CONFIG, c & ~c & ~0x18);                  // Clear AFS bits [4:3]
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, GYRO_CONFIG, c | MPU6050Dev.Data.gscale << 3); // Set full scale range for the gyro

    // Set accelerometer configuration
    HW_I2C_ReadByte(MPU6050Dev.I2cDevAddr, ACCEL_CONFIG, &c);
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, ACCEL_CONFIG, c & ~0xE0);                       // Clear self-test bits [7:5]
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, ACCEL_CONFIG, c & ~0x18);                       // Clear AFS bits [4:3]
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, ACCEL_CONFIG, c | MPU6050Dev.Data.ascale << 3); // Set full scale range for the accelerometer

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, INT_PIN_CFG, 0x0);
    HW_I2C_WriteByte(MPU6050Dev.I2cDevAddr, INT_ENABLE, 0x01); // Enable data ready (bit 0) interrupt
    MPU6050_SetIntDataReadyEnabled(&MPU6050Dev,1);
    status = MPU6050_ReadAcc(&MPU6050Dev, acc);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }

    MPU6050_SetIntIrq(MPU6050IrqHandler);

    return status;
}

MPU6050_Error MPU6050_SetIntIrq(GpioIrqHandler *irqHandler)
{
    GPIO_InitTypeDef initDef = {0};
    initDef.Pin = MPU_INT_PIN;
    initDef.Mode = MPU_INT_MODE;
    initDef.Pull = MPU_INT_PULL;
    HW_GPIO_Init(MPU_INT_PORT, MPU_INT_PIN, &initDef);
    HW_GPIO_SetIrq(MPU_INT_PORT, MPU_INT_PIN, 0, irqHandler);
    return MPU6050_ERROR_NONE;
}

void MPU6050_Delay(uint32_t delay)
{
    HAL_Delay(delay);
}

MPU6050_Error MPU6050_ReadByte(MPU6050_DEV dev, uint8_t index, uint8_t *pdata)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    status_int = HW_I2C_ReadByte(dev->I2cDevAddr, index, pdata);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_ReadBytes(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint32_t count)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    if (count >= MPU6050_MAX_I2C_XFER_SIZE)
    {
        error = MPU6050_ERROR_INVALID_PARAMS;
    }

    status_int = HW_I2C_ReadBytes(dev->I2cDevAddr, index, pdata, count);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_ReadBit(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint8_t bit)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    status_int = HW_I2C_ReadBit(dev->I2cDevAddr, index, pdata, bit);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}
MPU6050_Error MPU6050_ReadBits(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint8_t bitStart, uint8_t count)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    status_int = HW_I2C_ReadBits(dev->I2cDevAddr, index, pdata, bitStart, count);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_WriteByte(MPU6050_DEV dev, uint8_t index, uint8_t data)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    status_int = HW_I2C_WriteByte(dev->I2cDevAddr, index, data);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_WriteBytes(MPU6050_DEV dev, uint8_t index, uint8_t *pdata, uint32_t count)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    if (count >= MPU6050_MAX_I2C_XFER_SIZE)
    {
        error = MPU6050_ERROR_INVALID_PARAMS;
    }

    status_int = HW_I2C_WriteBytes(dev->I2cDevAddr, index, pdata, count);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_WriteBit(MPU6050_DEV dev, uint8_t index, uint8_t bit, uint8_t data)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    status_int = HW_I2C_WriteBit(dev->I2cDevAddr, index, bit, data);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}

MPU6050_Error MPU6050_WriteBits(MPU6050_DEV dev, uint8_t index, uint8_t bitStart, uint8_t count, uint8_t data)
{
    MPU6050_Error error = MPU6050_ERROR_NONE;
    int32_t status_int = 0;

    if (count >= MPU6050_MAX_I2C_XFER_SIZE)
    {
        error = MPU6050_ERROR_INVALID_PARAMS;
    }

    status_int = HW_I2C_WriteBits(dev->I2cDevAddr, index, data, bitStart, count);

    if (status_int != 0)
        error = MPU6050_ERROR_CONTROL_INTERFACE;

    return error;
}