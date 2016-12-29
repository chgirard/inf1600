/*
 * Nom: TP7-Probleme_2.cpp
 * Copyright (C) 2016 Sebastien Chagnon et Sida (Eric) Li
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description:
 * Version: 1.0
 */

#define F_CPU 8000000
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include "can.h"

int main()
{
  DDRA = 0x00; // PORT A est en mode entre
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entre

  can converter = can();

  for (;;) {
    uint8_t ratio = converter.lecture(0) >> 2;
    for (uint8_t i = 0; i < 255; i++) {
      if (i < ratio) {
        PORTC = 0x01; //rouge
      }
      else {
        PORTC = 0x02; //vert
      }
    }
  }
  return 0;
}
