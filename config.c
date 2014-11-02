#include "hw.h"
#include "config.h"

void config_port_init (void)
{
	P1DIR = BIT0 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
	P2DIR = BIT0 + BIT2 + BIT3 + BIT4 + BIT5;
}

void config_port_set (uint8_t pin)
{
	switch (pin)
	{
		case PIN_LED_RED:
			P1OUT |= BIT0;
			break;
		case PIN_OW1:
			P1OUT |= BIT3;
			break;
		case PIN_OW2:
			P1OUT |= BIT4;
			break;
		case PIN_LCD_RS:
			P1OUT |= BIT5;
			break;
		case PIN_LED_GREEN:
			P1OUT |= BIT6;
			break;
		case PIN_LCD_ENABLE:
			P1OUT |= BIT7;
			break;
		case PIN_NEXA_OUT:
			P2OUT |= BIT0;
			break;
		case PIN_LCD_DATA1:
			P2OUT |= BIT2;
			break;
		case PIN_LCD_DATA2:
			P2OUT |= BIT3;
			break;
		case PIN_LCD_DATA3:
			P2OUT |= BIT4;
			break;
		case PIN_LCD_DATA4:
			P2OUT |= BIT5;
			break;
	}
}

void config_port_clear (uint8_t pin)
{
	switch (pin)
	{
		case PIN_LED_RED:
			P1OUT &= ~BIT0;
			break;
		case PIN_OW1:
			P1OUT &= ~BIT3;
			break;
		case PIN_OW2:
			P1OUT &= ~BIT4;
			break;
		case PIN_LCD_RS:
			P1OUT &= ~BIT5;
			break;
		case PIN_LED_GREEN:
			P1OUT &= ~BIT6;
			break;
		case PIN_LCD_ENABLE:
			P1OUT &= ~BIT7;
			break;
		case PIN_NEXA_OUT:
			P2OUT &= ~BIT0;
			break;
		case PIN_LCD_DATA1:
			P2OUT &= ~BIT2;
			break;
		case PIN_LCD_DATA2:
			P2OUT &= ~BIT3;
			break;
		case PIN_LCD_DATA3:
			P2OUT &= ~BIT4;
			break;
		case PIN_LCD_DATA4:
			P2OUT &= ~BIT5;
			break;
	}
}

void config_port_mode (uint8_t pin, uint8_t out)
{
	switch (pin)
	{
		case OW1:
			P1DIR &= ~BIT3;
			if (out)
			{
				P1DIR |= BIT3;
			}
			break;
		case OW2:
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
