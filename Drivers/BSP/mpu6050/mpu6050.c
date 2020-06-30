#include "mpu6050.h"

MPU6050_Error MPU6050_LPMotionInit(MPU6050_DEV dev)
{
    // The sensor has a high-pass filter necessary to invoke to allow the sensor motion detection algorithms work properly
    // Motion detection occurs on free-fall (acceleration below a threshold for some time for all axes), motion (acceleration
    // above a threshold for some time on at least one axis), and zero-motion toggle (acceleration on each axis less than a
    // threshold for some time sets this flag, motion above the threshold turns it off). The high-pass filter takes gravity out
    // consideration for these threshold evaluations; otherwise, the flags would be set all the time!

    uint8_t c;
    //  wake up device-don't need this here if using calibration function below
    MPU6050_WriteByte(dev, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
    // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt
    MPU6050_Delay(100);
    // get stable time source
    MPU6050_Error status = MPU6050_WriteByte(dev, PWR_MGMT_1, 0x01); // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    // Configure Gyro and Accelerometer
    // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
    // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
    // Maximum delay time is 4.9 ms corresponding to just over 200 Hz sample rate
    status = MPU6050_WriteByte(dev, CONFIG, 0x03);

    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    status = MPU6050_WriteByte(dev, SMPLRT_DIV, 0x04); // Use a 200 Hz rate; the same rate set in CONFIG above

    // Set gyroscope full scale range
    // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    status = MPU6050_ReadByte(dev, GYRO_CONFIG, &c);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, GYRO_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, GYRO_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, GYRO_CONFIG, c | dev->Data.gscale << 3); // Set full scale range for the gyro
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }

    // Set accelerometer configuration
    status = MPU6050_ReadByte(dev, ACCEL_CONFIG, &c);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, ACCEL_CONFIG, c & ~0xE0); // Clear self-test bits [7:5]
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, ACCEL_CONFIG, c & ~0x18); // Clear AFS bits [4:3]
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_WriteByte(dev, ACCEL_CONFIG, c | dev->Data.ascale << 3); // Set full scale range for the accelerometer
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    //status = MPU6050_WriteByte(dev, INT_PIN_CFG, 0x02);

    status = MPU6050_SetIntMotionEnabled(dev, 1); //Set Motion Detection interrupt enabled status.
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetIntFreefallEnabled(dev, 1);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetIntZeroMotionEnabled(dev, 0);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetIntFIFOBufferOverflowEnabled(dev, 0);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetIntDataReadyEnabled(dev, 0); //New interrupt enabled status
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetDHPFMode(dev, 0); //New high-pass filter configuration more than 1.25Hz pass
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetDLPFMode(dev, 0);
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetMotionDetectionThreshold(dev, 5); //20 - 2
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetMotionDetectionDuration(dev, 1); //New motion detection duration threshold value (LSB = 1ms)
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetInterruptMode(dev, 1); //New interrupt mode (0=active-high, 1=active-low)
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetInterruptDrive(dev, 0); //New interrupt drive mode (0=push-pull, 1=open-drain)
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetInterruptLatch(dev, 0); //New latch mode (0=50us-pulse, 1=latch-until-int-cleared)
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetInterruptLatchClear(dev, 1); //New latch clear mode (0=status-read-only, 1=any-register-read)
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetRate(dev, 7); //Set the rate to disable the gyroscope
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetWakeFrequency(dev, 0); //Wake up the accelerometer at 1.25Hz to save power
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetWakeCycleEnabled(dev, 1); //Enable only accel. ON - Low power mode, waking it up from time to time
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }

    MPU6050_Delay(50);

    status = MPU6050_SetTempSensorEnabled(dev, 0); //Disable tmp sensor
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetStandbyXGyroEnabled(dev, 1); //Disable GyroX
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetStandbyYGyroEnabled(dev, 1); //Disable GyroY
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    status = MPU6050_SetStandbyZGyroEnabled(dev, 1); //Disable GyroZ
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }

    return status;
}

MPU6050_Error MPU6050_ReadAcc(MPU6050_DEV dev, int16_t acc[3])
{
    uint8_t rawData[6];                                                          // x/y/z accel register data stored here
    MPU6050_Error status = MPU6050_ReadBytes(dev, ACCEL_XOUT_H, &rawData[0], 6); // Read the six raw data registers into data array
    if (status != MPU6050_ERROR_NONE)
    {
        return status;
    }
    acc[0] = (int16_t)((rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
    acc[1] = (int16_t)((rawData[2] << 8) | rawData[3]);
    acc[2] = (int16_t)((rawData[4] << 8) | rawData[5]);
    return status;
}

MPU6050_Error MPU6050_SetIntMotionEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, INT_ENABLE, INTERRUPT_MOT_BIT, enabled);
}

bool MPU6050_GetIntMotionEnabled(MPU6050_DEV dev)
{
    uint8_t enable = 0;
    MPU6050_ReadBit(dev, INT_ENABLE, &enable, INTERRUPT_MOT_BIT);
    return enable;
}

MPU6050_Error MPU6050_SetIntFreefallEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, INT_ENABLE, INTERRUPT_FF_BIT, enabled);
}

bool MPU6050_GetIntFreefallEnabled(MPU6050_DEV dev)
{
    uint8_t enable = 0;
    MPU6050_ReadBit(dev, INT_ENABLE, &enable, INTERRUPT_FF_BIT);
    return enable;
}

MPU6050_Error MPU6050_SetIntZeroMotionEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, INT_ENABLE, INTERRUPT_ZMOT_BIT, enabled);
}

bool MPU6050_GetIntZeroMotionEnabled(MPU6050_DEV dev)
{
    uint8_t enable = 0;
    MPU6050_ReadBit(dev, INT_ENABLE, &enable, INTERRUPT_ZMOT_BIT);
    return enable;
}

