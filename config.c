#include "hw.h"
#include "config.h"

void config_port_init (void)
{
	P1DIR = BIT0 + BIT3 + BIT5 + BIT6 + BIT7;
	P2DIR = BIT0 + BIT2 + BIT3 + BIT4 + BIT5;
}

void config_port_set (uint8_t pin)
{
	switch (pin)
	{
	}
}

void config_port_clear (uint8_t pin)
{
	switch (pin)
	{
	}
}

void config_port_mode (uint8_t pin, uint8_t out)
{
	switch (pin)
	{
	}
}

uint8_t config_port_read (uint8_t pin)
{
	uint8_t ret=0;
	switch (pin)
	{
	}
	return ret;
}
