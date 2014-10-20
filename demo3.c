/**
 * A simple example of event system.
 *
 * Copyright 2014 Jari Ojanen
 */
#ifdef _SIMULATED_
#include <stdio.h>
#include "main.h"
#include "port_sim.h"
#else
#include <msp430.h>
#include <stdio.h>
#include "main.h"
#include "config.h"
#include "lcd.h"
#include "ds1820.h"
#endif

void timer3()
{
	toggle_LED_RED;

	ds1820_init(0);
	ds1820_read_temp(0);

	lcd_init();
	lcd_str("Hello");
}

void app_init()
{
	START_TIMER3(timer3);	
}
