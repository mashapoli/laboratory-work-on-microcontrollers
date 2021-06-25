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

#define KB_PORT_OUT 			PORTB
#define KB_PORT_IN			PINB

char *buffer_line1="Number button : ";

void main(void)
{
unsigned char upperNibble, keyCode, keyPressed, i;

// Port D initialization
PORTD=0x00;
DDRD=0x00;

// Port B initialization
DDRB  = 0x0f;        
PORTB = 0xff;
 
lcd_init(16);
lcd_clear( );
lcd_gotoxy(0, 0); 
lcd_puts(buffer_line1);         

while (1)
      {
      
       upperNibble = 0xff;
        
      for(i=0; i<4; i++)
        {
         delay_ms(1);
         KB_PORT_OUT = ~(0x01 << i);
         delay_ms(1);                           //delay for port o/p settling
         upperNibble = KB_PORT_IN | 0x0f;
         
         if (upperNibble != 0xff)
         {
           delay_ms(20);                    //key debouncing delay
           upperNibble = KB_PORT_IN | 0x0f;
           if(upperNibble == 0xff) goto OUT;
           
           keyCode = (upperNibble & 0xf0) | (0x0f & ~(0x01 << i));
           
           while (upperNibble != 0xff)
             upperNibble = KB_PORT_IN | 0x0f;
           
           delay_ms(20);                  //key debouncing delay
           
           switch (keyCode)               //generating key characetr to display on LCD
           {
           case (0xee): keyPressed = '0'; 
                          break;
            case (0xed): keyPressed = '1';
                          break;
            case (0xeb): keyPressed = '2'; 
                            break;
            case (0xe7): keyPressed = '3'; 
                          break;
            case (0xde): keyPressed = '4'; 
                          break;
            case (0xdd): keyPressed = '5'; 
                          break;
            case (0xdb): keyPressed = '6'; 
                          break;
            case (0xd7): keyPressed = '7'; 
                          break;
            case (0xbe): keyPressed = '8'; 
				 		 break;
			case (0xbd): keyPressed = '9'; 
				 		 break;
			case (0xbb): keyPressed = 'A'; 
				 		 break;
			case (0xb7): keyPressed = 'B'; 
				 		 break;
			case (0x7e): keyPressed = 'C'; 
				 		 break;
			case (0x7d): keyPressed = 'D'; 
				 		 break;
			case (0x7b): keyPressed = 'E'; 
				 		 break;
			case (0x77): keyPressed = 'F'; 
				 		 break;
			default	   : keyPressed = 'X';
			}//end of switch
			lcd_clear( );    
            lcd_gotoxy(0, 0); 
            lcd_puts(buffer_line1);  
            lcd_gotoxy(0, 1);
			lcd_putchar(keyPressed);  	
			
		   OUT:;
		  }//end of if
		}//end of for
      }
}
