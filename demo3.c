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
#include "ds1820.h"
#include "nrf24.h"
#include "uart.h"
#include "spi.h"
#endif

uint8_t stage;
uint8_t temp1;
uint8_t temp2;
uint8_t led1_state = 1;
uint8_t led2_state = 1;

void timer1()
{
  digitalWrite(P_LED_RED, led1_state);
  led1_state = !led1_state;
}

void timer3()
{
  //digitalWrite(PIN_LED_RED, led2_state);
  //led2_state = !led2_state;

  if (nrf24_available()) {
    uart_ch('R');
  }

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
    ds1820_measure(P2_0);
    break;
  case 2:
    temp1 = ds1820_read_temp(P2_0);
    break;
  case 3:
    ds1820_measure(P2_1);
    break;
  case 4:
    //_disable_interrupts();
    temp2 = ds1820_read_temp(P2_1);
    //_enable_interrupts();
    break;
  }

  stage++;
  if (stage == 10)
    stage = 0;
}

void app_init()
{
	START_TIMER1(0x7FFF, timer1);
	START_TIMER3(timer3);	

	cb_uart_tx = uart_tx;
	stage = 0;
    spi_init();
	uart_init();
}

void app_begin()
{
    nrf24_begin(0, 70);
 
	ds1820_begin(P2_0);
	ds1820_begin(P2_1);
}
