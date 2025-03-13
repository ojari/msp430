#pragma once

#define NEXA_UNIT_1    0x03
#define NEXA_UNIT_2    0x02
#define NEXA_UNIT_3    0x01
#define NEXA_UNIT_4    0x00

#define NEXA_CH_1   0x0C
#define NEXA_CH_2   0x08
#define NEXA_CH_3   0x04
#define NEXA_CH_4   0x00

#define NEXA_ON     0x00
#define NEXA_OFF    0x10

extern void nexa_init(void);
extern void nexa_send(uint8_t channel, uint8_t unit, uint8_t status);
