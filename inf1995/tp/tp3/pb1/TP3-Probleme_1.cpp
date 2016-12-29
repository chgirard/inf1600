/*
 * Nom: TD3-Probleme_1.cpp
 * Copyright (C) 2016 Sebastien Chagnon et Sida (Eric) Li
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Travail diciplinaire 3 - Problème 1
 * Version: 1.1
 */

 #define F_CPU 8000000UL

 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdio.h>

 enum States {INIT, LIGHT};

 void lightUp() {
   PORTC = 0x02;
   _delay_ms(1000);
   PORTC = 0x00;
 }

 void debounce() {
   _delay_ms(10);
 }

 int main()
 {
   DDRA = 0xff; // PORT A est en mode sortie
   DDRB = 0xff; // PORT B est en mode sortie
   DDRC = 0xff; // PORT C est en mode sortie
   DDRD = 0x00; // PORT D est en mode entrée

   int compteur = 0;

   States state = INIT;

   bool pressedDown = false;

   while(true) {
     switch (state) {
       case INIT: {
         // Pressed button 5 times, go to LIGHT state
         if (compteur == 5) {
           state = LIGHT;
         }
         // If the button is detected as pressed
         else if (PIND & 0x04) {
            debounce();
           if (PIND & 0x04) {
             pressedDown = true;
           }
         }
         // Otherwise, the button isn't detected as pressed
         else {
           debounce();
           // True only when button is released
           if (!(PIND & 0x04) && pressedDown) {
             compteur++;
             pressedDown = false;
           }
         }
         break;
       }
       case LIGHT: {
         lightUp();
         // Reset
         compteur = 0;
         state = INIT;
         break;
       }
     }
   }
   return 0;
 }
