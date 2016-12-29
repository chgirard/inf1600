/*
 * Nom: TP7-Probleme_1.cpp
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

volatile uint8_t etat = 0;
volatile uint8_t initialized = 0;
volatile uint8_t buttonVCC = 1;
volatile uint8_t counter = 0;

void initProgram() {
  DDRA = 0x00; // PORT A est en mode entre
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entre
}

void initialisation() {
  cli(); // Bloquer interrupts pendant l'initialisation

  EIMSK |= _BV(INT0);
  EICRA |= (1 << ISC00); //Trigger on any logical change of INT0

  sei(); // Commencer interrupts après que l'initialisation s'est faite
}

void initCounter() {
  TCNT1 = 0;
  OCR1A = 12500; // Avec prescaler 64, CTC à chaque 0.1 secondes
  TCCR1A = 0;
  TCCR1B |= ((1 << WGM12) |(1 << CS11) |(1 << CS10)); // Prescaler 64
  TCCR1C = 0;
  TIMSK1 |= (1 << OCIE1A); // Clear timer on compare à 12500 -> 0.1 secondes
}

void redBlink() {
  for (uint8_t i = 0; i < counter/2; i++) {
    PORTC = 0x02; //red
    _delay_ms(250);
    PORTC = 0x00; //off
    _delay_ms(250);
  }
}

int main()
{
  initProgram();

  for (;;) {
    switch(etat) {
      case 0:
        if (!initialized) {
          initialisation();
          initialized = 1;
        }
        break;

      case 1:
        if (counter >= 120) {
          cli();
          etat = 2;
        }
	      break;

      case 2:
        {
          PORTC = 0x01; //Vert
          _delay_ms(500);
          PORTC = 0x00; //none
          _delay_ms(2000);
          redBlink();
          PORTC = 0x01; //Vert
          _delay_ms(1000);
          etat = 0;
          initialized = 0;
          buttonVCC = 1;
          counter = 0;
        }
        break;
      }
  }
  return 0;
}

ISR(INT0_vect){
  _delay_ms(30);
  if (buttonVCC) {
    if (!(PIND & 0x04)) {
      buttonVCC = 0;
      if (etat == 0) {
        etat = 1;
        initCounter();
      }
    }
  }
  else {
    if (PIND & 0x04) {
      buttonVCC = 1;
      if (etat == 1) {
        etat = 2;
      }
    }
  }
  EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect) {
  counter++;
}
