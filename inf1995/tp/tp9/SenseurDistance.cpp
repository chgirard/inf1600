
#define F_CPU 8000000L

#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>
#include <math.h>

#include "can.h"
#include "Memoire24CXXX.h"
#include "lib_dir/Librairie.h"
#include "lib_dir/Direction.h"
#include "lib_dir/CouleurDell.h"
#include "lib_dir/Roue.h"
#include "lib_dir/Prescaler.h"

double convertDistance(double voltage) {
    return pow(voltage, -1.288)*11419;
}

int main()
{
  DDRA = 0x00;
  DDRB = 0xff;
  DDRC = 0xff;
  DDRD = 0x00;

  PORTC = 0x01;

  can converter;

  while (1) {
    double voltage = converter.lecture(0) >> 2;

    double distance = convertDistance(voltage);

    if (distance < 10) {
        PORTC = 0x00;
    }
    else if (distance < 13) {
        PORTC = 0x01;
    }
    else if (distance < 16) {
        PORTC = 0x02;
    }
    else if (distance < 19) {
        PORTC = 0x01;
    }
    else if (distance < 22) {
        PORTC = 0x02;
    }
    else if (distance < 25) {
        PORTC = 0x01;
    }
    else if (distance < 28) {
        PORTC = 0x02;
    }
    else {
        PORTC = 0x00;
    }
    
  }

  return 0;
}
