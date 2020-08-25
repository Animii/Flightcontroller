/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONF_F1_H__
#define __HW_CONF_F1_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* MPU6050 I/O definition */
#define MPU_INT_PORT GPIOB
#define MPU_INT_PIN GPIO_PIN_10
#define MPU_INT_MODE GPIO_MODE_IT_RISING
#define MPU_INT_PULL GPIO_NOPULL

#define UART_TX_PIN GPIO_PIN_6
#define UART_TX_PORT GPIOB
#define UART_RX_PIN GPIO_PIN_7
#define UART_RX_PORT GPIOB

#define I2C1_SCL_PIN GPIO_PIN_8
#define I2C1_SCL_PORT GPIOB

#define I2C1_SDA_PIN GPIO_PIN_9
#define I2C1_SDA_PORT GPIOB

#define I2C1_REMAP() __HAL_AFIO_REMAP_I2C1_ENABLE()
#ifdef __cplusplus
}
#endif

#endif /* __HW_CONF_L0_H__ */