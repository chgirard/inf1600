#include "ColorDetector.h"


/* ===OBJECT DEFAULT CONSTRUCTORS/DESTRUCTORS=== */
ColorDetector::ColorDetector() {
	currentFilter_ = CLEAR;
	verifiedColor_ = Color::WHITE;
	bufferColor_ = Color::WHITE;
	bufferSize_ = 0;

	clearFilterFrequency_ = 0;
	redFilterFrequency_ = 0;
	greenFilterFrequency_ = 0;
	blueFilterFrequency_ = 0;
}

ColorDetector::~ColorDetector() {}


/* ===MAIN PROGRAM METHODS=== */
void ColorDetector::addSample(uint16_t nCycles) {
	setFilterFrequency(nCycles); // Save the parameter in it's corresponding attribute
	if (currentFilter_ == BLUE) { // BLUE each 4 Samples - Every 20 ms
		updateColor();	// Check if buffer / verified color should change
	}

	nextFilter(); // Sets the next filter for the net reading
}

Color::Color ColorDetector::getColor() {
	return verifiedColor_;
}

void ColorDetector::openDell() {
	PORTD |= 0x01; // Set PD0 to 1
}

void ColorDetector::closeDell() {
	PORTD &= ~(0x01); // Set PD0 to 0
}


/* ===PRIVATE MANAGEMENT METHODS=== */
void ColorDetector::setSensorFilter(Filter filter) {
	//Sets the bits s2 and s3 from the sensor to update the filter
	switch (filter){
	case RED:
		PORTC &= ~(1 << 2); // s2 = 0
		PORTC &= ~(1 << 3); // s3 = 0
		break;
	case GREEN:
		PORTC |= (1 << 2); // s2 = 1
		PORTC |= (1 << 3); // s3 = 1
		break;
	case BLUE:
		PORTC &= ~(1 << 2); // s2 = 0
		PORTC |= (1 << 3); // s3 = 1
		break;
	case CLEAR:
		PORTC |= (1 << 2); // s2 = 1
		PORTC &= ~(1 << 3); // s3 = 0
		break;
	}

	currentFilter_ = filter; //Updates the current filter
}

void ColorDetector::nextFilter() {
	// Loop through the different filters
	// There are four filters so every filter comes back every 20 ms
	switch (currentFilter_) {
		case CLEAR: {
			setSensorFilter(GREEN);
			break;
		}
		case RED: {
			setSensorFilter(BLUE);
			break;
		}
		case GREEN: {
			setSensorFilter(RED);
			break;
		}
		case BLUE: {
			setSensorFilter(CLEAR);
		}
	}
}

void ColorDetector::setFilterFrequency(uint16_t nCycles) {
	// Depending on the last filter set, update the sample frequancy until reading
	switch (currentFilter_) {
		case CLEAR: {
			clearFilterFrequency_ = nCycles;
			break;
		}
		case RED: {
			redFilterFrequency_ = nCycles;
			break;
		}
		case GREEN: {
			greenFilterFrequency_ = nCycles;
			break;
		}
		case BLUE: {
			blueFilterFrequency_ = nCycles;
		}
	}
}

void ColorDetector::updateColor() {

	Color::Color foundColor = colorAlgorithm(); // Get the detected value based on the last 4 readings

	if (foundColor == bufferColor_) { // If value is same as last calculation
		if (bufferSize_ >= 5) { // Value must be the same for 10 calculations so 5 * 20 ms = 200 ms until verified value changes
			verifiedColor_ = foundColor; // Update verified color
		} else {
			bufferSize_++; // increase the buffer
		}
	} else {
		bufferColor_ = foundColor; // update the buffer color
		bufferSize_ = 1; // Stach the buffer
	}
}

Color::Color ColorDetector::colorAlgorithm() {
	if (clearFilterFrequency_ > 100) { // if frequency > 100 - hard coded
		return Color::WHITE;
  }
	// Check for the next biggest filter associated value between Red, Green, and Blue
  else if (redFilterFrequency_ > blueFilterFrequency_ && redFilterFrequency_ > greenFilterFrequency_) {
		return Color::RED;
	}
	// Check for the next biggest filter associated value between Green and Blue
  else if (greenFilterFrequency_ >= blueFilterFrequency_) {
    return Color::GREEN;
  }
	// Rest defaults to Blue
  else {
    return Color::BLUE;
  }
}
