#include "spi.h"

void spi_begin()
{  
#define CLK BIT5
#define SOMI BIT6
#define SIMO BIT7

	P2SEL  |= CLK + SOMI + SIMO;
	P2SEL2 |= CLK + SOMI + SIMO;

    UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;
    UCB0CTL1 |= UCSSEL_2;
    UCB0BR0 = 10;                             // /10
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCB0RXIE;

   	UCB0CTL1 &= ~UCSWRST;
}

uint8_t spi_transmit(uint8_t data)
{
    while (!(IFG2 & UCB0TXIFG));              // USCI_A0 TX buffer ready?
    //while (!(UCB0IFG & UCTXIFG));

    IFG2 &= ~UCB0TXIFG;

    UCB0TXBUF = data;

    while (!(IFG2 & UCB0RXIFG));

    return UCB0RXBUF;
}
