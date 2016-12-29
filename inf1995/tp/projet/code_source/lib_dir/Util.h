#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include "Settings.h"
#include "Sound.h"

// Verifies if the button is really pressed after 10 ms
bool debounce();

// Checks whether botton is pressed or not
bool isButtonPressed();

// Initialise different registers for the well performing of the robot
void initialization();

// Removes interruptions in queue
void clairInterruptions();

//Transbit a Bit to PC via USB
void transmissionUART ( uint8_t donnee );

//Multiplies a value with a percentage
uint8_t ajustValueWithPercentage ( uint8_t valeur, uint8_t pourcentage );

#endif // ! LIBRAIRIE_H
