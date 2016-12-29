#include "LineFollower.h"


bool isDetecting(Sensor::Sensor sensor) {
  return PINA & sensor; // A 8bit value is associated with each member of the enum
}


LineFollower::LineFollower() {
      isOnLine = true;
      rotationStage = 5;

      normalRightSpeed = INITIAL_SPEED_RIGHT;
      normalLeftSpeed = INITIAL_SPEED_LEFT;
      rightSpeed = INITIAL_SPEED_RIGHT;
      leftSpeed = INITIAL_SPEED_LEFT;
}

LineFollower::~LineFollower() {}

bool LineFollower::followLine( bool twist) {

  ajustTrack(100, twist); // Follow Line


  // IF 3 or more sensors detect a line, indicates an intersection
  uint8_t nbCapteurDetect = 0;
  if (isDetecting(Sensor::EXTREM_LEFT))
    nbCapteurDetect++;
  if (isDetecting(Sensor::LEFT))
    nbCapteurDetect++;
  if (isDetecting(Sensor::CENTER))
    nbCapteurDetect++;
  if (isDetecting(Sensor::RIGHT))
    nbCapteurDetect++;
  if (isDetecting(Sensor::EXTREM_RIGHT))
    nbCapteurDetect++;

  return nbCapteurDetect >= 3;
}

bool LineFollower::followLine(uint8_t distanceToWall, bool twist) {
  // This function is called whan the robot enters into rooms
  // It's speed will decay the nearest it gets to the back wall
	

  if (distanceToWall - 19 < 5) // If distance is lower than 24
  {
    ajustTrack(((distanceToWall - 19) * 3 ) + 85, twist); // Decay speed
  }
  else
  {
    ajustTrack(100, twist); // Else 100% speed (normal)
  }

  return distanceToWall < 21; // returns if the robot should stop
}

void LineFollower::ajustTrack(uint8_t percentage, bool twist) {

// If the center sensor is detecting a line go straight forward
  if (isDetecting(Sensor::CENTER))
  {
    if (!isOnLine) {
      isOnLine = true;
      rightSpeed = normalRightSpeed;
      leftSpeed = normalLeftSpeed;
    }

// If one of the extrem sensor detects a line and is in twist mode, do  the twist
// The twist is a small rotating move backward to get back on track
  } else if (isDetecting(Sensor::EXTREM_LEFT) && twist) {

	// small stop
      stopPWM();
      _delay_ms(200);

    // while not back on track, small rotation motion backward
    while (!isDetecting(Sensor::CENTER)) {
      setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 100), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 70), PWM::BACKWARD);
      _delay_ms(5);
    }

	// small stop
      stopPWM();
      _delay_ms(200);

  } else if (isDetecting(Sensor::EXTREM_RIGHT) && twist) {

	// small stop
      stopPWM();
      _delay_ms(200);

    // while not back on track, small rotation motion backward
    while (!isDetecting(Sensor::CENTER)) {
      setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 70), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 100), PWM::BACKWARD);
      _delay_ms(5);
    }

	// small stop
      stopPWM();
      _delay_ms(200);

// When the right or left sensor are detecting a line, slows or accelerate the right wheel to get back on track
  } else if (isDetecting(Sensor::LEFT)) {

    if (isOnLine) {
      isOnLine = false;

      if (normalRightSpeed < INITIAL_SPEED_RIGHT + 0x20) { //normal speed cannot go higher than 0x20 over it's initial speed'
        normalRightSpeed += 3;
      }
    }

    if ((rightSpeed < INITIAL_SPEED_RIGHT + 0x20) && (rightSpeed < 0xff)) {//actual speed cannot go higher than 0x40 over it's initial speed and 0xff
      rightSpeed += 1;
    }

  } else if (isDetecting(Sensor::RIGHT)) {

    if (isOnLine) {
      isOnLine = false;

      if (normalRightSpeed > INITIAL_SPEED_RIGHT - 0x20) {//normal speed cannot go lower than 0x20 lower it's initial speed'
        normalRightSpeed -= 4;
      }

    }

    if ((rightSpeed > INITIAL_SPEED_RIGHT - 0x20) && (rightSpeed > 0x50)) {//actual speed cannot go lower than 0x40 lower it's initial speed anf 0x50
      rightSpeed -= 1;
    }

// If one of the extrem sensor detects a line and there is no twist
// Stops one wheel while the other moves forward to get back on track
  } else if (isDetecting(Sensor::EXTREM_LEFT) && !twist) {

	// small stop
      stopPWM();
      _delay_ms(200);

	//while still off-track, stop the left wheel and move the right one
      while (isDetecting(Sensor::EXTREM_LEFT) || !isDetecting(Sensor::LEFT)) {
        setPWM(0x00, ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 80), PWM::FORWARD);
        _delay_ms(5);
      }

	// small stop
      stopPWM();
      _delay_ms(200);

  } else if (isDetecting(Sensor::EXTREM_RIGHT) && !twist) {

	// small stop
      stopPWM();
      _delay_ms(200);

	//while still off-track, stop the right wheel and move the left one
      while (isDetecting(Sensor::EXTREM_RIGHT) || !isDetecting(Sensor::RIGHT)) {
        setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 80), 0x00, PWM::FORWARD);
        _delay_ms(5);
      }

	// small stop
      stopPWM();
      _delay_ms(200);

  }

