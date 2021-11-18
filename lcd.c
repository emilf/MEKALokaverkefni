// LCD
#include "common.h"
//LCD CONFIG BEGINS
#define	LCD_RS RB4
#define LCD_EN RB5
#define LCD_DATA	PORTB
#define _LCD_CURSOR_OFF 0x0C
#define _LCD_CURSOR_ON 0x0F
#define _LCD_CURSOR_ON_SOLID 0x0E
#define _LCD_CLEAR 0x01
#define _LCD_BLANK 0x08
#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

// LCD CONFIG END
/* write a byte to the LCD in 4 bit mode */
void lcd_write(unsigned char c) {
	__delay_us(40);
	LCD_DATA = (LCD_DATA & 0xF0) | ( ( c >> 4 ) & 0x0F);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = (LCD_DATA & 0xF0) | ( c & 0x0F );
	LCD_STROBE();
	__delay_us(200);
}
 /* 	Clear and home the LCD */
void lcd_clear(void) {
	LCD_RS = 0;
	lcd_write(0x01);
	__delay_ms(2);
}
/* write a string of chars to the LCD */
void lcd_out( unsigned char line, unsigned char character, const char * s) {
	lcd_goto( ( 0x40 * ( line - 1 ) ) + ( character - 1 ) );
	LCD_RS = 1;	// write characters
	while(*s) lcd_write(*s++);
}
/* write one character to the LCD */
void lcd_chr_cp(char c) {
	LCD_RS = 1;	// write characters
	lcd_write( c );
}
void lcd_chr( unsigned char line, unsigned char character, char c ) {
	lcd_goto( ( 0x40 * ( line - 1 ) ) + ( character - 1 ) );
	LCD_RS = 1;	// write characters
	lcd_write( c );
}
void lcd_cmd( unsigned char c ) {
	LCD_RS = 0;
	lcd_write( c );
}
/* Go to the specified position */
void lcd_goto(unsigned char pos) {
	LCD_RS = 0;
	lcd_write(0x80+pos);
}
/* initialise the LCD - put into 4 bit mode */
void lcd_init() {
	TRISB = 0xC0;
	ANSEL = 0x00;
	ANSELH = 0x00;
	LCD_RS = 0;
	LCD_EN = 0;
	__delay_ms(20);	// wait 15mSec after power applied,
	LCD_DATA = (LCD_DATA & 0xF0) | ( 0x03 & 0x0F );
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = (LCD_DATA & 0xF0) | ( 0x02 & 0x0F );
	LCD_STROBE();
	__delay_ms(5);
	lcd_write(0x28); // Set interface length
	lcd_clear();	// Clear screen
	lcd_write(0x06); // Set entry Mode
	lcd_write(0x0C); // Turn on screen without cursor
}
