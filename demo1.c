/**
 * A simple example of event system.
 *
 * Copyright 2014 Jari Ojanen
 */
#include <msp430.h>
#include <stdio.h>
#include "main.h"

void timer1()
{
	START_TIMER1(0x7FFF, timer1);
}

void timer2()
{
	START_TIMER2(0xFFFF, timer2);
}

void app_init()
{
	START_TIMER1(0x7FFF, timer1);
	START_TIMER2(0xFFFF, timer2);	
}
