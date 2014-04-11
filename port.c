#include <msp430.h>
#include "port.h"

void port_init ()
{
	P1DIR = BIT0 + BIT3 + BIT5 + BIT6 + BIT7;
	P2DIR = BIT2 + BIT3 + BIT4 + BIT5;
}
