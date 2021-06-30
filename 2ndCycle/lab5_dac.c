/*******************************************************
This program was created by the CodeWizardAVR V3.42 
Automatic Program Generator
© Copyright 1998-2020 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
Version : 
Date    : 15.05.2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega328
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328.h>
#include <delay.h>
// SPI functions
#include <spi.h>

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))

void sent_data (unsigned char data1, unsigned char data2) {

  PORTB.2=0;
  SPDR=data1; //send first byte
  while(!(SPSR & (1<<SPIF)));
  SPDR=data2; //send second byte
  while(!(SPSR & (1<<SPIF)));
}

// Declare your global variables here

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
  // Place your code here
  PORTC.1=0;
}

// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input) {

  ADMUX=adc_input | ADC_VREF_TYPE;
  // Delay needed for the stabilization of the ADC input voltage
  delay_us(10);
  // Start the AD conversion
  ADCSRA|=(1<<ADSC);
  // Wait for the AD conversion to complete
  while ((ADCSRA & (1<<ADIF))==0);
  ADCSRA|=(1<<ADIF);
  return ADCH;
}

void main(void)
{
  // Declare your local variables here
  unsigned char adac_h;
  unsigned char adac_l;

  // Crystal Oscillator division factor: 1
  #pragma optsize-
  CLKPR=(1<<CLKPCE);
  CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
  #ifdef _OPTIMIZE_SIZE_
  #pragma optsize+
  #endif

  // Input/Output Ports initialization
  // Port B initialization
  // Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=In Bit0=In
  DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (0<<DDB1) | (0<<DDB0);
  // State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=T Bit0=T
  PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

  // Port C initialization
  // Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=In
  DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (1<<DDC1) | (0<<DDC0);
  // State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=T
  PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

  // Port D initialization
  // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
  DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
  // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
  PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

  // ADC initialization
  // ADC Clock frequency: 250,000 kHz
  // ADC Voltage Reference: AREF pin
  // ADC Auto Trigger Source: ADC Stopped
  // Only the 8 most significant bits of
  // the AD conversion result are used
  // Digital input buffers on ADC0: On, ADC1: Off, ADC2: Off, ADC3: Off
  // ADC4: Off, ADC5: Off
  DIDR0=(1<<ADC5D) | (1<<ADC4D) | (1<<ADC3D) | (1<<ADC2D) | (1<<ADC1D) | (0<<ADC0D);
  ADMUX=ADC_VREF_TYPE;
  ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
  ADCSRB=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

  // SPI initialization
  // SPI Type: Master
  // SPI Clock Rate: 2000,000 kHz
  // SPI Clock Phase: Cycle Start
  // SPI Clock Polarity: Low
  // SPI Data Order: MSB First
  SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
  SPSR=(0<<SPI2X);

  // Globally enable interrupts
  #asm("sei")

  while (1) {
    // Place your code here
    PORTC.1=1;
    adac_h=0b00110000; 
    adac_l=read_adc(0);

    PORTB.2=1;
    sent_data(adac_h,adac_l);
    delay_us(1);
  }
}
