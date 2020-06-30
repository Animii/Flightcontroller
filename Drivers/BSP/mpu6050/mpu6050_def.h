#ifndef __MPU6050_DEF_H
#define __MPU6050_DEF_H

#include <stdint.h>

#define XGOFFS_TC 0x00 // Bit 7 PWR_MODE, bits 6:1 XG_OFFS_TC, bit 0 OTP_BNK_VLD
#define YGOFFS_TC 0x01
#define ZGOFFS_TC 0x02
#define X_FINE_GAIN 0x03 // [7:0] fine gain
#define Y_FINE_GAIN 0x04
#define Z_FINE_GAIN 0x05
#define XA_OFFSET_H 0x06 // User-defined trim values for accelerometer
#define XA_OFFSET_L_TC 0x07
#define YA_OFFSET_H 0x08
#define YA_OFFSET_L_TC 0x09
#define ZA_OFFSET_H 0x0A
#define ZA_OFFSET_L_TC 0x0B
#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10
#define XG_OFFS_USRH 0x13 // User-defined trim values for gyroscope; supported in MPU-6050?
#define XG_OFFS_USRL 0x14
#define YG_OFFS_USRH 0x15
#define YG_OFFS_USRL 0x16
#define ZG_OFFS_USRH 0x17
#define ZG_OFFS_USRL 0x18
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG2 0x1D
#define FF_THR 0x1D    // Free-fall
#define FF_DUR 0x1E    // Free-fall
#define MOT_THR 0x1F   // Motion detection threshold bits [7:0]
#define MOT_DUR 0x20   // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
#define ZMOT_THR 0x21  // Zero-motion detection threshold bits [7:0]
#define ZRMOT_DUR 0x22 // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
#define FIFO_EN 0x23
#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define DMP_INT_STATUS 0x39 // Check DMP interrupt
#define INT_STATUS 0x3A
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define MOT_DETECT_STATUS 0x61
#define I2C_SLV0_DO 0x63
#define I2C_SLV1_DO 0x64
#define I2C_SLV2_DO 0x65
#define I2C_SLV3_DO 0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL 0x69
#define USER_CTRL 0x6A  // Bit 7 enable DMP, bit 3 reset DMP
#define PWR_MGMT_1 0x6B // Device defaults to the SLEEP mode
#define PWR_MGMT_2 0x6C
#define DMP_BANK 0x6D   // Activates a specific bank in the DMP
#define DMP_RW_PNT 0x6E // Set read/write pointer to a specific start address in specified DMP bank
#define DMP_REG 0x6F    // Register in DMP from which to read or to which to write
#define DMP_REG_1 0x70
#define DMP_REG_2 0x71
#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74
#define WHO_AM_I_MPU6050 0x75 // Should return 0x68

#define PWR1_DEVICE_RESET_BIT 7
#define PWR1_SLEEP_BIT 6
#define PWR1_CYCLE_BIT 5
#define PWR1_TEMP_DIS_BIT 3
#define PWR1_CLKSEL_BIT 2
#define PWR1_CLKSEL_LENGTH 3

#define INTERRUPT_FF_BIT 7
#define INTERRUPT_MOT_BIT 6
#define INTERRUPT_ZMOT_BIT 5
#define INTERRUPT_FIFO_OFLOW_BIT 4
#define INTERRUPT_I2C_MST_INT_BIT 3
#define INTERRUPT_PLL_RDY_INT_BIT 2
#define INTERRUPT_DMP_INT_BIT 1
#define INTERRUPT_DATA_RDY_BIT 0

#define ACONFIG_XA_ST_BIT 7
#define ACONFIG_YA_ST_BIT 6
#define ACONFIG_ZA_ST_BIT 5
#define ACONFIG_AFS_SEL_BIT 4
#define ACONFIG_AFS_SEL_LENGTH 2
#define ACONFIG_ACCEL_HPF_BIT 2
#define ACONFIG_ACCEL_HPF_LENGTH 3

#define CFG_EXT_SYNC_SET_BIT 5
#define CFG_EXT_SYNC_SET_LENGTH 3
#define CFG_DLPF_CFG_BIT 2
#define CFG_DLPF_CFG_LENGTH 3

#define INTCFG_INT_LEVEL_BIT 7
#define INTCFG_INT_OPEN_BIT 6
#define INTCFG_LATCH_INT_EN_BIT 5
#define INTCFG_INT_RD_CLEAR_BIT 4
#define INTCFG_FSYNC_INT_LEVEL_BIT 3
#define INTCFG_FSYNC_INT_EN_BIT 2
#define INTCFG_I2C_BYPASS_EN_BIT 1
#define INTCFG_CLKOUT_EN_BIT 0

#define PWR2_LP_WAKE_CTRL_BIT 7
#define PWR2_LP_WAKE_CTRL_LENGTH 2
#define PWR2_STBY_XA_BIT 5
#define PWR2_STBY_YA_BIT 4
#define PWR2_STBY_ZA_BIT 3
#define PWR2_STBY_XG_BIT 2
#define PWR2_STBY_YG_BIT 1
#define PWR2_STBY_ZG_BIT 0

#define MPU6050_ADDRESS (0x68) // Device address when ADO = 0
#define MPU6050_MAX_I2C_XFER_SIZE (64)

typedef enum 
{
    AFS_2G = 0,
    AFS_4G,
    AFS_8G,
    AFS_16G
}Ascale;

typedef enum 
{
    GFS_250DPS = 0,
    GFS_500DPS,
    GFS_1000DPS,
    GFS_2000DPS
}Gscale;
/**
 * @struct MPU6050_DevData_t
 *
 * @brief MPU6050 private data structure \n
 * End user should never access any of these field directly
 *
 * These must never access directly but only via macro
 */
typedef struct {
	Ascale ascale;
    Gscale gscale;
} MPU6050_DevData_t;

typedef int8_t MPU6050_Error;

#define MPU6050_ERROR_NONE ((MPU6050_Error) 0)
#define MPU6050_ERROR_TIMEOUT ((MPU6050_Error) 1)
#define MPU6050_ERROR_INVALID_PARAMS ((MPU6050_Error) 2)
#define MPU6050_ERROR_CONTROL_INTERFACE ((MPU6050_Error) 3)
#define MPU6050_ERROR_NOT_IMPLEMENTED ((MPU6050_Error) 254)

#endif