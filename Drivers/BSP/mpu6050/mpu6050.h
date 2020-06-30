#ifndef __MPU6050_H
#define __MPU6050_H

#include <stdint.h>
#include <stdbool.h>

#include "mpu6050_def.h"
#include "mpu6050_platform.h"

MPU6050_Error MPU6050_LPMotionInit(MPU6050_DEV dev);

MPU6050_Error MPU6050_ReadAcc(MPU6050_DEV dev, int16_t acc[3]);
MPU6050_Error MPU6050_SetIntMotionEnabled(MPU6050_DEV dev, bool enabled);
bool MPU6050_GetIntMotionEnabled(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetIntFreefallEnabled(MPU6050_DEV dev, bool enabled);
bool MPU6050_GetIntFreefallEnabled(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetIntZeroMotionEnabled(MPU6050_DEV dev, bool enabled);
bool MPU6050_GetIntZeroMotionEnabled(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetIntFIFOBufferOverflowEnabled(MPU6050_DEV dev, bool enabled);
bool MPU6050_GetIntFIFOBufferOverflowEnabled(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetIntDataReadyEnabled(MPU6050_DEV dev, bool enabled);
bool MPU6050_GetIntDataReadyEnabled(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetDHPFMode(MPU6050_DEV dev, uint8_t bandwidth);
uint8_t MPU6050_GetDHPFMode(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetDLPFMode(MPU6050_DEV dev, uint8_t mode);
uint8_t MPU6050_GetDLPFMode(MPU6050_DEV dev);

uint8_t MPU6050_SetMotionDetectionThreshold(MPU6050_DEV dev, uint8_t threshold);
uint8_t MPU6050_GetMotionDetectionThreshold(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetMotionDetectionDuration(MPU6050_DEV dev, uint8_t duration);
uint8_t MPU6050_GetMotionDetectionDuration(MPU6050_DEV dev);

MPU6050_Error MPU6050_SetInterruptMode(MPU6050_DEV dev, bool mode);
MPU6050_Error MPU6050_SetInterruptDrive(MPU6050_DEV dev, bool drive);
MPU6050_Error MPU6050_SetInterruptLatch(MPU6050_DEV dev, bool latch);
MPU6050_Error MPU6050_SetInterruptLatchClear(MPU6050_DEV dev, bool clear);

MPU6050_Error MPU6050_SetRate(MPU6050_DEV dev, uint8_t rate);
MPU6050_Error MPU6050_SetWakeFrequency(MPU6050_DEV dev, uint8_t frequency);
MPU6050_Error MPU6050_SetWakeCycleEnabled(MPU6050_DEV dev, bool enabled);

MPU6050_Error MPU6050_SetTempSensorEnabled(MPU6050_DEV dev, bool enable);
MPU6050_Error MPU6050_SetStandbyXGyroEnabled(MPU6050_DEV dev, bool enable);
MPU6050_Error MPU6050_SetStandbyYGyroEnabled(MPU6050_DEV dev, bool enable);
MPU6050_Error MPU6050_SetStandbyZGyroEnabled(MPU6050_DEV dev, bool enable);
#endif //__MPU6050_H