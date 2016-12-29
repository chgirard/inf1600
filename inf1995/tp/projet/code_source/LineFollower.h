#ifndef LineFollower_H
#define LineFollower_H

  #include "lib_dir/Settings.h"
  #include "lib_dir/PulseWidthModulation.h"
  #include "lib_dir/Util.h"

  namespace Sensor {
    // 5 Different sensors on the line detector
    enum Sensor {
      EXTREM_LEFT = 0x80, LEFT = 0x40, CENTER = 0x20, RIGHT = 0x10, EXTREM_RIGHT = 0x08
    };
  }

  bool isDetecting(Sensor::Sensor sensor);

  class LineFollower {

  public:
// Constructors and desctructors
    LineFollower();
    ~LineFollower();

// Call to follor the line , returns true at an intersection
    bool followLine(bool twist);

// Call to follor the line , returns true at the appropriate distance from the wall
    bool followLine(uint8_t distanceToWall, bool twist);

// Call to make a uturn returns true twice, once it is ready to start measurments and once it is ready to stop
    bool uTurn();

// Robot makes a right turn
    void rightTurn();

// Right makes a left turn
    void leftTurn();

// Stop the robot
    void stop();

  private:
    void ajustTrack(uint8_t percentage, bool twist);

// true when sensor C3 detects the line
    bool isOnLine;

// rotation stade of the robot for the uTurn
    uint8_t rotationStage;

// Ajusted Speed of the robot for the right wheel
    uint8_t normalRightSpeed;

// Ajusted Speed of the robot for the left wheel
    uint8_t normalLeftSpeed;

// Actual Speed of the robot for the right wheel
    uint8_t rightSpeed;

// Actual Speed of the robot for the left wheel
    uint8_t leftSpeed;

  };

#endif // ! LineFollower_H
