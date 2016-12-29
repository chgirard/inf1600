#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include "lib_dir/Settings.h"
#include "lib_dir/Util.h"
#include "Color.h"

class ColorDetector {
public:

  /* ===OBJECT DEFAULT CONSTRUCTORS/DESTRUCTORS=== */
	ColorDetector();
	~ColorDetector();

  /* ===MAIN PROGRAM METHODS=== */
	// Add a Sample to the class representing the frequency of the last filter set on the current color
	void addSample(uint16_t nCycles);

	// To get the current color
 	Color::Color getColor();

	// To open the sensor LED
	void openDell();

	// To close the sensor LED
	void closeDell();

private:
  /* ===CLASS SPECIFiC ENUM=== */
	// The different sensor's filters
	enum Filter {
		CLEAR, RED, GREEN, BLUE
	};

  /* ===PRIVATE MANAGEMENT METHODS=== */
	// Sets the filter to the specified value
	void setSensorFilter(Filter filter);

	// Switch to the next filter
	void nextFilter();

	// Saves the data to the attributes
	void setFilterFrequency(uint16_t nCycles);

	// Update the buffer/verified value based on the last readings
	void updateColor();

	// Finds the correct color based on the last readings
	Color::Color colorAlgorithm();

  /* ===SAVING ATTRIBUTES=== */
	// Current filter applied to the sensor
	Filter currentFilter_;

	// The official color the class is sur to be on
	Color::Color verifiedColor_;

	// The temporary color the class reads, waiting to be verified
	Color::Color bufferColor_;

	// The buffer size until the buffer value gets verified
	uint8_t bufferSize_;

  /* ===PREVIOUS FILTER ATTRIBUTES=== */
	// Last frequencies read for the different filters - waiting to be processed
	uint16_t clearFilterFrequency_;
	uint16_t redFilterFrequency_;
	uint16_t greenFilterFrequency_;
	uint16_t blueFilterFrequency_;
};


#endif /* ColorDetector_h */
