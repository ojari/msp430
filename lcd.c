#include "hw.h"
#include "lcd.h"
#include <string.h>

void lcd_output(uint8_t);

#define DELAY_1US  __asm__ __volatile__ ("nop")
#define LIST_END 255


uint8_t dataPins[] = {
	PIN_LCD_DATA1,
	PIN_LCD_DATA2,
	PIN_LCD_DATA3,
	PIN_LCD_DATA4,
	LIST_END
};

void lcd_init()
{
	uint8_t i;

	i = 0;
	while (dataPins[i] != LIST_END) {	
		digitalWrite(dataPins[i], LOW);
		i++;
	}

	delay_ms(30);         // Wait for LCD display to bootup
	delay_ms(20);

	digitalWrite(PIN_LCD_RS, LOW);     // control lines to initial position
	digitalWrite(PIN_LCD_ENABLE, LOW);
  
	i = 3;
	while (i) {
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
	digitalWrite(PIN_LCD_RS, LOW);

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
	digitalWrite(PIN_LCD_RS, HIGH);

	lcd_output(value>>4);
	delay_us(500);
	lcd_output(0x0F & value);
	delay_ms(3);
	//delay_ms(30);
}


void lcd_output(uint8_t value)
{
	uint8_t i = 0;
	while (dataPins[i] != LIST_END) {
		if (value & (1 << i)) {
			digitalWrite(dataPins[i], HIGH);
		}
		else {
			digitalWrite(dataPins[i], LOW);
		}
		i++;
	}

	//clr_LCD_ENABLE;
	//DELAY_1US;
	digitalWrite(PIN_LCD_ENABLE, HIGH);
	delay_us(5);
	digitalWrite(PIN_LCD_ENABLE, LOW);
	delay_us(400);
}
