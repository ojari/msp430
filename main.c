#include <msp430.h>
#include <stdio.h>
#include "main.h"

unsigned int g_event = 0;

callback cb_timer1 = NULL;
callback cb_timer2 = NULL;
callback cb_timer3 = NULL;

int main()
{
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
