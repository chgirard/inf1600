#ifndef SOUND_H
#define SOUND_H

#include "Settings.h"
#include "Prescaler.h"

// Activates the speaker at a defined MIDI note
void soundOn(uint8_t note);

// Stops the speaker
void soundOff();

//Sets the appropriate regsters for the timer 0
void initializeSoundTimer(uint8_t duration);

//Sets the appropriate regsters for the timer 0
void initialiserCompteur0(uint8_t duration, Prescaler::Prescaler prescaler);

//Sets the appropriate regsters for the prescaler for the timer 0
void definirPrescaler0(Prescaler::Prescaler prescaler);

#endif // !SOUND_H
