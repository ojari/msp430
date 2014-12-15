#include "hw.h"
#include "uart.h"

#define UART_BUFFER_SIZE 80

uint8_t *uart_size = 0;
uint8_t *uart_ptr = 0;

uint8_t uart_buffer[UART_BUFFER_SIZE];

void uart_init()
{
#define TX BIT2
#define RX BIT1

	P1SEL  |= RX + TX;
	P1SEL2 |= RX + TX;

	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 0x08;
	UCA0BR1 = 0x00;
	UCA0MCTL = UCBRS2 + UCBRS0; // modulation
	UCA0CTL1 &= ~UCSWRST;

	IFG2 &= ~(UCA0TXIFG | UCA0RXIFG);
}

void uart_clear()
{
	uart_ptr = uart_buffer;
	uart_size = uart_buffer;
}

void uart_start()
{
	UC0IE |= UCA0TXIE;
	UCA0TXBUF = *(uart_ptr);
}

void uart_tx()
{
	if (uart_ptr != uart_size) {
		uart_ptr++;
		UCA0TXBUF = *(uart_ptr);
	}
	else {
		UC0IE &= ~UCA0TXIE;
	}
}

void uart_ch(char ch)
{
#if 1
	*uart_size = ch;
	uart_size++;
#else
	while ( !(IFG2 & UCA0TXIFG));
	UCA0TXBUF = ch;
#endif
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
	char digit0, digit1, digit2='0';
	digit0 = '0'+(num % 10);
	num /= 10;
	digit1 = '0'+(num % 10);
	if (num > 10) {
		num /= 10;
		digit2 = '0'+(num % 10);
		uart_ch(digit2);
	}
	uart_ch(digit1);
	uart_ch(digit0);
}
