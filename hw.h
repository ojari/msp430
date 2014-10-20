#ifndef _HW_H
#define _HW_H

#include <msp430.h>
#include <inttypes.h>
#include "config.h"

#define delay_us(x)  __delay_cycles(x)
#define delay_ms(x)  __delay_cycles(x*1000)


#endif
