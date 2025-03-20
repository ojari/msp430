/**
 * Copyright 2014 Jari Ojanen
 */
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "../ds1820.h"

unsigned int g_event = 0;

callback cb_timer1 = NULL;
callback cb_timer2 = NULL;
callback cb_timer3 = NULL;
callback cb_uart_tx = NULL;

unsigned char g_rtc_sec = 0;
unsigned char g_rtc_min = 0;
unsigned char g_rtc_hour = 0;
unsigned char g_rtc_wday = 0;

//------------------------------------------------------------------------------
void bit_toggle(const char* bitName) {
	printf("toggle %s\n", bitName);
}

//------------------------------------------------------------------------------
int onewire_read = 0;

int reg_simulator(int module, int reg, int value) {
	// printf("reg_simulator: %d %d %d\n", module, reg, value);

	if (module == MODULE_DS1820) {
		if (reg == 0xFF) {
			onewire_read++;
			if (onewire_read == 9) onewire_read = 1;
			return onewire_read;
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
int main() {
	int i;
	printf("Simulated\n");

	app_init();

	app_begin();

	for(i = 0; i < 44; i++) {
		// if (cb_timer1)
		// 	cb_timer1();
		if (cb_timer2)
			cb_timer2();
		if (cb_timer3)
			cb_timer3();
	}
	return 0;
}
