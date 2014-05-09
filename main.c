/**
 * Copyright 2014 Jari Ojanen
 */
#include <msp430.h>
#include <stdio.h>
#include "main.h"
#include "port.h"

unsigned int g_event = 0;

callback cb_timer1 = NULL;
callback cb_timer2 = NULL;
callback cb_timer3 = NULL;

unsigned char g_rtc_sec = 0;
unsigned char g_rtc_min = 0;
unsigned char g_rtc_hour = 0;
unsigned char g_rtc_wday = 0;


__attribute__ ((__interrupt__(TIMER0_A0_VECTOR)))
static void timer1_isr()
{
	g_event |= EV_TIMER1;
	__bic_SR_register_on_exit(LPM0_bits);
} 

__attribute__ ((__interrupt__(TIMER1_A0_VECTOR)))
static void timer2_isr()
{
	g_event |= EV_TIMER2;
	__bic_SR_register_on_exit(LPM0_bits);
} 

__attribute__ ((__interrupt__(WDT_VECTOR)))
static void timer3_isr()
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

__attribute__((__interrupt__(PORT1_VECTOR)))
static void port1_isr()
{
	g_event |= EV_PORT1;
	__bic_SR_register_on_exit(LPM0_bits);
} 

__attribute__((__interrupt__(PORT2_VECTOR)))
static void port2_isr()
{
	g_event |= EV_PORT2;
	__bic_SR_register_on_exit(LPM0_bits);
} 

__attribute__((__interrupt__(USCIAB0TX_VECTOR)))
static void usci_tx_isr()
{
	g_event |= EV_TX;
	__bic_SR_register_on_exit(LPM0_bits);
} 

__attribute__((__interrupt__(USCIAB0RX_VECTOR)))
static void usci_rx_isr()
{
	g_event |= EV_RX;
	__bic_SR_register_on_exit(LPM0_bits);
} 

//------------------------------------------------------------------------------
int main()
{
	WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog timer
	BCSCTL3 |= LFXT1S_2;                // VLOCLK

	BCSCTL1 = CALBC1_1MHZ;                 // Set DCO to calibrated 1 MHz.
	DCOCTL = CALDCO_1MHZ;

	// Init timer1
	//
	TA0CCR0   = 0x7FFF;
	TA0CCTL0  = CCIE;
	TA0CTL = TASSEL_1 + MC_1 + ID_0; // SMCLK, up to CCR0, divider /8

	// Init timer2
	//
	TA1CCR0   = 0x3FFF;
	TA1CCTL0  = CCIE;
	TA1CTL = TASSEL_1 + MC_1 + ID_0; // SMCLK, up to CCR0, divider /8

	// Init timer3
	//
	WDTCTL = WDT_ADLY_1000;
	IE1 |= WDTIE;

	// main loop
	//
	port_init();
	app_init();

	//__enable_interrupt();
	while (1) {
		if (g_event == 0)
			__bis_SR_register(LPM0_bits + GIE);

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
			
	}
	return 0;
}
