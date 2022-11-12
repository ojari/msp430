#pragma once

#define HIGH 1
#define LOW  0

#define OUTPUT 1
#define INPUT 0

extern void config_port_init (void);
extern void digitalWrite(uint16_t pin, uint8_t mode);
extern void pinMode(uint16_t pin, uint8_t out);
extern uint8_t digitalRead(uint16_t pin);

#define P1_0 0x0001 // red LED
#define P1_1 0x0002 // UCA0RX
#define P1_2 0x0004 // UCA0TX
#define P1_3 0x0008
#define P1_4 0x0010
#define P1_5 0x0020  // SPI CLK
#define P1_6 0x0040  // SPI SOMI  |  green LED
#define P1_7 0x0080  // SPI SIMO

#define P2_0 0x0100
#define P2_1 0x0200
#define P2_2 0x0400
#define P2_3 0x0800
#define P2_4 0x1000
#define P2_5 0x2000
//#define P2_6 0x4000  32kHz Xtal
//#define P2_7 0x8000

#define P_LED_RED P1_0
