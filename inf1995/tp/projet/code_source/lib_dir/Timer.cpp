#include "Timer.h"


void startTimer(uint16_t ms) {
  if (F_CPU <= 65536000L/ms) // Checks if this time fits in the range of the Prescaler 1
  {
    initializeCounter(((uint32_t)ms)*8000, Prescaler::Prescaler_1);
  }
  else if (F_CPU <= 8*(65536000L/ms)) // Checks if this time fits in the range of the Prescaler 8
  {
    initializeCounter((((uint32_t)ms)*8000)/8, Prescaler::Prescaler_8);
  }
  else if (F_CPU <= 64*(65536000L/ms)) // Checks if this time fits in the range of the Prescaler 64
  {
    initializeCounter((((uint32_t)ms)*8000)/64, Prescaler::Prescaler_64);
  }
  else if (F_CPU <= 256*(65536000L/ms)) // Checks if this time fits in the range of the Prescaler 256
  {
    initializeCounter((((uint32_t)ms)*8000)/256, Prescaler::Prescaler_256);
  }
  else if (F_CPU <= 1024*(65536000L/ms)) // Checks if this time fits in the range of the Prescaler 1024
  {
    initializeCounter((((uint32_t)ms)*8000)/1024, Prescaler::Prescaler_1024);
  }
  else
  {
    //throw error
  }
}

void initializeCounter(uint16_t duration) {
  initializeCounter(duration, Prescaler::Prescaler_1);
}

void initializeCounter(uint16_t duration, Prescaler::Prescaler prescaler) {
  TCNT1 = 0; // Counter starts at 0
  OCR1A = duration; // Comparison value

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCCR1B |= ((1 << WGM12)); //set CTC mode

  setPrescaler(prescaler);
  TIMSK1 |= (1 << OCIE1A); // enable output compare timer1 with OCR1A
}

void setPrescaler(Prescaler::Prescaler prescaler) {
  /*
  Sets the following prescalers in binary:
                      CS12  CS11  CS10
    Prescaler_1     = 0     0     1
    Prescaler_8     = 0     1     0
    Prescaler_64    = 0     1     1
    Prescaler_256   = 1     0     0
    Prescaler_1024  = 1     0     1
    Set them bit after bit
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

void stopTimer() {
  TIMSK1 &= ~(1 << OCIE1A); // stops interrupts thrown by OCR1A
}
