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
  PORTC = 0x02;
}

void lightGreen() {
  PORTC = 0x01;
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

  int cycleDuration = 250;

  while (1) {
    // for (int offDuration = 0; offDuration < cycleDuration; offDuration++) {
    //   for (int onCycle = 0; onCycle < cycleDuration - offDuration; onCycle++) {
    //     PORTC = 0x02;
    //     _delay_ms(0.0009);
    //   }
    //   for (int offCycle = 0; offCycle < offDuration; offCycle++) {
    //     PORTC = 0x00;
    //     _delay_ms(0.0009);
    //   }
    // }

    for (int offDuration = 0; offDuration < cycleDuration; offDuration++) {
      for (int offCycle = 0; offCycle < offDuration; offCycle++) {
        lightGreen();
        _delay_ms(0.01);
      }
      for (int onCycle = 0; onCycle < cycleDuration - offDuration; onCycle++) {
        lightOff();
        _delay_ms(0.01);
      }
    }
    for (int offDuration = 0; offDuration < cycleDuration; offDuration++) {
      for (int offCycle = 0; offCycle < offDuration; offCycle++) {
        lightOff();
        _delay_ms(0.01);
      }
      for (int onCycle = 0; onCycle < cycleDuration - offDuration; onCycle++) {
        lightGreen();
        _delay_ms(0.01);
      }
      lightOff();
    }
    for (int offDuration = 0; offDuration < cycleDuration; offDuration++) {
      for (int offCycle = 0; offCycle < offDuration; offCycle++) {
        lightRed();
        _delay_ms(0.01);
      }
      for (int onCycle = 0; onCycle < cycleDuration - offDuration; onCycle++) {
        lightOff();
        _delay_ms(0.01);
      }
    }
  }

  return 0;
}
