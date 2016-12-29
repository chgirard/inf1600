#include "RoomFinder.h"

/* ===OBJECT DEFAULT CONSTRUCTORS/DESTRUCTORS=== */
RoomFinder::RoomFinder() {
  nData_ = 0;
  samplesPerData_ = 1;
  tCounter_ = 0;
}

RoomFinder::~RoomFinder() {

}


/* ===MAIN PROGRAM METHODS=== */
// Returns the distance to obstacle in centimeters
float RoomFinder::getDistanceCm() {
  return convertVoltageToCm(getVoltageRatio());
}

// Returns the shape of the room
Piece::Piece RoomFinder::getShape() {
  // squareScore -> # of data greater than 23 centimeters [half sample]
  uint16_t squareScore = getSquareScore();
  // if more than 5% of data is greater -> square
  if (squareScore > nData_/40) {
    return Piece::CARRE;
  }
  else {
    // score -> max - min of the samples from 40 to 60 percent
    int8_t score = getCircleVsOctagon();
    if (score > 3) {
      return Piece::OCTOGONE;
    }
    else {
      return Piece::CERCLE;
    }
  }
}

// Resets the data attributes of the object
void RoomFinder::reset() {
	nData_ = 0;
  samplesPerData_ = 1;
  tCounter_ = 0;
}


/* ===DATA PROCESSING METHODS===*/
// Returns the number of data points above a certain threshold used to identify square room
uint16_t RoomFinder::getSquareScore() {
  uint16_t squareCounter = 0;
  // checks first half of samples collected
  for (uint16_t i = 0; i < nData_/2; i++) {
    if (convertVoltageToCm(sample_[i]) > 23) {
      squareCounter++;
    }
  }
  return squareCounter;
}

// Returns the max - min of the room, a lower spread indicates a circle, while a bigger spread is an octagon
int8_t RoomFinder::getCircleVsOctagon() {
  uint16_t midpoint = nData_/2;
  uint16_t offset = nData_/5;
  int16_t min = 255;
  int16_t max = 0;

  uint16_t lowpoint = midpoint - offset;
  uint16_t highpoint = midpoint + offset;
  for (uint16_t j = lowpoint; j < highpoint; j++) {
    int16_t value = convertVoltageToCm(sample_[j]);
    if (value < min) {
      min = value;
    }
    if (value > max) {
      max = value;
    }
  }

  return max - min;
}


/* ===DATA COLLECTION METHODS=== */
// Collect sample and store it
bool RoomFinder::addSample() {
  if (samplesPerData_ >= 16) {
    return false; // collected 3200 raw samples
  }
  if (nData_ >= 200) {
    compressSamples();
  }

  // add data point to temporary table
  tempSample_[tCounter_] = getVoltageRatio();

  // if we don't have enough data points to compress at the ratio specified
  // ratio -> samplesPerData_ to 1
  if (tCounter_ < samplesPerData_ - 1) {
    tCounter_++;
  }
  // we have enough data points to compress
  // compress then move to main data table
  else {
    sample_[nData_] = averageCompressed();
    nData_++;
    tCounter_ = 0; // reset temporary table
  }

  return true;
}

// Compress samples before adding to main table at ratio of samplesPerData_ to 1
void RoomFinder::compressSamples() {
  for (uint8_t i = 0; i < 100; i++) {
    sample_[i] = (sample_[2*i] + sample_[2*i + 1])/2;
  }
  nData_ = 100;
  samplesPerData_ *= 2;
}

// Average of raw data, we compress by taking averages
uint16_t RoomFinder::averageCompressed() {
  uint16_t sum = 0;
  for (uint8_t i = 0; i < samplesPerData_; i++) {
    sum += tempSample_[i];
  }
  return sum / samplesPerData_;
}

// Get the distance from sensor in the form of a uint8_t [0 to 255]
uint8_t RoomFinder::getVoltageRatio() {
  // Converter returns a 10 bit value. Shift by 2 to get an 8 bit value.
	return converter.lecture(0) >> 2;
}

// Convert uint8_t voltage ratio distance to centimeters
float RoomFinder::convertVoltageToCm(uint8_t voltageRatio) {
  // voir courbe de voltage vs. distance dans la documentation
  // voir "extra/Capteur Distance/SENSEURDISTANCE.xlsx"
  return float(pow(voltageRatio, -1.288) * 11419);
}
