#include "Dell.h"

void setLight(Dell::Color color) {
  // Using PIN 2 et 3 for the DEL
  // Off = 00
  // Green = 01
  // Red = 10
  if (color & 0x01) { // set PB2
    PORTB |= (0x01 << 0);
  } else {
    PORTB &= ~(0x01 << 0);
  }

  if (color & 0x02) { // set PB3
    PORTB |= (0x01 << 1);
  } else {
    PORTB &= ~(0x01 << 1);
  }
}
