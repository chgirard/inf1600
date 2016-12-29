/*
 * Nom: TP3-Probleme_2.cpp
 * Copyright (C) 2016 Sebastien Chagnon et Sida (Eric) Li
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description:
 * Version: 1.0
 */


/**************************************************************************************
 * État présent * Interupteur * État Suivant *              Sortie PORTC              *
 **************************************************************************************
 *      A       *      0      *       A      *                   0x02                 *
 *      A       *      0      *       A      *                   0x02                 *
 *      B       *      0      *       C      * (compteur >> 8) % 8 == 0 ? 0x02 : 0x01 *
 *      B       *      0      *       C      * (compteur >> 8) % 8 == 0 ? 0x02 : 0x01 *
 *      C       *      0      *       D      *                   0x01                 *
 *      C       *      1      *       C      *                   0x01                 *
 *      D       *      0      *       E      *                   0x02                 *
 *      D       *      1      *       D      *                   0x02                 *
 *      E       *      0      *       F      *                   0x00                 *
 *      E       *      1      *       E      *                   0x00                 *
 *      F       *      0      *       A      *                   0x01                 *
 *      F       *      1      *       F      *                   0x01                 *
 **************************************************************************************/



#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>


/**
 * @brief isPushed Fonction anti-rebond de l'interrupteur
 * @return true si l'interrupteur est pesé, false sinon
 */
bool isPushed() {
  if ( !(PIND & 0x04) )
    return false;

  _delay_ms(10);

  return (PIND & 0x04) ? true : false;
}


/**
 * @brief isReleased Fonction verifiant si l'interrupteur n'est pas pesé
 * @return true si l'interrupteur n'est pas pesé, false sinon
 */
bool isReleased() {
  return (PIND & 0x04) ? false : true;
}


/**
 * @brief main Fonction principale du programme
 * @return 0 si tout s'est bien passé, le code d'erreur sinon
 */
int main()
{
  DDRA = 0x00; // PORT A est en mode entre
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entre

  enum Etats {A, B, C, D, E, F};

  Etats etat = A;
  unsigned long compteur = 0;

  PORTC = 0x02; // Lumiere rouge


  for(;;)  // boucle sans fin
  {

    switch(etat) {
      case A:
        PORTC = 0x02; // Lumiere rouge

        if ( isPushed() )
          etat = B;

	break;

      case B:
        PORTC = (compteur >> 8) % 8 == 0 ? 0x02 : 0x01; // Lumiere ambre

        if ( isReleased() )
          etat = C;

	break;

      case C:
        PORTC = 0x01; // Lumiere verte

        if ( isPushed() )
          etat = D;

	break;

      case D:
        PORTC = 0x02; // Lumiere rouge

        if ( isReleased() )
          etat = E;

	break;

      case E:
        PORTC = 0x00; // Lumiere éteinte
        if ( isPushed() )
          etat = F;

	break;

      case F:
        PORTC = 0x01; // Lumiere verte
        if ( isReleased() )
          etat = A;

	break;
    }

    compteur++;
  }

  return 0;
}
