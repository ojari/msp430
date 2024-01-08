TARGET   = demo
MCU      = msp430g2553
OBJDIR   = bin

MSP_FILES = $(OBJDIR)\config.o $(OBJDIR)\uart.o $(OBJDIR)\spi.o
DRV_FILES = $(OBJDIR)\ds1820.o $(OBJDIR)\nrf24.o

OBJS     = $(OBJDIR)\main.o $(OBJDIR)\demo3.o $(DRV_FILES) $(MSP_FILES)

CFLAGS   = -mmcu=$(MCU) -g -Os -Wall -Wunused -Iinc -DGCC
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) -g -Os -Wl,-Map=$(TARGET).map

CC       = msp430-elf-gcc
OBJCOPY  = msp430-elf-objcopy
SIZE     = msp430-elf-size
#RM       = rm -f
RM       = del
MSPDEBUG = mspdebug

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
.c{$(OBJDIR)}.o:
	$(CC) -c $(CFLAGS) -o $@ $<

%.lst: %.c
	$(CC) -c $(ASFLAGS) -Wa,-anlhd $< > $@

.SILENT:
.PHONY:	clean erase prog gen
clean:
# echo $(OBJS)
	$(RM) $(OBJS) $(TARGET).*

erase:
	$(MSPDEBUG) rf2500 "erase"

flash:
	$(MSPDEBUG) rf2500 "prog $(TARGET).elf"

gen:
	cd ../CodeGen; python msp430.py
