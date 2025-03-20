#include "spi.h"

void spi_init() {
#define PIN_CLK BIT5
#define PIN_SOMI BIT6
#define PIN_SIMO BIT7

    UCB0CTL1 |= UCSWRST;  // put in SW reset

    UCB0CTL0 |= UCMSB + UCMST + UCSYNC;
    UCB0CTL1 |= UCSSEL_2;
    UCB0BR0 = 1;                             // /1
    UCB0BR1 = 0;

	P1SEL  |= PIN_CLK + PIN_SOMI + PIN_SIMO;
	P1SEL2 |= PIN_CLK + PIN_SOMI + PIN_SIMO;

    UCB0CTL1 &= ~UCSWRST;   // release SW reset

    IE2 |= UCB0RXIE + UCB0TXIE;
}

uint8_t spi_transmit(uint8_t data) {
    // while (!(IFG2 & UCB0TXIFG)) {}              // USCI_A0 TX buffer ready?
    while (UCB0STAT & UCBUSY) {}
    // while (!(UCB0IFG & UCTXIFG)) {}

    IFG2 &= ~UCB0TXIFG;

    UCB0TXBUF = data;

    // while (!(IFG2 & UCB0RXIFG)) {}
    while (UCB0STAT & UCBUSY) {}

    return UCB0RXBUF;
}
