#include "hw.h"
#include "spi.h"
#include "nrf24.h"

#define PIN_NRF_CE  P2_4
#define PIN_NRF_CSN P2_3


void nrf24_begin(uint8_t datarate, uint8_t channel)
{
    digitalWrite(PIN_NRF_CE, LOW);
    digitalWrite(PIN_NRF_CSN, HIGH);

    spi_transmit(0);  // fix issue in G2553

    nrf24_reg(NRF24_REG_CONFIG, 0x00);
    nrf24_reg(NRF24_REG_AA, 0x03);
    nrf24_reg(NRF24_REG_RXADDR, 0x03);
    nrf24_reg(NRF24_REG_RF_SET, 0x00);
    //nrf24_reg(NRF24_REG_STATUS, );
    nrf24_reg(NRF24_REG_DYNPD, 0x03);
    //nrf24_reg(NRF24_REG_FEATURE, DYNPAYLOAD);

    nrf24_reg(NRF24_CMD_FLUSH_TX, NRF24_CMD_NOP);
    nrf24_reg(NRF24_CMD_FLUSH_RX, NRF24_CMD_NOP);

    nrf24_reg(NRF24_REG_RF_CH, 10);
}

uint8_t nrf24_available()
{
    return 0;
}

uint8_t nrf24_reg(uint8_t reg, uint8_t value)
{
    uint8_t ret;

    digitalWrite(PIN_NRF_CSN, LOW);

    ret = spi_transmit(reg);

    if (reg < NRF24_CMD_FLUSH_TX)
        ret = spi_transmit(value);

    digitalWrite(PIN_NRF_CSN, HIGH);

    // delay(4us)

    return ret;
}
