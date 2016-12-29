/*
 * Nom: TP5-Probleme_1.cpp
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
volatile uint8_t pressed = 0;

void initialisation() {
  cli(); // Bloquer interrupts pendant l'initialisation

  DDRA = 0x00; // PORT A est en mode entre
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entre

  EIMSK |= _BV(INT0);
  EICRA |= (1 << ISC00); //Trigger on any logical change of INT0

  PORTC = 0x02; // Initialiser à la lumière rouge

  sei(); // Commencer interrupts après que l'initialisation s'est faite
}

int main()
{
  initialisation();

  for (unsigned long compteur = 0; ; compteur++) {
    switch(etat) {
      case 0:
        PORTC = 0x02; // Lumière rouge
        break;

      case 1:
        PORTC = (compteur >> 8) % 8 == 0 ? 0x02 : 0x01; // Lumière ambre
	      break;

      case 2:
        PORTC = 0x01; // Lumiere verte
        break;

      case 3:
        PORTC = 0x02; // Lumiere rouge
        break;

      case 4:
        PORTC = 0x00; // Lumiere éteinte
        break;

      case 5:
        PORTC = 0x01; // Lumiere verte
        break;
    }
    compteur++;
  }

  return 0;
}

ISR(INT0_vect) {
  _delay_ms(30);
  bool changed = false;
  if (pressed == 0) {
    if (PIND & 0x04) {
      pressed = 1;
      changed = true;
    }
  }
  else {
    if (!(PIND & 0x04)) {
      pressed = 0;
      changed = true;
    }
  }
  if (changed) {
    etat = (etat + 1) % 5;
  }
  EIFR |= (1 << INTF0) ;
}
