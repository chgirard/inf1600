
#include "Sound.h"

void soundOn(uint8_t note) {
  uint32_t frequency = 440000 * pow(2, (note - 69) / 12.0); // find the frequency in milli Hertz from the MIDI note
  uint32_t periode_us = pow(10, 9) / frequency; // finds the period in micro seconds from the frequency
  uint32_t us = periode_us / 2; // Finds half of the period

  if (F_CPU <= 256000000L/us) // Checks if the counter can fit in prescaler 1
  {
    initialiserCompteur0(us*8, Prescaler::Prescaler_1);
  }
  else if (F_CPU <= 8*(256000000L/us)) // Checks if the counter can fit in prescaler 8
  {
    initialiserCompteur0(us*8/8, Prescaler::Prescaler_8);
  }
  else if (F_CPU <= 64*(256000000L/us)) // Checks if the counter can fit in prescaler 64
  {
    initialiserCompteur0(us*8/64, Prescaler::Prescaler_64);
  }
  else if (F_CPU <= 256*(256000000L/us)) // Checks if the counter can fit in prescaler 256
  {
    initialiserCompteur0(us*8/256, Prescaler::Prescaler_256);
  }
  else if (F_CPU <= 1024*(256000000L/us)) // Checks if the counter can fit in prescaler 1024
  {
    initialiserCompteur0(us*8/1024, Prescaler::Prescaler_1024);
  }
  else
  {
    //throw error
  }
}

void soundOff() {
  OCR0B = 0xff; // Comparison value
  TCCR0A = 0;   //Registers set to 0 stops the counter
  TCCR0B = 0;
}

void initialiserCompteur0(uint8_t duree) {
  initialiserCompteur0(duree, Prescaler::Prescaler_1);
}

void initialiserCompteur0(uint8_t duree, Prescaler::Prescaler prescaler) {
  TCCR0A = 0; //Reset registers
  TCCR0B = 0;
  TCNT0 = 0; // Initialize counter at 0

  PORTB &= ~(1 << 5); //Sets the ground input of the speaker to 0

  TCCR0A |= (1 << WGM00); // set PWM, Phase Correct mode
  TCCR0B |= (1 << WGM02); // set PWM, Phase Correct mode
  TCCR0A |= ((1 << COM0B1) | (1 << COM0B0)); // Set output on compare B

  definirPrescaler0(prescaler); // Set prescaler

  OCR0A = duree; // TOP value
  OCR0B = duree / 2; // Comparison value
}

void definirPrescaler0(Prescaler::Prescaler prescaler) {
  /*
  Define these prescalers in binary
                      CS02  CS01  CS00
    Prescaler_1     = 0     0     1
    Prescaler_8     = 0     1     0
    Prescaler_64    = 0     1     1
    Prescaler_256   = 1     0     0
    Prescaler_1024  = 1     0     1
    Set them bit after bit
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
