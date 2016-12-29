
#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/delay_basic.h>

#include "Librairie.h"
#include "Roue.h"

void debounce() {
  _delay_ms(10);
}

bool isButtonPressed() {
  if (PIND & 0x04) {
    debounce();
    if (PIND & 0x04) {
      return true;
    }
  }
  return false;
}

bool isButtonReleased() {
  if (!(PIND & 0x04)) {
    debounce();
    if (!(PIND & 0x04)) {
      return true;
    }
  }
  return false;
}

void setLight(lib::CouleurDell couleur) {
  // On utilise les PIN 2 et 3 pour le DEL
  // switch (couleur) {
  //   case CouleurDell_Eteint:
  //   {
  //     // set bit 2 et 3 à 0 sans toucher les autres PIN
  //     PORTB &= (~(0x01 << 2 | 0x01 << 3));
  //     break;
  //   }
  //   case CouleurDell_Vert:
  //   {
  //     // set bit 2 à 1 et bit 3 à 0 sans toucher les autres PIN
  //     PORTB &= (~(0x01 << 3));
  //     PORTB |= 0x01 << 2;
  //     break;
  //   }
  //   case CouleurDell_Rouge:
  //   {
  //     // set bit 2 à 0 et bit 3 à 1 sans toucher les autres PIN
  //     PORTB &= (~(0x01 << 2));
  //     PORTB |= 0x01 << 3;
  //     break;
  //   }
  // }
  // Eteint = 0 0
  // Vert = 0 1
  // Rouge = 1 0
  if (couleur & 0x01) { // set le bit PINB 2
    PORTB |= (0x01 << 2);
  } else {
    PORTB &= ~(0x01 << 2);
  }

  if (couleur & 0x02) { // set le bit PINB 3
    PORTB |= (0x01 << 3);
  } else {
    PORTB &= ~(0x01 << 3);
  }
}

void initialisation(uint8_t portA, uint8_t portB, uint8_t portC, uint8_t portD) {
  cli();
  DDRA = portA;
  DDRB = portB;
  DDRC = portC;
  DDRD = portD;

  EIMSK |= _BV(INT0);
  EICRA |= (1 << ISC00); //Trigger on any logical change of INT0

	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous �viter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	//UCSR0A = ;
  // TXEN0 = transmission enable
  // RXEN0 = receive enable
	UCSR0B = _BV(TXEN0)|_BV(RXEN0);
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);

  sei();

  // Musique d'initialisation
  soundOn(48);
  _delay_ms(225);
  soundOn(48);
  _delay_ms(225);
  soundOn(52);
  _delay_ms(225);
  soundOn(55);
  _delay_ms(340);
  soundOn(52);
  _delay_ms(225);
  soundOn(55);
  _delay_ms(450);
  soundOff();

}

