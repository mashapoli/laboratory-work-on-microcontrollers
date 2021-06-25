#include     <mega328p.h>
#include     <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>
char *buffer_line1="Microcontrollers"; //
//char *buffer_line2="Second Name 1, Second Name 2"; //
flash char char_from_arr[][9] = {
{0x32,0x30,0x32,0x5F}
};


void slova (unsigned char column,unsigned char row,unsigned char num_arr){
    unsigned char count = 0;
    lcd_gotoxy(column, row); //   
    while(char_from_arr[num_arr][count])   { 
    lcd_putchar(char_from_arr[num_arr][count]); 
    delay_ms( 50 );
    count++;
    }  
} 


void main(void)
{
// Port D initialization
PORTD=0x00;
DDRD=0x00;
 
lcd_init(40);
lcd_clear( );
lcd_gotoxy(9, 0); 
lcd_puts(buffer_line1); 
slova(26,0,0);  
lcd_gotoxy(6, 1); 
delay_ms( 20 );
lcd_putsf("Second Name 1, Second Name 2");  

    
while (1)
      {    
      }
}
