/**
 * Copyright 2014 Jari Ojanen
 * 
 * Device driver for Microchip 23A256 serial SRAM
 */
#pragma once

#define S23A256_READ  0x03
#define S23A256_WRITE 0x02
#define S23A256_RDSR  0x05  // Read status register
#define S23A256_WRSR  0x01  // Write status register

#define S23A256_MODE_BYTE 0x00
#define S23A256_MODE_PAGE 0x80
#define S23A256_MODE_SEQ  0x40
#define S23A256_HOLD      0x01

extern void sram23a256_init(void);
extern void sram23a256_write(uint16_t addr, uint8_t data);
extern uint8_t sram23a256_read(uint16_t addr);
