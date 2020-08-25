

#include "hw_uart.h"
#include "stm32f1xx_hal_uart.h"

static UART_HandleTypeDef huart;

void HW_UART_Init(void)
{
    HW_UART_IoInit();
    huart.Instance = USART1;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        Error_Handler();
    }
    
}

void HW_UART_DeInit(void)
{
    
}

void HW_UART_IoInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE END USART1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = UART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(UART_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(UART_RX_PORT, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_USART1_ENABLE();
}

void HW_UART_IoDeInit(void)
{
    /* Peripheral clock disable */
    //__HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    //HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
}

void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if (0 < vsprintf(string, fmt, argp)) // build string
    {
        HAL_UART_Transmit(&huart, (uint8_t *)string, strlen(string), 0xffffffu); // send message via UART
    }
}

void HW_UART_PRINTF(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
}