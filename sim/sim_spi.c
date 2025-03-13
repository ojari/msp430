#include "../spi.h"
#include <stdio.h>

void spi_init()
{  
}

uint8_t spi_transmit(uint8_t data)
{
    printf("SPI: %02x\n", data);

    return 0x00;
}
