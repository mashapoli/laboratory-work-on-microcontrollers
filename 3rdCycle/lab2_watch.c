/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/12/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328p.h>

#include <stdio.h> 
// Alphanumeric LCD functions
#include <alcd.h>
#include <delay.h>

// Declare your global variables here
int sec, min, hour;
unsigned char month=1;
char lcd_buffer[33];
int date=1;
int year =2021;
int editCount = 0;
bit menu = 0;
void nextDay();

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
sec++;
TCNT1H=0;
TCNT1L=0;

}

void time(){
    if(sec>59){ 
        min++;
        sec=0;
        }
    if(min>59){ 
        hour++;
        min=0;
    }
    if(hour>23){
        nextDay();
        hour=0; 
        min=0;
    }
}

void timeOut (void)
{      
  time();
  lcd_gotoxy(0,1); 
  lcd_puts("Time ");
  lcd_putchar(hour/10+0x30);
  lcd_putchar(hour%10+0x30);
  lcd_putchar(':'); 
  lcd_putchar(min/10+0x30);
  lcd_putchar(min%10+0x30);       
  lcd_putchar(':');
  lcd_putchar(sec/10+0x30);
  lcd_putchar(sec%10+0x30); 
}


void monthOut (void){
 switch (month) {
    case 1:
    lcd_puts("JAN");
    break;
    case 2:
    lcd_puts("FEB");
    break;
    case 3:
    lcd_puts("MAR");
    break;
    case 4:
    lcd_puts("APR");
    break;
    case 5:
    lcd_puts("MAY");
    break;
    case 6:
    lcd_puts("JUN");
    break;
    case 7:
    lcd_puts("JUL");
    break;
    case 8:
    lcd_puts("AUG");
    break;
    case 9:
    lcd_puts("SEP");
    break;
    case 10:
    lcd_puts("OCT");
    break;
    case 11:
    lcd_puts("NOV");
    break;
    case 12:
    lcd_puts("DEC");
    break;
    }; 
}


void dateout (void)
{   
  sprintf(lcd_buffer,"%4d", year);   
  lcd_gotoxy(0,0);
  lcd_puts("Date ");
  lcd_putchar(date/10+0x30);
  lcd_putchar(date%10+0x30);
  lcd_putchar(' '); 
  monthOut();  
  lcd_putchar(' ');
  lcd_puts(lcd_buffer);                      
}


int  maxdDayPerMonth(void){
int i = (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
switch (month) {
 case 1:case 3:case 5:case 7:case 8:case 10:case 12:
 return 31;
 case 4:case 6:case 9:case 11:
  return 30;
 case 2:
 return 28 + i; 
}
}

void nextDay (void){
    date++;
    if (date > maxdDayPerMonth()) {
        date = 1;
        month++;
    }
    if (month > 12) {
        month = 1;
        date = 1;
        year++;
     } 
}


void menuView (void){
while (menu){
switch (editCount){
case 0:
 if (PINC.1 == 0) {
    hour++;
    if (hour > 23) {
        hour = 0;
    } 
 }
 if (PINC.2 == 0) {
    hour--;
    if (hour <= -1) {
        hour = 23;
    } 
 }
//lcd_gotoxy(5,1);
//lcd_putchar(hour/10+0x30);
//lcd_putchar(hour%10+0x30);
delay_ms(200);
 if (PINC.0 == 0) {
    editCount++;
}
break;

case 1:
 if (PINC.1 == 0) {
    min++;
    if (min > 59) {
        min = 0;
    } 
 }
 if (PINC.2 == 0) {
    min--;
    if (min <= -1) {
        min = 59;
    } 
 }
//lcd_gotoxy(8,1);
//lcd_putchar(min/10+0x30);
//lcd_putchar(min%10+0x30);
delay_ms(200);
 if (PINC.0 == 0) {
    editCount++;
}
break;


case 2:
 if (PINC.1 == 0) { 
    year++;
    if (year > 2050) {
        year = 2021;
    } 
 }
 if (PINC.2 == 0) {
    year--;
    if (year < 2011) {
        year = 2021;
    } 
 } 
//sprintf(lcd_buffer,"%4d", year); 
//lcd_gotoxy(12,0);
//lcd_puts(lcd_buffer);  
delay_ms(200);
 if (PINC.0 == 0) {
    editCount++;
}
break;

case 3:
 if (PINC.1 == 0) { 
    month++;
    if (month > 12) {
        month = 1;
    } 
 }
 if (PINC.2 == 0) {
    month--;
    if (month <= 0) {
        month = 12;
    } 
 }
//lcd_gotoxy(8,0);
//monthOut(); 
delay_ms(200);
 if (PINC.0 == 0) {
    editCount++;
}
break;

case 4:
 if (PINC.1 == 0) {
    date++;
    if (date > maxdDayPerMonth()) {
        date = 1;
    } 
 }
 if (PINC.2 == 0) {
    date--;
    if (date <= 0) {
        date = maxdDayPerMonth();
    } 
 }
//lcd_gotoxy(5,0);
//lcd_putchar(date/10+0x30);
//lcd_putchar(date%10+0x30);
delay_ms(200);
 if (PINC.0 == 0) {
    editCount++;
}
break;

case 5:
        lcd_clear(); 
        lcd_gotoxy(0,0);
        lcd_puts("exit setup mode");
        delay_ms(1000);

    menu = 0;
    editCount = 0; 
    
    break; 
};
       timeOut(); 
      dateout();
}
}


void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (1<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: CTC top=OCR0A
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 31.250 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 1 s
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x1E;
OCR1AL=0x85;
OCR1BH=0x00;
OCR1BL=0x00;


// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (1<<OCIE1A) | (1<<TOIE1);

lcd_init(16);
// Global enable interrupts
#asm("sei")
while (1)
      {
      // Place your code here 
      //time();
      
      if (PINC.0 == 0) {
        menu = 1;  
        lcd_clear(); 
        lcd_gotoxy(3,0);
        lcd_puts("setup mode");
        delay_ms(1000); 
      }  
      
      menuView();
      timeOut(); 
      dateout();
      }  
     
}
