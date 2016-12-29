
#define F_CPU 8000000L

#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "can.h"
#include "Memoire24CXXX.h"
#include "lib_dir/Librairie.h"
#include "lib_dir/Direction.h"
#include "lib_dir/CouleurDell.h"
#include "lib_dir/Roue.h"
#include "lib_dir/Prescaler.h"

volatile uint8_t counter = 0;

int main()
{
  cli();
  initialisation(0x00, 0x00, 0xff, 0xf0);
  sei();
  can converter;
  initialiserMinuterie(100);

  while (1) {


    switch (counter % 2) {
      case 0:
        setLight(lib::CouleurDell_Vert);
      break;
      case 1:
        setLight(lib::CouleurDell_Rouge);
      break;
    }

        /*

  uint8_t ratio = converter.lecture(1) >> 2;
  for (uint8_t i = 0; i < 255; i++) {
    if (i < ratio) {
      setLight(lib::CouleurDell_Rouge);
    }
    else {
      setLight(lib::CouleurDell_Vert);
    }
  }
  //TEST COMPLETE AVEC SUCCES

  */

  /*
    uint8_t ratio = converter.lecture(1) >> 2;
    for (uint8_t i = 0; i < 255; i++) {
      if (i < ratio) {
        setLight(lib::CouleurDell_Rouge);
      }
      else {
        setLight(lib::CouleurDell_Vert);
      }
    }
    //TEST COMPLETE AVEC SUCCES

    */

/*
    setLight(lib::CouleurDell_Vert);
    _delay_ms(1000);
    setLight(lib::CouleurDell_Eteint);
    _delay_ms(1000);
    setLight(lib::CouleurDell_Rouge);
    _delay_ms(1000);

    if (isButtonPressed())
      while (!isButtonReleased()) {
        setLight(lib::CouleurDell_Vert);
        _delay_ms(100);
        setLight(lib::CouleurDell_Eteint);
        _delay_ms(100);
        setLight(lib::CouleurDell_Rouge);
        _delay_ms(100);
      }
    TEST COMPLETE AVEC SUCCES
*/
  }

  return 0;
}

ISR(TIMER1_COMPA_vect){
	counter++;
}