void ajusterPWM(uint8_t ratio, lib::Direction direction) {
  ajusterPWM(ratio, ratio, direction, direction);
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

void arreterPWM() {
  // Set en mode [0 0] pour Phase-correct PWM-mode "Normal port operation, OC2A disconnected."
  TCCR2A &= ~(1 << COM2A1 | 1 << COM2B1);
}

void ajusterDirection(lib::Roue roue, lib::Direction direction) {
  switch (direction) {
    case lib::Direction_Avancer:
      PORTD |= (1 << roue);
    break;
    case lib::Direction_Reculer:
      PORTD &= ~(1 << roue);
    break;
  }
}

void clairInterruptions() {
  EIFR |= (1 << INTF0); // Clear interruptions pour les external interrupts
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
  TCNT1 = 0; // débute compteur à 0
  OCR1A = duree; // valeur de comparaison

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCCR1B |= ((1 << WGM12)); //set CTC mode

  definirPrescaler(prescaler);
  TIMSK1 |= (1 << OCIE1A); // enable output compare timer1 with OCR1A
}

void definirPrescaler(lib::Prescaler prescaler) {
  /*
  On définit les prescalers suivants en binaire:
                      CS12  CS11  CS10
    Prescaler_1     = 0     0     1
    Prescaler_8     = 0     1     0
    Prescaler_64    = 0     1     1
    Prescaler_256   = 1     0     0
    Prescaler_1024  = 1     0     1
    puis on les set bit par bit
  */
  if (prescaler & 0x01) { // set bit CS10
    TCCR1B |= (1 << CS10);
  } else {
    TCCR1B &= ~(1 << CS10);
  }

  if (prescaler & 0x02) { // set bit CS11
    TCCR1B |= (1 << CS11);
  } else {
    TCCR1B &= ~(1 << CS11);
  }

  if (prescaler & 0x04) { // set bit CS12
    TCCR1B |= (1 << CS12);
  } else {
    TCCR1B &= ~(1 << CS12);
  }
}

void arreterMinuterie() {
  TIMSK1 &= ~(1 << OCIE1A); // arrêter les interruptions déclenchées par OCR1A
}

void transmissionUART ( uint8_t donnee ) {
	while (!(UCSR0A & _BV(UDRE0))); // attendre que le UDRE0 dans le registre UCSR0A est set = Data Register empty -> new data can be transmitted
	UDR0=donnee; // USART Data Register (write 1 byte at a time)
}

void soundOn(uint8_t note) {
  uint32_t frequency = 440000 * pow(2, (note - 69) / 12.0);
  uint32_t periode_us = pow(10, 9) / frequency;
  uint32_t us = periode_us / 2;

  if (((us < 4550) & (us > 4540))) {
    setLight(lib::CouleurDell_Vert);
  }

  if (F_CPU <= 256000000L/us)
  {
    initialiserCompteur0(us*8, lib::Prescaler_1);
  }
  else if (F_CPU <= 8*(256000000L/us))
  {
    initialiserCompteur0(us*8/8, lib::Prescaler_8);
  }
  else if (F_CPU <= 64*(256000000L/us))
  {
    initialiserCompteur0(us*8/64, lib::Prescaler_64);
  }
  else if (F_CPU <= 256*(256000000L/us))
  {
    initialiserCompteur0(us*8/256, lib::Prescaler_256);
  }
  else if (F_CPU <= 1024*(256000000L/us))
  {
    initialiserCompteur0(us*8/1024, lib::Prescaler_1024);
  }
  else
  {
    //throw error
  }
}

void soundOff() {
  TIMSK0 = 0;
}

void initialiserCompteur0(uint8_t duree) {
  initialiserCompteur0(duree, lib::Prescaler_1);
}

void initialiserCompteur0(uint8_t duree, lib::Prescaler prescaler) {
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0; // Initialiser compteur à 0
  OCR0A = duree; // Valeur de comparaison

  TCCR0A |= ((1 << WGM01)); // set CTC mode

  definirPrescaler0(prescaler);
  TIMSK0 |= (1 << OCIE0A); // enable interrupt on timer == OCR0A
}

void definirPrescaler0(lib::Prescaler prescaler) {
  /*
  On définit les prescalers suivants en binaire:
                      CS02  CS01  CS00
    Prescaler_1     = 0     0     1
    Prescaler_8     = 0     1     0
    Prescaler_64    = 0     1     1
    Prescaler_256   = 1     0     0
    Prescaler_1024  = 1     0     1
    puis on les set bit par bit
  */

  if (prescaler & 0x01) { // set bit CS00
    TCCR0B |= (1 << CS00);
  } else {
    TCCR0B &= ~(1 << CS00);
  }

  if (prescaler & 0x02) { // set bit CS01
    TCCR0B |= (1 << CS01);
  } else {
    TCCR0B &= ~(1 << CS01);
  }

  if (prescaler & 0x04) { // set bit CS02
    TCCR0B |= (1 << CS02);
  } else {
    TCCR0B &= ~(1 << CS02);
  }
}
