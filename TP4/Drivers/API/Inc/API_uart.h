/*
 * API_uart.h
 *
 *  Created on: 22 nov. 2021
 *      Author: martin
 */
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>


#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

typedef bool bool_t;

UART_HandleTypeDef UartHandle;

bool_t uartInit();
void uartSendString(uint8_t *pstring);



#endif /* API_INC_API_UART_H_ */
