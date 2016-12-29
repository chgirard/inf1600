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
  DDRD = 0xff; // PORT D est en mode entre

  PORTC = 0x00; // Initialiser à off
  sei();
}

void ajustementPWM (uint8_t ratio) {
// mise a un des sorties OC1A et OC1B sur comparaison
// reussie en mode PWM 8 bits, phase correcte
// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
// page 130 de la description technique du ATmega324PA)
TCCR1A |= (1 << WGM10 | 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0) ;
OCR1A = ratio ;
OCR1B = ratio ;

// division d'horloge par 8 - implique une frequence de PWM fixe
TCCR1B |= (1 << CS11);
TCCR1C = 0;
}

int main()
{
  initialisation();
  ajustementPWM(100);
  while(1) {

  }
  return 0;
}
