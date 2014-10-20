/**
 * A simple example of event system.
 *
 * Copyright 2014 Jari Ojanen
 */
#include <msp430.h>
#include <stdio.h>
#include "main.h"
#include "config.h"

void timer1()
{
	toggle_LED_RED;
}

void timer2()
{
	toggle_LED_GREEN;
}

void dummy()
{
}

void app_init()
{
	//cb_timer1 = dummy;
	START_TIMER1(0x7FFF, timer1);
	START_TIMER2(0x3FFF, timer2);	
}
