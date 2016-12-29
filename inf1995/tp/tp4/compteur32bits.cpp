/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void lightRed() {
  PORTC = 0xEE;
}

void lightGreen() {
  PORTC = 0xEE;
}

void lightOff() {
  PORTC = 0x00;
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode entrée

  while (1) {
    for (int i = 0; i < 120; i++) {
      PORTC = 0x0E;
      _delay_ms(4.166);
      PORTC = 0x00;
      _delay_ms(12.5);
    }

    _delay_ms(2000);

    for (int i = 0; i < 120; i++) {
      PORTC = 0x0E;
      _delay_ms(8.333);
      PORTC = 0x00;
      _delay_ms(8.333);
    }

    _delay_ms(2000);

    for (int i = 0; i < 120; i++) {
      PORTC = 0x0E;
      _delay_ms(12.5);
      PORTC = 0x00;
      _delay_ms(4.166);
    }

    _delay_ms(2000);

    PORTC = 0x0E;
    _delay_ms(2000);

    PORTC = 0x00;
    _delay_ms(5000);
  }

  return 0;
}
