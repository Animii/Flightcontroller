#include "nrf24_platform.h"

void nRF24_SetupTx(void)
{
  uint8_t ADDR[] = {0xE8, 0xE8, 0xF1, 0xF0, 0xE1}; // the address for RX pipe
  nRF24_DisableAA(0xFF);                           // disable ShockBurst
  nRF24_SetRFChannel(90);                          // set RF channel to 2490MHz
  nRF24_SetDataRate(nRF24_DR_250kbps);             // 2Mbit/s data rate
  nRF24_SetCRCScheme(nRF24_CRC_1byte);             // 1-byte CRC scheme
  nRF24_SetAddrWidth(5);                           // address width is 5 bytes
  nRF24_SetTXPower(nRF24_TXPWR_0dBm);              // configure TX power
  nRF24_SetAutoRetr(nRF24_ARD_NONE, 0);
  nRF24_SetAddr(nRF24_PIPETX, ADDR);               // program TX address
  nRF24_SetOperationalMode(nRF24_MODE_TX);         // switch transceiver to the TX mode
  nRF24_SetPowerMode(nRF24_PWR_UP);                // wake-up transceiver (in case if it sleeping)
  // the nRF24 is ready for transmission, upload a payload, then pull CE pin to HIGH and it will transmit a packet...
}
void nRF24_SetupRx(void)
{
  uint8_t ADDR[] = {0xE8, 0xE8, 0xF1, 0xF0, 0xE1}; // the address for RX pipe
  nRF24_DisableAA(0xFF);                           // disable ShockBurst
  nRF24_SetRFChannel(90);                          // set RF channel to 2490MHz
  nRF24_SetDataRate(nRF24_DR_250kbps);             // 2Mbit/s data rate
  nRF24_SetCRCScheme(nRF24_CRC_1byte);             // 1-byte CRC scheme
  nRF24_SetAddrWidth(5);                           // address width is 5 bytes
  nRF24_SetAddr(nRF24_PIPE1, ADDR);                // program pipe address
  nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_OFF, 10);  // enable RX pipe#1 with Auto-ACK: disabled, payload length: 10 bytes
  nRF24_SetOperationalMode(nRF24_MODE_RX);         // switch transceiver to the RX mode
  nRF24_SetPowerMode(nRF24_PWR_UP);                // wake-up transceiver (in case if it sleeping)
  nRF24_CE_H();                                      // start receiving
}

nRF24_TXResult nRF24_TransmitPacket(uint8_t *pBuf, uint8_t length) {
	volatile uint32_t wait = nRF24_WAIT_TIMEOUT;
	uint8_t status;

	// Deassert the CE pin (in case if it still high)
	nRF24_CE_L();

	// Transfer a data from the specified buffer to the TX FIFO
	nRF24_WritePayload(pBuf, length);

	// Start a transmission by asserting CE pin (must be held at least 10us)
	nRF24_CE_H();

	// Poll the transceiver status register until one of the following flags will be set:
	//   TX_DS  - means the packet has been transmitted
	//   MAX_RT - means the maximum number of TX retransmits happened
	// note: this solution is far from perfect, better to use IRQ instead of polling the status
	do {
		status = nRF24_GetStatus();
		if (status & (nRF24_FLAG_TX_DS | nRF24_FLAG_MAX_RT)) {
			break;
		}
	} while (wait--);

	// Deassert the CE pin (Standby-II --> Standby-I)
	nRF24_CE_L();

	if (!wait) {
		// Timeout
		return nRF24_TX_TIMEOUT;
	}

	// Clear pending IRQ flags
    nRF24_ClearIRQFlags();

	if (status & nRF24_FLAG_MAX_RT) {
		// Auto retransmit counter exceeds the programmed maximum limit (FIFO is not removed)
		return nRF24_TX_MAXRT;
	}

	if (status & nRF24_FLAG_TX_DS) {
		// Successful transmission
		return nRF24_TX_SUCCESS;
	}

	// Some banana happens, a payload remains in the TX FIFO, flush it
	nRF24_FlushTX();

	return nRF24_TX_ERROR;
}