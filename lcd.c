#include <msp430.h>
#include "lcd.h"
#include "port.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

void lcd_output(uint8_t);

#define DELAY_1US  __asm__ __volatile__ ("nop")
#define delay_us(x)  __delay_cycles(x)
#define delay_ms(x)  __delay_cycles(x*1000)

#define LCD_DATA_LINES (BIT2+BIT3+BIT4+BIT5)


void lcd_init()
{
	uint8_t i;
	
	P2OUT = 0;
	
	delay_ms(30);         // Wait for LCD display to bootup
	delay_ms(30);

	clr_LCD_RS;                       // control lines to initial position
	clr_LCD_ENABLE;
  
	i = 3;
	while (i)
		{
			lcd_output(0x03);
			delay_ms(5);      // wait min 5ms
			i--;
		}
    lcd_output(0x02);                // set to 4-bit interface
	delay_ms(1);
	lcd_command(LCD_FUNCTION);  
	delay_ms(1);
	lcd_command(LCD_DISPLAY);
	delay_ms(2);
	lcd_command(LCD_CLEAR_DISPLAY);
	delay_ms(2);
	lcd_command(LCD_RETURN_HOME);
}

void lcd_command(uint8_t value)
{
	clr_LCD_RS;
	lcd_output(value>>4);
	delay_ms(1);
	lcd_output(value);
	delay_ms(10);
}

// Prints one character into display
//
void lcd_write(uint8_t value)
{
	set_LCD_RS;
	lcd_output(value>>4);
	delay_us(500);
	lcd_output(0x0F & value);
	delay_ms(30);
	delay_ms(30);
}


void lcd_output(uint8_t value)
{
	P2OUT &= ~LCD_DATA_LINES;

	if (value & 0x01)	set_LCD_DATA1;
	if (value & 0x02)	set_LCD_DATA2;
	if (value & 0x04)	set_LCD_DATA3;
	if (value & 0x08)	set_LCD_DATA4;

	//	P2OUT = (0xC3 & P2OUT) + (0x3C & (value << 2));

	//clr_LCD_ENABLE;
	//DELAY_1US;
	set_LCD_ENABLE;
	delay_us(5);
	clr_LCD_ENABLE;
	delay_us(500);
}
