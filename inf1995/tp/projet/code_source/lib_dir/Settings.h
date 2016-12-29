#ifndef SETTINGS_H
#define SETTINGS_H

#define F_CPU 8000000L
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>
#include <util/twi.h>

//1 -> output
//0 -> input

//PA0 input for the distance sensor
//PA1 free
//PA2 output for the calibration of the line sensor
//PA3 input Captor 5 of the line sensor
//PA4 input Captor 4 of the line sensor
//PA5 input Captor 3 of the line sensor
//PA6 input Captor 2 of the line sensor
//PA7 input Captor 1 of the line sensor
#define PA 0x00

//PB0 output for the Dell
//PB1 output for the Dell
//PB2 free
//PB3 free
//PB4 output for the active input of the speaker
//PB5 output for the ground input of the speaker
//PB6 free
//PB7 free
#define PB 0xff

//PC0 free
//PC1 free
//PC2 output S0 of color sensor
//PC3 output S1 of color sensor
//PC4 output S2 of color sensor
//PC5 output S3 of color sensor
//PC6 free
//PC7 free
#define PC 0xff

//PD0 output for the LED of the color sensor
//PD1 free
//PD2 input for the color captor's frequency
//PD3 free
//PD4 output for direction of left wheel
//PD5 output for direction of right wheel
//PD6 output output enable of left motor
//PD7 output output enable of right motor
#define PD 0xf1

// Initial Speed for Left Wheel
#define INITIAL_SPEED_LEFT 0x94
// Initial Speed for Right Wheel
#define INITIAL_SPEED_RIGHT 0xa4

#endif // ! SETTINGS_H
