/*
 * uart_src.h
 *
 *  Created on: 18 Aug 2017
 *      Author: amjad
 */
#include <stdint.h>

#ifndef INCLUDE_UART_SRC_H_
#define INCLUDE_UART_SRC_H_

void uart_sendByte(uint8_t n);
void uart_sendChar(uint8_t c);
void uart_sendStr(uint8_t const * c);
void uart_sendText(uint8_t const * c, const uint16_t len);
void uart_sendHex_digit(uint8_t n);
void uart_sendHex8(uint8_t n);
void uart_sendHex16(uint16_t n);
void uart_sendHex32(uint32_t n);
void uart_init();



#endif /* INCLUDE_UART_SRC_H_ */
