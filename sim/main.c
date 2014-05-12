/**
 * Copyright 2014 Jari Ojanen
 */
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

//------------------------------------------------------------------------------
void bit_toggle(const char* bitName)
{
	printf("toggle %s\n", bitName);
}


//------------------------------------------------------------------------------
int main()
{
	printf("Simulated\n");

	app_init();
	
	if (cb_timer1)
		cb_timer1();
	if (cb_timer2)
		cb_timer2();
	if (cb_timer3)
		cb_timer3();


	return 0;
}
