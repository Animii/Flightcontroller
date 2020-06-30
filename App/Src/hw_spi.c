/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board SPI driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
/**
  ******************************************************************************
  * @file    hw_spi.c
  * @author  MCD Application Team
  * @brief   manages the SPI interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static SPI_HandleTypeDef hspi;
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/*!
 * @brief Initializes the SPI object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_SPI_Init(void)
{

    /*##-1- Configure the SPI peripheral */
    /* Set the SPI parameters */
 
    hspi.Instance = SPI1;

    hspi.Instance = SPI1;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.Direction = SPI_DIRECTION_2LINES;
    hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi.Init.CRCPolynomial = 10;

    __HAL_RCC_SPI1_CLK_ENABLE();

    if (HAL_SPI_Init(&hspi) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }

    /*##-2- Configure the SPI GPIOs */
    HW_SPI_IoInit();
}

/*!
 * @brief De-initializes the SPI object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_SPI_DeInit(void)
{

    HAL_SPI_DeInit(&hspi);

    /*##-1- Reset peripherals ####*/
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();
    /*##-2- Configure the SPI GPIOs */
    HW_SPI_IoDeInit();
}

void HW_SPI_IoInit(void)
{
    GPIO_InitTypeDef initStruct = {0};

    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    initStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    initStruct.Mode = GPIO_MODE_AF_PP;
    initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &initStruct);

    initStruct.Pin = GPIO_PIN_6;
    initStruct.Mode = GPIO_MODE_INPUT;
    initStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &initStruct);
    /*
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;

  HW_GPIO_Init(RADIO_NSS_PORT, RADIO_NSS_PIN, &initStruct);

  HW_GPIO_Write(RADIO_NSS_PORT, RADIO_NSS_PIN, 1);
  */
}

void HW_SPI_IoDeInit(void)
{
    //GPIO_InitTypeDef initStruct = {0};

    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
}

/*!
 * @brief Sends outData and receives inData
 *
 * @param [IN] outData Byte to be sent
 * @retval inData      Received byte.
 */
uint8_t HW_SPI_InOut(uint8_t txData)
{
    uint8_t rxData;

    HAL_SPI_TransmitReceive(&hspi, (uint8_t *)&txData, (uint8_t *)&rxData, 1, HAL_MAX_DELAY);

    return rxData;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
