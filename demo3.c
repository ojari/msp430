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
#include "hw.h"
#include <stdio.h>
#include "main.h"
#include "config.h"
#include "lcd.h"
#include "ds1820.h"
#include "nexa.h"
#endif

void timer3()
{
	uart_str("ping\n");
	uart_num(g_rtc_hour);
	uart_str(":");
	uart_num(g_rtc_min);
	uart_str(":");
	uart_num(g_rtc_sec);
	uart_str("\r\n");

	toggle_LED_RED;

	ds1820_init(0);
	ds1820_read_temp(0);

	lcd_str("Hello");

	nexa_send(NEXA_CH_1, NEXA_UNIT_1, NEXA_ON);
}

void app_init()
{
	START_TIMER3(timer3);	

	nexa_init();
	lcd_init();
}
