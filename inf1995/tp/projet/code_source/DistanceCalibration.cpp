#include "lib_dir/Settings.h"
#include "lib_dir/Util.h"
#include "lib_dir/Timer.h"
#include "lib_dir/PulseWidthModulation.h"
#include "lib_dir/Dell.h"
#include "RoomFinder.h"

int main()
{
  // Set les ports
  initialization();

  // Interface to detect the room shapes
  RoomFinder roomFinder;

  /* === DISTANCE SENSOR CALIBRATION === */
  // ===DO NOT REMOVE, VERY IMPORTANT FOR CALIBRATION===
  // CHECK #1: LED must turn RED at 11 centimeters
  // CHECK #2: LED must alternate between red and green at every 2 centimeters
  // !!! COMMENT OUT WHEN RUNNING MAIN PROGRAM !!!
  while(true){
    uint8_t distance = roomFinder.getDistanceCm();
    if(distance < 10 || distance > 40)
    setLight(Dell::OFF);
    else if((distance/2)%2==0)
    setLight(Dell::GREEN);
    else
    setLight(Dell::RED);
  }

  return 0;
}
