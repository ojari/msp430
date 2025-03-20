/**
 * Copyright 2014 Jari Ojanen
 */
#include "hw.h"
#include "sram23a256.h"

void sram23a256_init(void) {
  set_SRAM_CS;
}

void sram23a256_write(uint16_t addr, uint8_t data) {
  clr_SRAM_CS;
  spi_send(S23A256_WRITE);
  spi_send(addr >> 8);
  spi_send(addr & 0xFF);
  spi_send(data);
  set_SRAM_CS;
}

uint8_t sram23a256_read(uint16_t addr) {
  uint8_t response;
  clr_SRAM_CS;
  spi_send(S23A256_READ);
  spi_send(addr >> 8);
  spi_send(addr & 0xFF);
  response = spi_read(0x00);
  set_SRAM_CS;
}
