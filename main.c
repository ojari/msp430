#include <msp430.h>
#include <stdio.h>
#include "main.h"

unsigned int g_event = 0;

callback cb_timer1 = NULL;
callback cb_timer2 = NULL;
callback cb_timer3 = NULL;

__attribute__ ((__interrupt__(TIMER1_A0_VECTOR)))
static void timer1_isr()
{
	__bic_SR_register_on_exit(LPM4_bits);
} 

__attribute__((__interrupt__(PORT1_VECTOR)))
static void port1_isr()
{
	P1IFG &= ~BIT3;
	__bic_SR_register_on_exit(LPM4_bits | GIE);
} 


int main()
{
	WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog timer

	while (1) {
		if (g_event & EV_TIMER1) {
			cb_timer1();
			g_event &= ~EV_TIMER1;
		}
		if (g_event & EV_TIMER2) {
			cb_timer2();
			g_event &= ~EV_TIMER2;
		}
			
	}
	return 0;
}
