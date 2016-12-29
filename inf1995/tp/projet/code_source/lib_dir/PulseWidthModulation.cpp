#include "PulseWidthModulation.h"
#include "Dell.h"


void setPWM(uint8_t ratio, PWM::Direction direction) {
  setPWM(ratio, ratio, direction, direction);
}

void setPWM(uint8_t ratioLeftWheel, uint8_t ratioRightWheel, PWM::Direction direction) {
  setPWM(ratioLeftWheel, ratioRightWheel, direction, direction);
}

void setPWM(uint8_t ratio, PWM::Direction directionLeftWheel, PWM::Direction directionRightWheel) {
  setPWM(ratio, ratio, directionLeftWheel, directionRightWheel);
}

void setPWM(uint8_t ratioLeftWheel, uint8_t ratioRightWheel, PWM::Direction directionLeftWheel, PWM::Direction directionRightWheel) {
  TCCR2A = 0; // Reset Registers
  TCCR2B = 0;

  // Outputs are 1 to outputs OC1A and OC1B on successful comparison
  // in PWM mode 8bits on counter 2
  TCCR2A |= (1 << WGM20 | 1 << COM2A1 | 1 << COM2B1) ;

  // prescaler of 8 - fixe PWM frequency
  TCCR2B |= (1 << CS11);

  OCR2A = ratioRightWheel ; //Sets the ratios (Fastest : 0xff, Slowest : 0x00)
  OCR2B = ratioLeftWheel ;

  setDirection(PWM::LEFT, directionLeftWheel);  // Set the wheels rotation direction
  setDirection(PWM::RIGHT, directionRightWheel);

}

void stopPWM() {
  TCCR2A = 0; // Reset Registers
  TCCR2B = 0;
}

void setDirection(PWM::Wheel wheel, PWM::Direction direction) {
  // set bit after bit the value required
  // See the values of the enum "Wheel"
  switch (direction) {
    case PWM::FORWARD:
      PORTD |= (1 << wheel);
    break;
    case PWM::BACKWARD:
      PORTD &= ~(1 << wheel);
    break;
  }

}
