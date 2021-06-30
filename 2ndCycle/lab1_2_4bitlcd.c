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

#include     <mega328p.h>
#include     <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>

const char char_from_arr[][9] = {
  {0x32,0x30,0x32,0x5F}
};

void words(unsigned char column,unsigned char row,unsigned char num_arr){
    unsigned char count = 0;
    lcd_gotoxy(column, row); //   
    while(char_from_arr[num_arr][count]) {
      lcd_putchar(char_from_arr[num_arr][count]);
      delay_ms(50);
      count++;
    }  
} 

void main(void)
{
  // Port D initialization
  // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
  DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
 
  // Alphanumeric LCD initialization
  // Connections are specified in the
  // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
  // RS - PORTB Bit 0
  // RD - PORTB Bit 1
  // EN - PORTB Bit 2
  // D4 - PORTB Bit 4
  // D5 - PORTB Bit 5
  // D6 - PORTB Bit 6
  // D7 - PORTB Bit 7
  // Characters/line: 40
  lcd_init(40);

  lcd_clear( );
  lcd_gotoxy(9, 0);
  lcd_puts((char *) "Microcontrollers");
  words(26,0,0);
  lcd_gotoxy(6, 1);
  delay_ms( 20 );
  lcd_putsf("Second Name 1, Second Name 2");

  while (1) { }
}
