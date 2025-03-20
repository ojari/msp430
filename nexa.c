#include "hw.h"
#include "nexa.h"

#define TRANSMITTER_CODE 0xFF00

void nexa_init(void) {
}

void nexa_send_bit(uint8_t bit) {
	digitalWrite(PIN_NEXA_OUT, HIGH);
	delay_us(250);
	digitalWrite(PIN_NEXA_OUT, LOW);
	if (bit)
		delay_us(250);
	else
		delay_us(5*250);

	digitalWrite(PIN_NEXA_OUT, HIGH);
	delay_us(250);
	digitalWrite(PIN_NEXA_OUT, LOW);
	if (bit)
		delay_us(5*250);
	else
		delay_us(250);
}

void nexa_send(uint8_t channel, uint8_t unit, uint8_t status) {
	uint32_t code;
	uint32_t bit;

	code = TRANSMITTER_CODE | channel | unit | status;

	for (bit=1; bit; bit <<= 1) {
		if (code & bit)
			nexa_send_bit(1);
		else
			nexa_send_bit(0);
	}
}
