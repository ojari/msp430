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




#endif
