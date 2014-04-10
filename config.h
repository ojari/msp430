#ifndef _CONFIG_H
#define _CONFIG_H

extern void config_port_init ();
#define set_LED_GREEN P1OUT |= BIT0
#define clr_LED_GREEN P1OUT &= ~BIT0
#define toggle_LED_GREEN P1OUT ^= BIT0
#define set_LCD_RS P1OUT |= BIT5
#define clr_LCD_RS P1OUT &= ~BIT5
#define toggle_LCD_RS P1OUT ^= BIT5
#define set_LED_RED P1OUT |= BIT6
#define clr_LED_RED P1OUT &= ~BIT6
#define toggle_LED_RED P1OUT ^= BIT6
#define set_LCD_ENABLE P1OUT |= BIT7
#define clr_LCD_ENABLE P1OUT &= ~BIT7
#define toggle_LCD_ENABLE P1OUT ^= BIT7
#define set_LCD_DATA1 P2OUT |= BIT2
#define clr_LCD_DATA1 P2OUT &= ~BIT2
#define toggle_LCD_DATA1 P2OUT ^= BIT2
#define set_LCD_DATA2 P2OUT |= BIT3
#define clr_LCD_DATA2 P2OUT &= ~BIT3
#define toggle_LCD_DATA2 P2OUT ^= BIT3
#define set_LCD_DATA3 P2OUT |= BIT4
#define clr_LCD_DATA3 P2OUT &= ~BIT4
#define toggle_LCD_DATA3 P2OUT ^= BIT4
#define set_LCD_DATA4 P2OUT |= BIT5
#define clr_LCD_DATA4 P2OUT &= ~BIT5
#define toggle_LCD_DATA4 P2OUT ^= BIT5

#endif
