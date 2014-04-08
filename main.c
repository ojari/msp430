#include <msp430.h>
#include <stdio.h>
#include "main.h"

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
	__bic_SR_register_on_exit(LPM4_bits);
} 

__attribute__ ((__interrupt__(TIMER1_A0_VECTOR)))
static void timer2_isr()
{
	g_event |= EV_TIMER2;
	__bic_SR_register_on_exit(LPM4_bits);
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
	//	__bic_SR_register_on_exit(LPM4_bits);
} 

__attribute__((__interrupt__(PORT1_VECTOR)))
static void port1_isr()
{
	g_event |= EV_PORT1;
	__bic_SR_register_on_exit(LPM4_bits | GIE);
} 

__attribute__((__interrupt__(PORT2_VECTOR)))
static void port2_isr()
{
	g_event |= EV_PORT2;
	__bic_SR_register_on_exit(LPM4_bits | GIE);
} 

__attribute__((__interrupt__(USCIAB0TX_VECTOR)))
static void usci_tx_isr()
{
	g_event |= EV_TX;
	__bic_SR_register_on_exit(LPM4_bits | GIE);
} 

__attribute__((__interrupt__(USCIAB0RX_VECTOR)))
static void usci_rx_isr()
{
	g_event |= EV_RX;
	__bic_SR_register_on_exit(LPM4_bits | GIE);
} 

//------------------------------------------------------------------------------
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
