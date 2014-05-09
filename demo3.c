/**
 * A simple example of event system.
 *
 * Copyright 2014 Jari Ojanen
 */
#include <msp430.h>
#include <stdio.h>
#include "main.h"
#include "port.h"
#include "lcd.h"

void timer3()
{
	toggle_LED_RED;
}

void app_init()
{
	START_TIMER3(timer3);	
}
