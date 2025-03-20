/**
 * A simple example of event system.
 *
 * Copyright 2014 Jari Ojanen
 */
#include <stdio.h>
#include "hw.h"
#include "main.h"
#include "config.h"
#include "lcd.h"


void app_init() {
	lcd_init();
	lcd_write('a');
	lcd_write('b');
	lcd_write('0');
	lcd_write('1');
}