MPU6050_Error MPU6050_SetIntFIFOBufferOverflowEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, INT_ENABLE, INTERRUPT_FIFO_OFLOW_BIT, enabled);
}

bool MPU6050_GetIntFIFOBufferOverflowEnabled(MPU6050_DEV dev)
{
    uint8_t enable = 0;
    MPU6050_ReadBit(dev, INT_ENABLE, &enable, INTERRUPT_FIFO_OFLOW_BIT);
    return enable;
}

MPU6050_Error MPU6050_SetIntDataReadyEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, INT_ENABLE, INTERRUPT_DATA_RDY_BIT, enabled);
}

bool MPU6050_GetIntDataReadyEnabled(MPU6050_DEV dev)
{
    uint8_t enable = 0;
    MPU6050_ReadBit(dev, INT_ENABLE, &enable, INTERRUPT_DATA_RDY_BIT);
    return enable;
}

MPU6050_Error MPU6050_SetDHPFMode(MPU6050_DEV dev, uint8_t bandwidth)
{
    return MPU6050_WriteBits(dev, ACCEL_CONFIG, ACONFIG_ACCEL_HPF_BIT, ACONFIG_ACCEL_HPF_LENGTH, bandwidth);
}

uint8_t MPU6050_GetDHPFMode(MPU6050_DEV dev)
{
    uint8_t data = 0;
    MPU6050_ReadBits(dev, ACCEL_CONFIG, &data, ACONFIG_ACCEL_HPF_BIT, ACONFIG_ACCEL_HPF_LENGTH);
    return data;
}

MPU6050_Error MPU6050_SetDLPFMode(MPU6050_DEV dev, uint8_t mode)
{
    return MPU6050_WriteBits(dev, CONFIG, CFG_DLPF_CFG_BIT, CFG_DLPF_CFG_LENGTH, mode);
}

uint8_t MPU6050_GetDLPFMode(MPU6050_DEV dev)
{
    uint8_t data = 0;
    MPU6050_ReadBits(dev, CONFIG, &data, CFG_DLPF_CFG_BIT, CFG_DLPF_CFG_LENGTH);
    return data;
}

uint8_t MPU6050_SetMotionDetectionThreshold(MPU6050_DEV dev, uint8_t threshold)
{
    return MPU6050_WriteByte(dev, MOT_THR, threshold);
}
uint8_t MPU6050_GetMotionDetectionThreshold(MPU6050_DEV dev)
{
    uint8_t data = 0;
    MPU6050_ReadByte(dev, MOT_THR, &data);
    return data;
}

MPU6050_Error MPU6050_SetMotionDetectionDuration(MPU6050_DEV dev, uint8_t duration)
{
    return MPU6050_WriteByte(dev, MOT_DUR, duration);
}

uint8_t MPU6050_GetMotionDetectionDuration(MPU6050_DEV dev)
{
    uint8_t data = 0;
    MPU6050_ReadByte(dev, MOT_DUR, &data);
    return data;
}

MPU6050_Error MPU6050_SetInterruptMode(MPU6050_DEV dev, bool mode)
{
    return MPU6050_WriteBit(dev, INT_PIN_CFG, INTCFG_INT_LEVEL_BIT, mode);
}

MPU6050_Error MPU6050_SetInterruptDrive(MPU6050_DEV dev, bool drive)
{
    return MPU6050_WriteBit(dev, INT_PIN_CFG, INTCFG_INT_OPEN_BIT, drive);
}

MPU6050_Error MPU6050_SetInterruptLatch(MPU6050_DEV dev, bool latch)
{
    return MPU6050_WriteBit(dev, INT_PIN_CFG, INTCFG_LATCH_INT_EN_BIT, latch);
}

MPU6050_Error MPU6050_SetInterruptLatchClear(MPU6050_DEV dev, bool clear)
{
    return MPU6050_WriteBit(dev, INT_PIN_CFG, INTCFG_INT_RD_CLEAR_BIT, clear);
}

MPU6050_Error MPU6050_SetRate(MPU6050_DEV dev, uint8_t rate)
{
    return MPU6050_WriteByte(dev, SMPLRT_DIV, rate);
}

MPU6050_Error MPU6050_SetWakeFrequency(MPU6050_DEV dev, uint8_t frequency)
{
    return MPU6050_WriteBits(dev, PWR_MGMT_2, PWR2_LP_WAKE_CTRL_BIT, PWR2_LP_WAKE_CTRL_LENGTH, frequency);
}

MPU6050_Error MPU6050_SetWakeCycleEnabled(MPU6050_DEV dev, bool enabled)
{
    return MPU6050_WriteBit(dev, PWR_MGMT_1, PWR1_CYCLE_BIT, enabled);
}

MPU6050_Error MPU6050_SetTempSensorEnabled(MPU6050_DEV dev, bool enable)
{
    return MPU6050_WriteBit(dev, PWR_MGMT_1, PWR1_TEMP_DIS_BIT, !enable);
}

MPU6050_Error MPU6050_SetStandbyXGyroEnabled(MPU6050_DEV dev, bool enable)
{
    return MPU6050_WriteBit(dev, PWR_MGMT_2, PWR2_STBY_XG_BIT, enable);
}

MPU6050_Error MPU6050_SetStandbyYGyroEnabled(MPU6050_DEV dev, bool enable)
{
    return MPU6050_WriteBit(dev, PWR_MGMT_2, PWR2_STBY_YG_BIT, enable);
}

MPU6050_Error MPU6050_SetStandbyZGyroEnabled(MPU6050_DEV dev, bool enable)
{
    return MPU6050_WriteBit(dev, PWR_MGMT_2, PWR2_STBY_ZG_BIT, enable);
}