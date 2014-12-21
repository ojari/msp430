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
//#include "lcd.h"
#include "ds1820.h"
#include "nexa.h"
#include "uart.h"
#endif

uint8_t stage;
uint8_t temp1;
uint8_t temp2;

void timer3()
{
  toggle_LED_RED;

  switch (stage) {
  case 0:
    uart_clear();
    uart_ch('m');
    /*
      uart_num(g_rtc_hour);
      uart_str(":");
      uart_num(g_rtc_min);
      uart_str(":");*/
    uart_num(g_rtc_sec);
    uart_ch(' ');
    uart_num(temp1);
    uart_ch(' ');
    uart_num(temp2);
    uart_str("\r\n");
    uart_start();
    break;
  case 1:
    ds1820_measure(PIN_OW1);
    break;
  case 2:
    temp1 = ds1820_read_temp(PIN_OW1);
    break;
  case 3:
    ds1820_measure(PIN_OW2);
    break;
  case 4:
    //_disable_interrupts();
    temp2 = ds1820_read_temp(PIN_OW2);
    //_enable_interrupts();
    break;
  case 5:
    //uart_str("  ");
    //uart_num(temp1);
    break;
  case 6:
    //lcd_clear();
    //lcd_str("Hello");
    break;
  case 7:
    nexa_send(NEXA_CH_1, NEXA_UNIT_1, NEXA_ON);
    break;
  }

  stage++;
  if (stage == 10)
    stage = 0;
}

void app_init()
{
	START_TIMER3(timer3);
	cb_uart_tx = uart_tx;
	stage = 0;
	nexa_init();
	//lcd_init();
	ds1820_init(PIN_OW1);
	ds1820_init(PIN_OW2);
}
