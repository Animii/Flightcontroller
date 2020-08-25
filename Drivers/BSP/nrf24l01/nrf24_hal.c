#include "nrf24_hal.h"


// Configure the GPIO lines of the nRF24L01 transceiver
// note: IRQ pin must be configured separately
void nRF24_GPIO_Init(void) {
    GPIO_InitTypeDef PORT;

    // Configure CSN pin
	PORT.Mode = GPIO_MODE_OUTPUT_PP;
	PORT.Speed= GPIO_SPEED_FREQ_HIGH;
	PORT.Pin = nRF24_CSN_PIN;
	HW_GPIO_Init(nRF24_CSN_PORT,nRF24_CSN_PIN, &PORT);
	nRF24_CSN_H;

	// Configure CE pin
	PORT.Pin = nRF24_CE_PIN;
	HW_GPIO_Init(nRF24_CE_PORT,nRF24_CE_PIN, &PORT);
	nRF24_CE_L();
}

// Low level SPI transmit/receive function (hardware depended)
// input:
//   data - value to transmit via SPI
// return: value received from SPI
uint8_t nRF24_LL_RW(uint8_t data) {
	// Return received byte
	return HW_SPI_InOut(data);
}