// Sets the wheel speeds based on the speeds previously set
  setPWM(ajustValueWithPercentage(leftSpeed, percentage), ajustValueWithPercentage(rightSpeed, percentage), PWM::FORWARD);
}


bool LineFollower::uTurn() {
  bool returnValue = false;
  if (rotationStage == 0) {
    rotationStage = 5; // reset rotation stage from the previous uTurn
  }

  switch (rotationStage) {

    case 5: // small hop right to give a starting speed
    {
      setPWM(0xff, PWM::FORWARD, PWM::BACKWARD);

      if (isDetecting(Sensor::EXTREM_LEFT)) {
        rotationStage--;

      }
    }
    break;

    case 4: // full speed left turn, to accelerate
    {
      setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 80), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 80), PWM::BACKWARD, PWM::FORWARD);

      if (isDetecting(Sensor::CENTER)) {
        rotationStage--;
      }
    }
    break;

    case 3: // full speed left turn,  taking Data
    {
      setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 80), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 80), PWM::BACKWARD, PWM::FORWARD);

      if (isDetecting(Sensor::EXTREM_LEFT)) {
        rotationStage--;
      }
    }
    break;

    case 2:// full speed left turn, is approaching from the line,  taking Data
    {
      setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 80), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 80), PWM::BACKWARD, PWM::FORWARD);

      if (isDetecting(Sensor::CENTER)) {
        rotationStage--;
        returnValue = true;
      }
    }
    break;

    case 1:// get back on track at a slower speed
    {

      if (isDetecting(Sensor::LEFT)) {
        stopPWM();
        rotationStage--;
        returnValue = true;
      } else {
        setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 70), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 70), PWM::FORWARD, PWM::BACKWARD);
      }

    }
    break;
  }

  return returnValue;

}

void LineFollower::rightTurn() {

	//Continue forward for one full second
  setPWM(normalLeftSpeed, normalRightSpeed, PWM::FORWARD);
  _delay_ms(1000);

	//Turn right at full speed until the extrem right sensor detects the line
  while (!isDetecting(Sensor::EXTREM_RIGHT)) {
    setPWM(INITIAL_SPEED_LEFT, INITIAL_SPEED_RIGHT, PWM::FORWARD, PWM::BACKWARD);
    _delay_ms(5);
  }

	//Continue turning at a slower speed until left sensor detects a line
  while (!isDetecting(Sensor::LEFT)) {
    setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 60), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 60), PWM::FORWARD, PWM::BACKWARD);
    _delay_ms(5);
  }

	//Turn the other way at a low speed to get back staight on the line
  while (!isDetecting(Sensor::RIGHT)) {
    setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 70), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 70), PWM::BACKWARD, PWM::FORWARD);
    _delay_ms(5);
  }

	// Small stop of one third of a second
  stopPWM();
  _delay_ms(300);

}

void LineFollower::leftTurn() {

	//Continue forward for one full second
    setPWM(normalLeftSpeed, normalRightSpeed, PWM::FORWARD);
    _delay_ms(1000);

	//Turn right at full speed until the extrem left sensor detects the line
  while (!isDetecting(Sensor::EXTREM_LEFT)) {
    setPWM(INITIAL_SPEED_LEFT, INITIAL_SPEED_RIGHT, PWM::BACKWARD, PWM::FORWARD);
    _delay_ms(5);
  }

	//Continue turning at a slower speed until right sensor detects a line
  while (!isDetecting(Sensor::RIGHT)) {
    setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 60), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 60), PWM::BACKWARD, PWM::FORWARD);
    _delay_ms(5);
  }

	//Turn the other way at a low speed to get back staight on the line
  while (!isDetecting(Sensor::LEFT)) {
    setPWM(ajustValueWithPercentage(INITIAL_SPEED_LEFT, 70), ajustValueWithPercentage(INITIAL_SPEED_RIGHT, 70), PWM::FORWARD, PWM::BACKWARD);
    _delay_ms(5);
  }

	// Small stop of one third of a second
  setPWM(0x00, PWM::FORWARD);
  _delay_ms(300);

}

void LineFollower::stop() {
  stopPWM();
}
