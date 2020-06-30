/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "mpu6050.h"
#include "mpu6050_platform.h"
#include "nrf24.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the hardware*/
  HW_Init();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /* USER CODE BEGIN TIM1_Init 2 */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  /**TIM1 GPIO Configuration    
    PA11     ------> TIM1_CH4 
    */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  //volatile HAL_StatusTypeDef s =
  nRF24_CE_H;                // start receiving
  uint8_t ADDR[] = {0xE8, 0xE8, 0xF1, 0xF0, 0xE1}; // the address for RX pipe
  nRF24_DisableAA(0xFF);                           // disable ShockBurst
  nRF24_SetRFChannel(76);                          // set RF channel to 2490MHz
  nRF24_SetDataRate(nRF24_DR_250kbps);             // 2Mbit/s data rate
  nRF24_SetCRCScheme(nRF24_CRC_1byte);             // 1-byte CRC scheme
  nRF24_SetAddrWidth(5);                           // address width is 5 bytes
  nRF24_SetAddr(nRF24_PIPE1, ADDR);                // program pipe address
  nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_OFF, 10);  // enable RX pipe#1 with Auto-ACK: disabled, payload length: 10 bytes
  nRF24_SetOperationalMode(nRF24_MODE_RX);         // switch transceiver to the RX mode
  nRF24_SetPowerMode(nRF24_PWR_UP);                // wake-up transceiver (in case if it sleeping)

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //int16_t acc[3] ={0};
  _Atomic uint8_t b = 0;
  _Atomic uint32_t i = 0;
  HW_TIMER_PWM_ChangeDuty(1);

  uint8_t nRF24_payload[32]; // buffer for payload
  uint8_t payload_length;    // variable to store a length of received payload
  uint8_t pipe;              // pipe number

  while (1)
  {
    if (nRF24_GetStatus_RXFIFO() != nRF24_STATUS_RXFIFO_EMPTY)
    {
      // the RX FIFO have some data, take a note what nRF24 can hold up to three payloads of 32 bytes...
      pipe = nRF24_ReadPayload(nRF24_payload, &payload_length); // read a payload to buffer
      nRF24_ClearIRQFlags();
                                                                // clear any pending IRQ bits
                                                                // now the nRF24_payload buffer holds received data
                                                                // payload_length variable holds a length of received data
                                                                // pipe variable holds a number of the pipe which has received the data
                                                                // ... do something with received data ...
                                                                HW_UART_PRINTF("%d\n",pipe);
    }
    
    /* USER CODE END WHILE */
    if (1)
    {

      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      MPU6050_ReadBit(&MPU6050Dev, 0x3A, (uint8_t *)&b, 0);
      //HW_UART_PRINTF("In %d ", b);
      //HW_UART_PRINTF("\n");

      //HW_UART_PRINTF("Out %d ", i);
      //HW_UART_PRINTF("\n");
      i = 0;
    }
    else
    {

      MPU6050_ReadBit(&MPU6050Dev, 0x3A, (uint8_t *)&b, 0);
      //HW_UART_PRINTF("In %d ", b);
      //HW_UART_PRINTF("\n");
      i++;
    }
  }

  //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

  /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
