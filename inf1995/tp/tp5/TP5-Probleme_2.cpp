/*
 * Nom: TP5-Probleme_2.cpp
 * Copyright (C) 2016 Sebastien Chagnon et Sida (Eric) Li
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description:
 * Version: 1.0
 */

#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0;

void initialisation() {
  cli(); // Bloquer interrupts pendant l'initialisation

  DDRA = 0x00; // PORT A est en mode entre
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entre

  PORTC = 0x00; // Initialiser à off
}

void partirMinuterie(uint16_t duree) {
// minuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisee par 1024
// interruption apres la duree specifiee
TCNT1 = 0;
OCR1A = duree;
TCCR1A = 0;
TCCR1B |= ((1 << WGM12) |(1 << CS10) |(1 << CS12));
TCCR1C = 0;
TIMSK1 |= (1 << OCIE1A);

EIMSK |= _BV(INT0);
EICRA |= (1 << ISC00 | 1 << ISC01); //Trigger on rising of INT0
}

void flashRed() {
  PORTC = 0x02;
  _delay_ms(100);
  PORTC = 0x00;
}

int main()
{
  initialisation();
  _delay_ms(10000);
  flashRed();
  sei(); // Commencer interrupts après que l'initialisation s'est faite
  partirMinuterie(7813);

  do {
// attendre qu'une des deux variables soit modifiee
// par une ou l'autre des interruptions.
  } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

  cli();

  if (boutonPoussoir == 1) {
    PORTC = 0x01; //Vert
  }
  else {
    PORTC = 0x02; //Rouge
  }
  return 0;
}

ISR(TIMER1_COMPA_vect) {
  minuterieExpiree = 1;
}

ISR(INT0_vect) {
  _delay_ms(30);
  if (PIND & 0x04) {
    boutonPoussoir = 1;
  }
}
