/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_SPI_H__
#define __HW_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*!
 * @brief Initializes the SPI object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_SPI_Init(void);

/*!
 * @brief De-initializes the SPI object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_SPI_DeInit(void);

/*!
 * @brief Initializes the SPI IOs
 *
 * @param [IN] none
 */
void HW_SPI_IoInit(void);

/*!
 * @brief De-initializes the SPI IOs
 *
 * @param [IN] none
 */
void HW_SPI_IoDeInit(void);

/*!
 * @brief Sends outData and receives inData
 *
 * @param [IN] outData Byte to be sent
 * @retval inData      Received byte.
 */
uint8_t HW_SPI_InOut(uint8_t outData);



#ifdef __cplusplus
}
#endif

#endif  /* __HW_SPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/








