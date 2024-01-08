#include "hw.h"
#include "ds1820.h"

#define USE_DS1820B

extern void ds1820_reset(uint16_t pin);
extern void usart_str(const char*);

void ds1820_begin(uint16_t pin)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	//	delay_us(5);
	//	ds1820_reset(pin);
}

void ds1820_reset(uint16_t pin)
{
	uint8_t presence;

	// do reset
	digitalWrite(pin, LOW);
	delay_us(500);   // min 480us
	//config_port_set(pin);
	pinMode(pin, INPUT);

	// do presense
	delay_us(80);   // wait for DS1820 to send presence
	presence = digitalRead(pin);
	delay_us(300);
	//if (presence)
	//	usart_str("E DS1 0\r\n");
	//else
	//	usart_str("DS1 found\r\n");
	pinMode(pin, OUTPUT);
}

void ds1820_write(uint16_t pin, uint8_t data)
{
	uint8_t i;

	for (i=0; i<8; i++) {
		digitalWrite(pin, LOW);
		if (data & (1<<i)) {      // send bit 1
			delay_us(5);
			digitalWrite(pin, HIGH);
			delay_us(60);
		}
		else {                    // send bit 0
			delay_us(62);
			digitalWrite(pin, HIGH);
			delay_us(3);			
		}
	}
}

uint8_t ds1820_read(uint8_t pin)
{
	uint8_t i;
	uint8_t ret = 0;

	digitalWrite(pin, HIGH);
	delay_us(2);
	for (i=1; i; i<<=1) {
	        delay_us(1);
		digitalWrite(pin, LOW);
		delay_us(4);
		pinMode(pin, INPUT);
		delay_us(9);
		if (digitalRead(pin)) {
		//if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)) {
			ret |= i;
		}
		delay_us(60);
		digitalWrite(pin, HIGH);
		pinMode(pin, OUTPUT);
		delay_us(4);
	}
	return ret;
}

void ds1820_measure(uint16_t pin)
{
	ds1820_reset(pin);
	ds1820_write(pin, DS1820_CMD_SKIP_ROM);
	ds1820_write(pin, DS1820_CMD_CONVERT);
}

// based on DS18S20 OPERATION EXAMPLE 3
//
uint8_t ds1820_read_temp(uint16_t pin)
{
	uint8_t temp_lsb;
	uint8_t temp_msb;
#ifndef USE_DS1820B
	uint8_t count_remain;
	uint8_t count_per_c;
#endif

	/*ds1820_reset(pin);
	ds1820_write(pin, DS1820_CMD_SKIP_ROM);
	ds1820_write(pin, DS1820_CMD_CONVERT);
	delay_ms(750);*/
	ds1820_reset(pin);
	ds1820_write(pin, DS1820_CMD_SKIP_ROM);
	delay_us(3);
	ds1820_write(pin, DS1820_CMD_READ_SCRATCHPAD);


	// Read scratchpad
	//
	temp_lsb = ds1820_read(pin);
	temp_msb = ds1820_read(pin);
	ds1820_read(pin); // Th register or user byte 1
	ds1820_read(pin); // Tl register or user byte 2
	ds1820_read(pin); // reserved
	ds1820_read(pin); // reserved
#ifdef USE_DS1820B
	ds1820_read(pin); // reserved
	ds1820_read(pin); // reserved
#else
	count_remain = ds1820_read(pin);
	count_per_c  = ds1820_read(pin);
#endif
	ds1820_read(pin); // CRC

	ds1820_reset(pin);

	return temp_lsb;
}
