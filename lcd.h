#ifndef _LCD_H
#define _LCD_H

//#include <msp430.h>
#include <stdlib.h>

// HD44780 commands. Command parameters are hard coded into commands.
//
// see https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
//
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME   0x02
#define LCD_ENTRY_MODE    0x04 | 0x02   // Increment cursor
#define LCD_DISPLAY       0x08 | 0x04   // Display on
#define LCD_FUNCTION      0x10 | 0x08   // 2-line display
#define LCD_POSITION      0x80

// arguments to LCD_POSITION command.  
// Usage: lcd_command(LCD_POSITION | LCD_ROW1 | 10);  // row=1 col=10
//
#define LCD_ROW_1 0x00
#define LCD_ROW_2 0x40

// Interface to this module
//
extern void lcd_init(void);
extern void lcd_clear(void);
extern void lcd_str(const char *s);
extern void lcd_write(uint8_t ch);
extern void lcd_command(uint8_t cmd);

#endif
