/**
 * Copyright 2014 Jari Ojanen
 */
#ifndef UART_H_
#define UART_H_

extern void uart_init();
extern void uart_clear();
extern void uart_start();

extern void uart_str(char *str);
extern void uart_num(uint8_t num);

#endif /* UART_H_ */
