#ifndef MINUTERIE_H
#define MINUTERIE_H

#include "Settings.h"
#include "Prescaler.h"

// Starts the timer 1 with the defined amount of time in ms (from 1 to 8000)
void startTimer(uint16_t ms);

// Sets the appropriate registers for the timer 1
void initializeCounter(uint16_t duration);

// Sets the appropriate registers for the timer 1
void initializeCounter(uint16_t duration, Prescaler::Prescaler prescaler);

// Sets the appropriate registers for the prescaler of the timer 1
void setPrescaler(Prescaler::Prescaler prescaler);

// Stops the timer 1 interrupts
void stopTimer();

#endif // !MINUTERIE_H
