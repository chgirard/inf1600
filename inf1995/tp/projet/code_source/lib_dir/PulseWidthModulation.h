#ifndef PULSE_WIDTH_MODULATION_H
#define PULSE_WIDTH_MODULATION_H

#include "Settings.h"

  namespace PWM {

    // The 2 wheels of the robot
    enum Wheel {
        LEFT = 4, RIGHT = 5
    };

    // The two possible directions for the wheel to rool to
    enum Direction {
        FORWARD, BACKWARD
    };
  }


  // Sets the PWM to the desired ratios and directions
  void setPWM(uint8_t ratio, PWM::Direction direction);
  void setPWM(uint8_t ratioLeftWheel, uint8_t ratioRightWheel, PWM::Direction direction);
  void setPWM(uint8_t ratio, PWM::Direction directionLeftWheel, PWM::Direction directionRightWheel);
  void setPWM(uint8_t ratioLeftWheel, uint8_t ratioRightWheel, PWM::Direction directionLeftWheel, PWM::Direction directionRightWheel);

  // Stop the PWM
  void stopPWM();

  // Sets the rotation direction of a defined wheel
  void setDirection(PWM::Wheel wheel, PWM::Direction direction);

#endif // !PULSE_WIDTH_MODULATION_H
