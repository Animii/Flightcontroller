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

#ifdef __cplusplus
}
#endif

#endif /* __HW_CONF_L0_H__ */