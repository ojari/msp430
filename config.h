#pragma once

#define HIGH 1
#define LOW  0

#define OUTPUT 1
#define INPUT 0

extern void config_port_init (void);
extern void digitalWrite(uint8_t pin, uint8_t mode);
extern void pinMode(uint8_t pin, uint8_t out);
extern uint8_t digitalRead(uint8_t pin);

#define PIN_LED_RED 1
#define PIN_OW1 2
#define PIN_OW2 3
#define PIN_OW3 4
#define PIN_LED_GREEN 5
#define PIN_NEXA_OUT 6
/*#define PIN_LCD_RS 7
#define PIN_LCD_ENABLE 8
#define PIN_LCD_DATA1 9
#define PIN_LCD_DATA2 10
#define PIN_LCD_DATA3 11
#define PIN_LCD_DATA4 12*/
#define PIN_NRF_CSN 7
#define PIN_NRF_CE 8
