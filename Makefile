TARGET   = demo
MCU      = msp430g2553
#SRCS     = main.c demo1.c config.c
#SRCS     = main.c demo2.c config.c lcd.c
SRCS     = main.c demo3.c config.c nexa.c ds1820.c uart.c
#SRCS     = main.c demo3.c config.c lcd.c nexa.c ds1820.c uart.c
#SRCS     = main.c config.c lcd.c ds1820.c nexa.c demo3.c

CFLAGS   = -mmcu=$(MCU) -g -Os -Wall -Wunused -Iinc -DGCC
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -g -Os -Wl,-Map=$(TARGET).map

CC       = msp430-elf-gcc
OBJCOPY  = msp430-elf-objcopy
SIZE     = msp430-elf-size
#RM       = rm -f
RM       = del
MSPDEBUG = mspdebug

OBJS = $(SRCS:.c=.o)

all: $(TARGET).elf $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

#%.hex: %.elf
.elf.hex:
	$(OBJCOPY) -O ihex $< $@

#%.o: %.c
.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

%.lst: %.c
	$(CC) -c $(ASFLAGS) -Wa,-anlhd $< > $@

.SILENT:
.PHONY:	clean erase prog gen
clean:
	-$(RM) $(OBJS) $(TARGET).* $(SRCS:.c=.lst)

erase:
	$(MSPDEBUG) rf2500 "erase"

prog:
	$(MSPDEBUG) rf2500 "prog $(TARGET).elf"

gen:
	cd ../CodeGen; python msp430.py
