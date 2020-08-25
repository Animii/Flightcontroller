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
#include "nrf24_platform.h"
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

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //int16_t acc[3] ={0};

  //HW_TIMER_PWM_ChangeDuty(1);
  
  //HW_UART_PRINTF("Start\n\r");


//#define RX
#ifdef RX
  uint8_t nRF24_payload[32]; // buffer for payload
  uint8_t payload_length;    // variable to store a length of received payload
  uint8_t pipe;              // pipe number
  nRF24_SetupRx();
#else
  uint8_t buffer[] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07};
  nRF24_SetupTx();
#endif

  while (1)
  {
#ifdef RX
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
      HW_UART_PRINTF("%d\n\r", pipe);
    }
#else
    volatile nRF24_TXResult st =  nRF24_TransmitPacket(buffer,4);
    UNUSED(st);
#endif
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
