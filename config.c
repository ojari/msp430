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

struct PinData PORT_DATA[] = {
	[PIN_LED_RED] = { &P1OUT, BIT0 },
	[PIN_OW1] = { &P1OUT, BIT3},
	[PIN_OW2] = { &P1OUT, BIT4},
	[PIN_LCD_RS] = { &P1OUT, BIT5},
	[PIN_LED_GREEN] = { &P1OUT, BIT6},
	[PIN_LCD_ENABLE] = { &P1OUT, BIT7},
	[PIN_NEXA_OUT] = { &P2OUT, BIT0},
	[PIN_LCD_DATA1] = { &P2OUT, BIT2},
	[PIN_LCD_DATA2] = { &P2OUT, BIT3},
	[PIN_LCD_DATA3] = { &P2OUT, BIT4},
	[PIN_LCD_DATA4] = { &P2OUT, BIT5},
};

void digitalWrite(uint8_t pin, uint8_t mode)
{
	struct PinData pdata = PORT_DATA[pin];

	if (mode)
		*(pdata.port) |= pdata.bit;
	else
		*(pdata.port) &= ~pdata.bit;
}

void config_port_mode (uint8_t pin, uint8_t out)
{
	switch (pin)
	{
		case PIN_OW1:
			P1DIR &= ~BIT3;
			if (out)
			{
				P1DIR |= BIT3;
			}
			break;
		case PIN_OW2:
			P1DIR &= ~BIT4;
			if (out)
			{
				P1DIR |= BIT4;
			}
			break;
	}
}

uint8_t config_port_read (uint8_t pin)
{
	uint8_t ret=0;
	switch (pin)
	{
		case PIN_OW1:
			ret = ((P1IN & BIT3) == BIT3);
			break;
		case PIN_OW2:
			ret = ((P1IN & BIT4) == BIT4);
			break;
	}
	return ret;
}
