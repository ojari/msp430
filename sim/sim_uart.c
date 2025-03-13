#include "hw.h"
#include "uart.h"
#include <stdio.h>

const char hexDigit[] = "0123456789ABCDEF";

void uart_init()
{
	// printf("uart_init\n");
}

void uart_clear()
{
	// printf("uart_clear\n");
}

void uart_start()
{
}

void uart_tx()
{
}

void uart_ch(char ch)
{
	printf("%c", ch);
}

void uart_str(char *str)
{
    while(*str) {
		uart_ch(*str);
        str++;
    }
}

void uart_num(uint8_t num)
{
	uart_ch(hexDigit[num >> 4]);
	uart_ch(hexDigit[num & 0x0F]);
}