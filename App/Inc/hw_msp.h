#ifndef __HW_MSP_H__
#define __HW_MSP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/*!
 * \brief GPIOs Macro
 */

#define RCC_GPIO_CLK_ENABLE( __GPIO_PORT__ )              \
do {                                                    \
    switch( __GPIO_PORT__)                                \
    {                                                     \
      case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;    \
      case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;    \
      case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;    \
      case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;    \
    }                                                    \
  } while(0)

#define RCC_GPIO_CLK_DISABLE( __GPIO_PORT__ )              \
do {                                                    \
    switch( __GPIO_PORT__)                                \
    {                                                     \
      case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_DISABLE(); break;    \
      case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_DISABLE(); break;    \
      case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_DISABLE(); break;    \
      case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_DISABLE(); break;    \
    }                                                    \
  } while(0)

/* Exported functions ------------------------------------------------------- */

/*!
 * \brief Initializes the boards peripherals.
 */
void HW_Init(void);

/*!
* \brief De-initializes the target board peripherals to decrease power
*        consumption.
*/
void HW_DeInit(void);
/*!
 * \brief Configures the sytem Clock at start-up
 *
 * \param none
 * \retval none
 */
void SystemClock_Config(void);

/**
  * @brief  Configure all GPIO's to Analog input to reduce the power consumption
  * @param  None
  * @retval None
  */
void HW_GpioInit(void);

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __HW_MSP_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
