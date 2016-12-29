#ifndef RoomFinder_h
#define RoomFinder_h

#include "lib_dir/Settings.h"
#include "lib_dir/can.h"
#include "Pieces.h"
#include "lib_dir/Util.h"

class RoomFinder {

public:
  /* ===OBJECT DEFAULT CONSTRUCTORS/DESTRUCTORS=== */
  RoomFinder();
  ~RoomFinder();


  /* ===MAIN PROGRAM METHODS=== */
  // Returns the distance to obstacle in centimeters
  float getDistanceCm();

  // Returns the shape of the room
  Piece::Piece getShape();

  // Resets the data attributes of the object
  void reset();


  /* ===DATA PROCESSING METHODS===*/
  // Returns the number of data points above a certain threshold used to identify square room
  uint16_t getSquareScore();

  // Returns the variance of the room, a lower variance indicates a circle, while a bigger variance is an octagon
  int8_t getCircleVsOctagon();


  /* ===DATA COLLECTION METHODS=== */
  // Collect a data point from the sensor, and add it to the data tables
  bool addSample();

  // Compress samples before adding to main table at ratio of samplesPerData_ to 1
  void compressSamples();

  // Average of raw data, we compress by taking averages
  uint16_t averageCompressed();

  // Get the distance from sensor in the form of a uint8_t [0 to 255]
  uint8_t getVoltageRatio();

  // Convert uint8_t voltage ratio distance to centimeters
  float convertVoltageToCm(uint8_t voltage);

private:
  /* ===DATA COLLECTION ATTRIBUTES=== */
  // Compression ratio of data entered in sample_[]
  uint8_t samplesPerData_;

  // Array to store data before compression
  uint8_t tempSample_[16];

  // How many elements are in tempSample_[]
  uint8_t tCounter_;

  // Main data, up to 200 elements, can compress up to 16:1, so up to 3200 compressed data points
  uint8_t sample_[200];

  // How many elements are in sample_[]
  uint8_t nData_;

  /* ===DISTANCE SENSOR ATTRIBUTES===*/
  // Initialize the analog to digital converter
  can converter;
};

#endif /* RoomFinder_h */
