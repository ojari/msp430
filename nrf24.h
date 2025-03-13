#pragma once

#include "hw.h"

#define MODULE_NRF24  0x01

#define NRF24_REG_CONFIG    0x00
#define NRF24_REG_AA        0x01  // auto ack
#define NRF24_REG_RXADDR    0x02
#define NRF24_REG_AW        0x03  // address width
#define NRF24_REG_RETRANS   0x04
#define NRF24_REG_RF_CH     0x05
#define NRF24_REG_RF_SET    0x06
#define NRF24_REG_STATUS    0x07
#define NRF24_REG_RX_ADDR0  0x0A // RX address pipe0..
#define NRF24_REG_RX_ADDR1  0x0B
#define NRF24_REG_RX_ADDR2  0x0C
#define NRF24_REG_RX_ADDR3  0x0D
#define NRF24_REG_RX_ADDR4  0x0E
#define NRF24_REG_RX_ADDR5  0x0F
#define NRF24_REG_TX_ADDR   0x10
#define NRF24_REG_RX_PW0    0x11 // RX payload size pipe0..
#define NRF24_REG_RX_PW1    0x12
#define NRF24_REG_RX_PW2    0x13
#define NRF24_REG_RX_PW3    0x14
#define NRF24_REG_RX_PW4    0x15
#define NRF24_REG_RX_PW5    0x16
#define NRF24_REG_FIFO_STAT 0x17
#define NRF24_REG_DYNPD     0x1C
#define NRF24_REG_FEATURE   0x1D
#define NRF24_CMD_FLUSH_TX  0xE1
#define NRF24_CMD_FLUSH_RX  0xE2
#define NRF24_CMD_NOP       0xFF

// Bit values
//
// NRF24_REG_RF_SET
//
#define NRF24_RF_DR_LOW             0x20
#define NRF24_PLL_LOCK              0x10
#define NRF24_RF_DR_HIGH            0x08
#define NRF24_RF_PWR_n18dBm         0x00 // -18 dBm
#define NRF24_RF_PWR_n12dBm         0x02 // -12 dBm
#define NRF24_RF_PWR_n6dBm          0x04 // -6 dBm
#define NRF24_RF_PWR_0dBm           0x06 // 0 dBm

// NRF24_REG_Aw
//
#define NRF24_AW_3BYTES             0x01 // 3 bytes
#define NRF24_AW_4BYTES             0x02 // 4 bytes
#define NRF24_AW_5BYTES             0x03 // 5 bytes

extern void nrf24_begin(uint8_t datarate, uint8_t channel);
extern void nrf24_set_rx_address(uint8_t *addr);
extern void nrf24_enable_rx();
extern uint8_t nrf24_available();
extern uint8_t nrf24_read(void *buffer, uint8_t length);


extern uint8_t nrf24_reg(uint8_t reg, uint8_t value);
