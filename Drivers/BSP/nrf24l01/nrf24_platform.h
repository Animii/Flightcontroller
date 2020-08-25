#ifndef __NRF24_PLATFORM_H
#define __NRF24_PLATFORM_H
#include "nrf24.h"
/* USER CODE BEGIN PFP */
#define nRF24_WAIT_TIMEOUT         (uint32_t)0x000FFFFF
/* USER CODE END PFP */
typedef enum {
	nRF24_TX_ERROR  = (uint8_t)0x00, // Unknown error
	nRF24_TX_SUCCESS,                // Packet has been transmitted successfully
	nRF24_TX_TIMEOUT,                // It was timeout during packet transmit
	nRF24_TX_MAXRT                   // Transmit failed with maximum auto retransmit count
} nRF24_TXResult;

void nRF24_SetupTx(void);
void nRF24_SetupRx(void);

nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length);
#endif //__NRF24_PLATFORM_H