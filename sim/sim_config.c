#include "hw.h"
#include <stdio.h>
#include "config.h"

//#define VERBOSE

void config_port_init (void)
{
}

void digitalWrite(uint16_t pin, uint8_t mode)
{
    if (pin == P2_0 || pin == P2_1) // do not show DS1820
        return;
    if (pin == P1_0) {
        printf("RED LED: %d\n", mode);
        return;
    }

#ifdef VERBOSE
    printf("digitalWrite: %04x %d\n", pin, mode);
#endif
}

void pinMode(uint16_t pin, uint8_t out)
{
#ifdef VERBOSE
    printf("pinMode: %04x %d\n", pin, out);
#endif
}

uint8_t digitalRead(uint16_t pin)
{
#ifdef VERBOSE
    printf("digitalRead: %04x\n", pin);
#endif
    return 0;
}
