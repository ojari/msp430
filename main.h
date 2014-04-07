#ifndef _MAIN_H
#define _MAIN_H

extern unsigned int g_events;

#define EV_TIMER1 0x01
#define EV_TIMER2 0x02
#define EV_TIMER3 0x04

typedef void (*callback)(void);

extern callback cb_timer1;
extern callback cb_timer2;
extern callback cb_timer3;




#endif
