#include "hw.h"
#include "config.h"

void config_port_init (void)
{
	P1DIR = BIT0 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
	P2DIR = BIT0 + BIT2 + BIT3 + BIT4 + BIT5;
}

struct PinData {
	volatile unsigned char *port;
	uint8_t bit;
};

/*
   P1_1  UCA0RX
   P1_2  UCA0TX
   P1_4  UCB0STE
   P1_5  UCB0CLK
   P1_6  UCB0SOMI
   P1_7  UCB0SIMO
*/
const struct PinData PORT_DATA[] = {
	[PIN_LED_RED] = { &P1OUT, BIT0 },
	[PIN_OW1] = { &P2OUT, BIT0},
	[PIN_OW2] = { &P2OUT, BIT1},
	[PIN_LED_GREEN] = { &P1OUT, BIT6},
	[PIN_NEXA_OUT] = { &P2OUT, BIT0},
/*	[PIN_LCD_RS] = { &P1OUT, BIT5},
	[PIN_LCD_ENABLE] = { &P1OUT, BIT7},
	[PIN_LCD_DATA1] = { &P2OUT, BIT2},
	[PIN_LCD_DATA2] = { &P2OUT, BIT3},
	[PIN_LCD_DATA3] = { &P2OUT, BIT4},
	[PIN_LCD_DATA4] = { &P2OUT, BIT5},*/
	[PIN_NRF_CSN] = { &P2OUT, BIT3},
	[PIN_NRF_CE] = { &P2OUT, BIT4},
};

void digitalWrite(uint8_t pin, uint8_t mode)
{
	struct PinData pdata = PORT_DATA[pin];

	if (mode)
		*(pdata.port) |= pdata.bit;
	else
		*(pdata.port) &= ~pdata.bit;
}

void pinMode(uint8_t pin, uint8_t out)
{
	struct PinData pdata = PORT_DATA[pin];

	if (out)
		*(pdata.port) |= pdata.bit;
	else
		*(pdata.port) &= ~(pdata.bit);	
}

uint8_t digitalRead(uint8_t pin)
{
	struct PinData pdata = PORT_DATA[pin];
	
	return (*(pdata.port) & pdata.bit) == pdata.bit;
}
