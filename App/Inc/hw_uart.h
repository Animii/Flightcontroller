#ifndef __HW_UART_H__
#define __HW_UART_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "hw.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*!
 * @brief Initializes the UART object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_UART_Init(void);

/*!
 * @brief De-initializes the UART object and MCU peripheral
 *
 * @param [IN] none
 */
void HW_UART_DeInit(void);

/*!
 * @brief Initializes the UART IOs
 *
 * @param [IN] none
 */
void HW_UART_IoInit(void);

/*!
 * @brief De-initializes the UART IOs
 *
 * @param [IN] none
 */
void HW_UART_IoDeInit(void);
void vprint(const char *fmt, va_list argp);
void HW_UART_PRINTF(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //__HW_UART_H__
 
