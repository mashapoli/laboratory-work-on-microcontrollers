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
The program displays the number of the pressed key on the LCD module screen 


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328p.h>
#include <delay.h>
#include <alcd.h>

void main(void) {
  // Declare your local variables here
  unsigned char upper_tire, button_code , button_number, i;
  unsigned char *data = (unsigned char*)0x0100;

  // Port D initialization
  // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
  DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
 

  // Input/Output Ports initialization
  // Port B initialization
  // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
  DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTB=(1<<PORTB7) | (1<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

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
  // Characters/line: 16
  lcd_init(16);

  lcd_clear( );
  lcd_gotoxy(0, 0);
  lcd_puts((char *)"Number button : ");

  while(1) {
    upper_tire = 0xff;

    for(i=0; i<4; i++) {
      delay_ms(2);
      upper_tire = PINB | 0x0f;

      if (upper_tire != 0xff) {

        delay_ms(20); 
        upper_tire = PINB | 0x0f;

        if(upper_tire == 0xff) {
          continue;
        }

        button_code  = (upper_tire & 0xf0) | (0x0f & ~(0x01 << i));

        while (upper_tire != 0xff) {
          upper_tire = PINB | 0x0f;
        }

        delay_ms(20);

        switch (button_code) {
          case (0xee): button_number  = '0';
            break;
          case (0xed): button_number  = '1';
            break;
          case (0xeb): button_number  = '2';
            break;
          case (0xe7): button_number  = '3';
            break;
          case (0xde): button_number  = '4';
            break;
          case (0xdd): button_number  = '5';
            break;
          case (0xdb): button_number  = '6';
            break;
          case (0xd7): button_number  = '7';
            break;
          case (0xbe): button_number  = '8';
            break;
          case (0xbd): button_number  = '9';
            break;
          case (0xbb): button_number  = 'A';
            break;
          case (0xb7): button_number  = 'B';
            break;
          case (0x7e): button_number  = 'C';
            break;
          case (0x7d): button_number  = 'D';
            break;
          case (0x7b): button_number  = 'E';
            break;
          case (0x77): button_number  = 'F';
            break;
          default: button_number  = 'X';
        }
        lcd_gotoxy(0, 1);
        lcd_putchar(keyPressed);
      }
    }
  }
}