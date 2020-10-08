#pragma once

#define HIGH 1
#define LOW  0

extern void config_port_init (void);
extern void digitalWrite(uint8_t pin, uint8_t mode);
extern void config_port_mode (uint8_t pin, uint8_t out);
extern uint8_t config_port_read (uint8_t pin);

#define PIN_LED_RED 1
#define PIN_OW1 2
#define get_OW1 (P1IN & BIT3) == BIT3
#define out_OW1 P1DIR |= BIT3
#define in_OW1 P1DIR &= ~BIT3
#define set_OW2 P1OUT |= BIT4
#define clr_OW2 P1OUT &= ~BIT4
#define toggle_OW2 P1OUT ^= BIT4
#define PIN_OW2 3
#define get_OW2 (P1IN & BIT4) == BIT4
#define out_OW2 P1DIR |= BIT4
#define in_OW2 P1DIR &= ~BIT4
#define PIN_LCD_RS 4
#define PIN_LED_GREEN 5
#define PIN_LCD_ENABLE 6
#define PIN_NEXA_OUT 7
#define PIN_LCD_DATA1 8
#define PIN_LCD_DATA2 9
#define PIN_LCD_DATA3 10
#define PIN_LCD_DATA4 11
