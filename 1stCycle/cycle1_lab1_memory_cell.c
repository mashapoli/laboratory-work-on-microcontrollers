/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Demo Project
Version : 1
Date    : 5/20/2021
Author  : Maria Bystrova
Company : 
Comments: 
Writing a word to a specific memory cell


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega328p.h>

// Declare your global variables here

void main(void)
{
  // Declare your local variables here
  const char char_const[] = "example";
  unsigned char *data = (unsigned char*) 0x0100;
  char i;

  for(i=0;i<=6;i++) {
    *data = char_const[i];
    data++;
  }

  while (1) {
    // Place your code here
  }
}
