#ifndef __NRF24_HAL_H
#define __NRF24_HAL_H


// Hardware abstraction layer for NRF24L01+ transceiver (hardware depended functions)
// GPIO pins definition
// GPIO pins initialization and control functions
// SPI transmit functions


// Peripheral libraries
#include "hw.h"


#define PIPEOUT = 0xE8E8F1F0E1LL;
// SPI port peripheral
#define nRF24_SPI_PORT             SPI2

// nRF24 GPIO peripherals
#define nRF24_GPIO_PERIPHERALS     RCC_APB2ENR_IOPBEN

// CE (chip enable) pin (PB11)
#define nRF24_CE_PORT              GPIOA
#define nRF24_CE_PIN               GPIO_PIN_3
#define nRF24_CE_L                 HW_GPIO_Write(nRF24_CE_PORT, nRF24_CE_PIN,RESET)
#define nRF24_CE_H                 HW_GPIO_Write(nRF24_CE_PORT, nRF24_CE_PIN,SET)

// CSN (chip select negative) pin (PB12)
#define nRF24_CSN_PORT             GPIOA
#define nRF24_CSN_PIN              GPIO_PIN_4
#define nRF24_CSN_L                HW_GPIO_Write(nRF24_CSN_PORT, nRF24_CSN_PIN,RESET)
#define nRF24_CSN_H                HW_GPIO_Write(nRF24_CSN_PORT, nRF24_CSN_PIN,SET)

// IRQ pin (PB10)
#define nRF24_IRQ_PORT             GPIOB
#define nRF24_IRQ_PIN              GPIO_PIN_10


// Macros for the RX on/off
#define nRF24_RX_ON                nRF24_CE_H
#define nRF24_RX_OFF               nRF24_CE_L


// Function prototypes
void nRF24_GPIO_Init(void);
uint8_t nRF24_LL_RW(uint8_t data);

#endif // __NRF24_HAL_H
