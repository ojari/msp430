TARGET   = demo
MCU      = msp430g2553
SRCS     = main2.c config.c
#SRCS     = main.c config.c lcd.c ds1820.c nexa.c demo3.c

CFLAGS   = -mmcu=$(MCU) -g -Os -Wall -Wunused   
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -g -Os -Wl,-Map=$(TARGET).map

CC       = msp430-gcc
OBJCOPY  = msp430-objcopy
SIZE     = msp430-size
RM       = rm -f
MSPDEBUG = mspdebug

OBJS = $(SRCS:.c=.o)

all: $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.lst: %.c
	$(CC) -c $(ASFLAGS) -Wa,-anlhd $< > $@

.SILENT:
.PHONY:	clean erase prog gen
clean:
	-$(RM) $(OBJS) $(TARGET).* $(SRCS:.c=.lst)

erase:
	${MSPDEBUG} rf2500 "erase"

prog:
	${MSPDEBUG} rf2500 "prog ${TARGET}.elf"

gen:
	cd ../CodeGen; python msp430.py
