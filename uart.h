/**
 * Copyright 2014 Jari Ojanen
 */
#pragma once

extern void uart_init();
extern void uart_clear();
extern void uart_start();
extern void uart_tx(); /// event handler for uart tx IRQ

extern void uart_ch(char ch);
extern void uart_str(char *str);
extern void uart_num(uint8_t num);
