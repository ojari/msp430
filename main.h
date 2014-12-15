/**
 * Copyright 2014 Jari Ojanen
 */
#ifndef _MAIN_H
#define _MAIN_H

extern unsigned int g_events;

#define EV_TIMER1 0x0001
#define EV_TIMER2 0x0002
#define EV_TIMER3 0x0004
#define EV_PORT1  0x0008
#define EV_PORT2  0x0010
#define EV_TX     0x0020
#define EV_RX     0x0040

typedef void (*callback)(void);

extern callback cb_timer1;
extern callback cb_timer2;
extern callback cb_timer3;
extern callback cb_uart_tx;

extern unsigned char g_rtc_sec;
extern unsigned char g_rtc_min;
extern unsigned char g_rtc_hour;
extern unsigned char g_rtc_wday;

extern void app_init();

#define START_TIMER1(delay,fn) TA0CCR0 = delay; cb_timer1 = fn
#define START_TIMER2(delay,fn) TA1CCR0 = delay; cb_timer2 = fn
#define START_TIMER3(fn) cb_timer3 = fn

#ifdef _SIMULATED_
extern void bit_set(const char*);
extern void bit_clr(const char*);
extern void bit_toggle(const char*);
#endif

#endif
