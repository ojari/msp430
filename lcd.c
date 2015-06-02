#include "hw.h"
#include "lcd.h"
#include <string.h>
#include <inttypes.h>

void lcd_output(uint8_t);

#define DELAY_1US  __asm__ __volatile__ ("nop")

void lcd_init()
{
	uint8_t i;
	
	clr_LCD_DATA1;
	clr_LCD_DATA2;
	clr_LCD_DATA3;
	clr_LCD_DATA4;
	
	delay_ms(30);         // Wait for LCD display to bootup
	delay_ms(20);

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
	lcd_clear();
	lcd_command(LCD_CLEAR_DISPLAY);
	delay_ms(2);
}

void lcd_clear(void)
{
	lcd_command(LCD_RETURN_HOME);
	delay_ms(2);
}

void lcd_command(uint8_t value)
{
	clr_LCD_RS;
	lcd_output(value>>4);
	delay_ms(1);
	lcd_output(value);
	delay_ms(1);
}

void lcd_str(const char *s)
{
	while(*s) {
		lcd_write(*s);
		s++;
	}
}

// Prints one character into display
//
void lcd_write(uint8_t value)
{
	set_LCD_RS;
	lcd_output(value>>4);
	delay_us(500);
	lcd_output(0x0F & value);
	delay_ms(3);
	//delay_ms(30);
}


void lcd_output(uint8_t value)
{
	clr_LCD_DATA1;
	clr_LCD_DATA2;
	clr_LCD_DATA3;
	clr_LCD_DATA4;

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
	delay_us(400);
}
