#include "hw.h"
#include "config.h"

void config_port_init(void) {
	P1DIR = BIT0 + BIT3 + BIT4;
	P2DIR = BIT0 + BIT2 + BIT3 + BIT4 + BIT5;
}

void digitalWrite(uint16_t pin, uint8_t mode) {
	if (mode) {
		if (pin < 256) {
			P1OUT |= pin;
		} else {
			P2OUT |= (pin >> 8);
		}
	} else {
		if (pin < 256) {
			P1OUT &= ~pin;
		} else {
			P2OUT &= ~(pin >> 8);
		}
	}
}

void pinMode(uint16_t pin, uint8_t out) {
	if (out) {
		if (pin < 256)
			P1DIR |= pin;
		else
			P2DIR |= (pin >> 8);
	} else {
		if (pin < 256)
			P1DIR &= ~pin;
		else
			P2DIR &= ~(pin >> 8);
	}
}

uint8_t digitalRead(uint16_t pin) {
	if (pin < 256) {
		return (P1IN & pin) == pin;
	}

	uint8_t p = pin >> 8;

	return (P2IN & p) == p;
}
