#pragma once

#ifdef _SIMULATED_
#else
  #include <msp430g2553.h>
  //#include <inttypes.h> // for GCC
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#include "config.h"

#ifdef _SIMULATED_
  #define delay_us(x)  
  #define delay_ms(x)

  extern int reg_simulator(int module, int reg, int value);
#else
  #define delay_us(x)  __delay_cycles(x)
  #define delay_ms(x)  __delay_cycles(x*1000)
#endif