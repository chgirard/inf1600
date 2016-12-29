
#define F_CPU 8000000L

#include <util/delay.h>
#include <util/delay_basic.h>

#include "Librairie.h"
#include "Roue.h"

void debounce() {
  _delay_ms(10);
}

bool isButtonPressed() {
  if ( !(PIND & 0x04) )
    return false;

  debounce();
  return (PIND & 0x04) ? true : false;
}

bool isButtonReleased() {
  return (PIND & 0x04) ? false : true;
}

void setLight(lib::CouleurDell couleur) {

  if (couleur & 0x01) {
    PORTC |= (0x01);
  } else {
    PORTC &= ~(0x01);
  }

  if (couleur & 0x02) {
    PORTC |= (0x01 << 1);
  } else {
    PORTC &= ~(0x01 << 1);
  }
}

void initialisation(uint8_t portA, uint8_t portB, uint8_t portC, uint8_t portD) {
  DDRA = portA;
  DDRB = portB;
  DDRC = portC;
  DDRD = portD;

  EIMSK |= _BV(INT0);
  EICRA |= (1 << ISC00); //Trigger on any logical change of INT0
}

void ajusterPWM(uint8_t ratio, lib::Direction direction) {
  ajusterPWM(ratio, ratio, direction);
}

void ajusterPWM(uint8_t ratioRoueGauche, uint8_t ratioRoueDroite, lib::Direction direction) {
  ajusterPWM(ratioRoueGauche, ratioRoueDroite, direction, direction);
}

void ajusterPWM(uint8_t ratioRoueGauche, uint8_t ratioRoueDroite, lib::Direction directionRoueGauche,
  lib::Direction directionRoueDroite) {
    TCCR2A = 0;
    TCCR2B = 0;
  // mise a un des sorties OC1A et OC1B sur comparaison
  // reussie en mode PWM 8 bits, phase correcte
  // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
  // page 130 de la description technique du ATmega324PA)
  TCCR2A |= (1 << WGM20 | 1 << COM2A1 | 1 << COM2B1) ;
    // division d'horloge par 8 - implique une frequence de PWM fixe
  TCCR2B |= (1 << CS11);

  OCR2A = ratioRoueDroite ;
  OCR2B = ratioRoueGauche ;

  ajusterDirection(lib::Roue_Droite, directionRoueDroite);
  ajusterDirection(lib::Roue_Gauche, directionRoueGauche);
}

void ajusterDirection(lib::Roue roue, lib::Direction direction) {
  switch (direction) {
    case lib::Direction_Avancer:
      PORTD |= (1 << roue);
    break;
    case lib::Direction_Reculer:
      PORTD &= ~(1 << roue);
    break;;
  }
}

void clairInterruptions() {
  EIFR |= (1 << INTF0);
}

void initialiserMinuterie(uint16_t ms) {
  if (F_CPU <= 65536000L/ms)
  {
    initialiserCompteur(((uint32_t)ms)*8000, lib::Prescaler_1);
  }
  else if (F_CPU <= 8*(65536000L/ms))
  {
    initialiserCompteur((((uint32_t)ms)*8000)/8, lib::Prescaler_8);
  }
  else if (F_CPU <= 64*(65536000L/ms))
  {
    initialiserCompteur((((uint32_t)ms)*8000)/64, lib::Prescaler_64);
  }
  else if (F_CPU <= 256*(65536000L/ms))
  {
    initialiserCompteur((((uint32_t)ms)*8000)/256, lib::Prescaler_256);
  }
  else if (F_CPU <= 1024*(65536000L/ms))
  {
    initialiserCompteur((((uint32_t)ms)*8000)/1024, lib::Prescaler_1024);
  }
  else
  {
    //throw error
  }
}

void initialiserCompteur(uint16_t duree) {
  initialiserCompteur(duree, lib::Prescaler_1);
}

void initialiserCompteur(uint16_t duree, lib::Prescaler prescaler) {
  // minuterieExpiree = 0;
  // mode CTC du timer 1 avec horloge divisee par 1024
  // interruption apres la duree specifiee
  TCNT1 = 0;
  OCR1A = duree;

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCCR1B |= ((1 << WGM12));

  definirPrescaler(prescaler);
  TIMSK1 |= (1 << OCIE1A);
}

void definirPrescaler(lib::Prescaler prescaler) {
  if (prescaler & 0x01) {
    PORTC |= (1 << 2);
    TCCR1B |= (1 << CS10);
  } else {
    TCCR1B &= ~(1 << CS10);
  }

  if (prescaler & 0x02) {
    PORTC |= (1 << 4);
    TCCR1B |= (1 << CS11);
  } else {
    TCCR1B &= ~(1 << CS11);
  }

  if (prescaler & 0x04) {
    PORTC |= (1 << 6);
    TCCR1B |= (1 << CS12);
  } else {
    TCCR1B &= ~(1 << CS12);
  }
}
