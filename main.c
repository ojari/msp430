/**
 * Copyright 2014 Jari Ojanen
 */
#include "hw.h"
#include <stdio.h>
#include "main.h"
#include "uart.h"
#include "config.h"

unsigned int g_event = 0;

callback cb_timer1 = NULL;
callback cb_timer2 = NULL;
callback cb_timer3 = NULL;
callback cb_uart_tx = NULL;

unsigned char g_rtc_wday = 0;
unsigned char g_rtc_hour = 17;
unsigned char g_rtc_min = 40;
unsigned char g_rtc_sec = 0;

#ifdef GCC
__attribute__ ((__interrupt__(TIMER0_A0_VECTOR)))
static void timer1_isr()
#else
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer1_isr(void)
#endif
{
	g_event |= EV_TIMER1;
	__bic_SR_register_on_exit(LPM0_bits);
} 

#ifdef GCC
__attribute__ ((__interrupt__(TIMER1_A0_VECTOR)))
static void timer2_isr()
#else
#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer2_isr(void)
#endif
{
	TA1CCTL0 &= ~CCIFG;

	g_event |= EV_TIMER2;
	__bic_SR_register_on_exit(LPM0_bits);
} 

#ifdef GCC
__attribute__ ((__interrupt__(WDT_VECTOR)))
static void timer3_isr()
#else
#pragma vector=WDT_VECTOR
__interrupt void timer3_isr(void)
#endif
{
	g_rtc_sec++;
	if (g_rtc_sec > 59) {
		g_rtc_sec = 0;
		g_rtc_min++;
		if (g_rtc_min > 59) {
			g_rtc_min = 0;
			g_rtc_hour++;
			if (g_rtc_hour > 23) {
				g_rtc_hour = 0;
				g_rtc_wday++;
				if (g_rtc_wday > 6) {
					g_rtc_wday = 0;
				}
			}
		}
	}
	//toggle_LED_RED;
	g_event |= EV_TIMER3;
	__bic_SR_register_on_exit(LPM0_bits);
} 

#ifdef GCC
__attribute__((__interrupt__(PORT1_VECTOR)))
static void port1_isr()
#else
#pragma vector=PORT1_VECTOR
__interrupt void port1_isr(void)
#endif
{
	g_event |= EV_PORT1;
	__bic_SR_register_on_exit(LPM0_bits);
} 

#ifdef GCC
__attribute__((__interrupt__(PORT2_VECTOR)))
static void port2_isr()
#else
#pragma vector=PORT2_VECTOR
__interrupt void port2_isr(void)
#endif
{
	g_event |= EV_PORT2;
	__bic_SR_register_on_exit(LPM0_bits);
} 

/*
#ifdef GCC
__attribute__((__interrupt__(USCIAB0TX_VECTOR)))
static void usci_tx_isr()
#else
#pragma vector=USCIAB0TX_VECTOR
__interrupt void usci_tx_isr(void)
#endif
{
	IFG2 &= ~UCA0TXIFG;

	g_event |= EV_TX;
	__bic_SR_register_on_exit(LPM0_bits);
} */

/*
#ifdef GCC
__attribute__((__interrupt__(USCIAB0RX_VECTOR)))
static void usci_rx_isr()
#else
#pragma vector=USCIAB0RX_VECTOR
__interrupt void usci_rx_isr(void)
#endif
{
	IFG2 &= ~UCA0RXIFG;

	g_event |= EV_RX;
	__bic_SR_register_on_exit(LPM0_bits);
} 
*/
/*void uart_init()
{
#define TX BIT2
#define RX BIT1

	P1SEL  |= RX + TX;
	P1SEL2 |= RX + TX;

	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 104;        // 9600 baud
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0; // modulation
	//UCA0MCTL = UCBRS2 + UCBRS0; // modulation
	UCA0CTL1 &= ~UCSWRST;
	UC0IE |= UCA0RXIE;
}
*/
//------------------------------------------------------------------------------
int main()
{
	WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
#if 1
	BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
	DCOCTL = 0x00;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	BCSCTL1 |= XT2OFF | DIVA_0;
	BCSCTL3 = XT2S_0 | LFXT1S_0 | XCAP_1;

	/*do {
        IFG1 &= ~OFIFG; // Clear OSC fault flag
        __delay_cycles(50);  // 50us delay
    } while (IFG1 & OFIFG);
	*/
	WDTCTL = WDTPW | WDTTMSEL | WDTSSEL;
#else
	BCSCTL3 |= LFXT1S_2;                  // VLOCLK

	BCSCTL1 = CALBC1_1MHZ;                // Set DCO to calibrated 1 MHz.
	DCOCTL = CALDCO_1MHZ;

	//BCSCTL1 |= DIVA_0;  // ACLK / 8
	BCSCTL3 |= XCAP_3;
#endif
	// Init timer1
	//
	TA0CCR0   = 0x7FFF;
	TA0CCTL0  = CCIE;
	TA0CTL = TASSEL_1 + MC_1 + ID_0; // ACLK, up to CCR0, divider /1

	// Init timer2
	//
	TA1CCR0   = 0x3FFF;
	TA1CCTL0  = CCIE;
	TA1CTL = TASSEL_1 + MC_1 + ID_0; // ACLK, up to CCR0, divider /1

	// Init timer3
	//
	WDTCTL = WDT_ADLY_1000;
	IE1 |= WDTIE;


	// main loop
	//
	config_port_init();
    app_init();
    
    __enable_interrupt();
    
	app_begin();

	uart_ch('S');

	//if (BCSCTL3 & LFXT1OF)
	//	uart_str("osc fault\n");

	//__enable_interrupt();
	while (1) {
         if (g_event == 0) {
			//__bis_SR_register(LPM0_bits + GIE);
         }

		if (g_event & EV_TIMER1) {
			if (cb_timer1)
				cb_timer1();
			g_event &= ~EV_TIMER1;
		}
		if (g_event & EV_TIMER2) {
			if (cb_timer2)
				cb_timer2();
			g_event &= ~EV_TIMER2;
		}
		if (g_event & EV_TIMER3) {
			if (cb_timer3)
				cb_timer3();
			g_event &= ~EV_TIMER3;
		}
		if (g_event & EV_TX) {
			if (cb_uart_tx)
				cb_uart_tx();
			g_event &= ~EV_TX;
		}
	}
	return 0;
}
