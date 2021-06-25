/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : lcd
Version : 
Date    : 4/15/2021
Author  : Bystrova Maria
Company : 
Comments: 
The program implements the display of two-line text on the lcd screen in 8-bit mode


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
data Stack size         : 512
*******************************************************/

#include <mega328p.h>

#include <delay.h>

//lcd Functions declaration
void lcd_init(void);
void lcd_write_cmd(unsigned char cmd);
void lcd_write_data(unsigned char data);

void lcd_display_string(char row, char column, flash unsigned char * string);
void lcd_cursor(char row, char column);

#define LCD_EN PORTC |= 1 << 2
#define LCD_DIS PORTC &= ~(1 << 2)
#define LCD_RS_DATA PORTC |= 1 << 0
#define LCD_RS_CMD PORTC &= ~(1 << 0)

void main(void) {

  // RS - PORTC Bit 0
  // EN - PORTC Bit 2
  // D0 - PORTB Bit 0
  // D1 - PORTB Bit 1
  // D2 - PORTB Bit 2
  // D3 - PORTB Bit 3
  // D4 - PORTB Bit 4
  // D5 - PORTB Bit 5
  // D6 - PORTB Bit 6
  // D7 - PORTB Bit 7

  // Input/Output Ports initialization
  // Port B initialization
  // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
  DDRB = (1 << DDB7) | (1 << DDB6) | (1 << DDB5) | (1 << DDB4) | (1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
  PORTB = (0 << PORTB7) | (0 << PORTB6) | (0 << PORTB5) | (0 << PORTB4) | (0 << PORTB3) | (0 << PORTB2) | (0 << PORTB1) | (0 << PORTB0);

  // Port C initialization
  // Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=In Bit0=Out 
  DDRC = (0 << DDC6) | (0 << DDC5) | (0 << DDC4) | (0 << DDC3) | (1 << DDC2) | (0 << DDC1) | (1 << DDC0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
  PORTC = (0 << PORTC6) | (0 << PORTC5) | (0 << PORTC4) | (0 << PORTC3) | (0 << PORTC2) | (0 << PORTC1) | (0 << PORTC0);

  lcd_init();
  lcd_display_string(1, 9, "Microcontrollers 202_");
  lcd_write_cmd(0xc0); //moving lcd cursor to second row  
  lcd_display_string(2, 6, "Second Name 1, Second Name 2");

  while (1) {}
}

//Initialize the lcd driver
void lcd_init(void) {
  delay_ms(30); // wait 30ms
  lcd_write_cmd(0x38); // 8-bit, 2 lines
  lcd_write_cmd(0x0c); // display ON, cursor OFF
}

//Write a command instruction to the lcd 
void lcd_write_cmd(unsigned char cmd) {

  LCD_RS_CMD; // Set lcd in cmd mode
  PORTB = cmd; // Load data to port
  LCD_EN; // Write data to lcd
  delay_ms(2);
  LCD_DIS; // Disable lcd   
  delay_ms(1); // wait for 1ms
}

//Write one byte of data to the lcd  
void lcd_write_data(unsigned char data) {
  LCD_RS_DATA; // Set lcd in data mode
  PORTB = data; // Load data to port
  LCD_EN; // Write data to lcd
  delay_ms(2);
  LCD_DIS; // Disable lcd
  delay_ms(1); // wait for 1ms
}

//Display a string at the specified row and column
void lcd_display_string(char row, char column, flash unsigned char * string) {
  lcd_cursor(row, column);
  while ( * string)
    lcd_write_data( * string++);
}

//Position the lcd cursor at row and column
void lcd_cursor(char row, char column) {
  switch (row) {
  case 1:
    lcd_write_cmd(0x80 + column - 1);
    break;
  case 2:
    lcd_write_cmd(0xc0 + column - 1);
    break;
  default:
    break;
  }
}
