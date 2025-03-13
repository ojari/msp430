TARGET   = demo
SRCS     = main.c ../demo3.c ../ds1820.c ../nrf24.c sim_spi.c sim_config.c sim_uart.c

CFLAGS   = -g -Os -Wall -Wunused -I.. -D_SIMULATED_   
LDFLAGS  = -g -Os -Wl,-Map=$(TARGET).map

CC       = gcc
RM       = rm -f

OBJS = $(SRCS:.c=.o2)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o2: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.SILENT:
.PHONY:	clean
clean:
	-$(RM) $(OBJS) $(TARGET).*
