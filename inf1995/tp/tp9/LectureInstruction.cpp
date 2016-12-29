
#define F_CPU 8000000L

#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>

#include "Memoire24CXXX.h"
#include "lib_dir/Librairie.h"
#include "lib_dir/Direction.h"
#include "lib_dir/CouleurDell.h"
#include "lib_dir/Roue.h"
#include "lib_dir/Prescaler.h"

volatile uint8_t counter = 0;
volatile bool dataInput = false;

ISR(TIMER0_COMPA_vect){
  // Creation d'un onde carré pour faire du son
  if (counter == 0) {
    counter = 1;
    PORTB |= (1 << 0);
    PORTB &= ~(1 << 1);
  } else {
    counter = 0;
    PORTB |= (1 << 1);
    PORTB &= ~(1 << 0);
  }
}

ISR(TIMER1_COMPA_vect){
  counter++;
}

ISR(INT0_vect){
  if (isButtonPressed())
  {
    dataInput = true;
  }
  clairInterruptions();
}

int main()
{
  initialisation(0x00, 0xff, 0xff, 0xf0);
  Memoire24CXXX memoire;

/*
  soundOn(64);
  _delay_ms(300);
  soundOn(64);
  _delay_ms(300);
  soundOn(65);
  _delay_ms(300);
  soundOn(67);
  _delay_ms(300);
  soundOn(67);
  _delay_ms(300);
  soundOn(65);
  _delay_ms(300);
  soundOn(64);
  _delay_ms(300);
  soundOn(62);
  _delay_ms(300);
  soundOn(60);
  _delay_ms(300);
  soundOn(60);
  _delay_ms(300);
  soundOn(62);
  _delay_ms(300);
  soundOn(64);
  _delay_ms(300);
  soundOn(64);
  _delay_ms(450);
  soundOn(62);
  _delay_ms(150);
  soundOn(62);
  _delay_ms(600);
  soundOff();cpu cpu to
  _delay_ms(300);


    soundOn(64);
    _delay_ms(300);
    soundOn(64);
    _delay_ms(300);
    soundOn(65);
    _delay_ms(300);
    soundOn(67);
    _delay_ms(300);
    soundOn(67);
    _delay_ms(300);
    soundOn(65);
    _delay_ms(300);
    soundOn(64);
    _delay_ms(300);
    soundOn(62);
    _delay_ms(300);
    soundOn(60);
    _delay_ms(300);
    soundOn(60);
    _delay_ms(300);
    soundOn(62);
    _delay_ms(300);
    soundOn(64);
    _delay_ms(300);
    soundOn(62);
    _delay_ms(450);
    soundOn(60);
    _delay_ms(150);
    soundOn(60);
    _delay_ms(600);
    soundOff();
    _delay_ms(300);


      soundOn(62);
      _delay_ms(300);
      soundOn(62);
      _delay_ms(300);
      soundOn(64);
      _delay_ms(300);
      soundOn(60);
      _delay_ms(300);
      soundOn(62);
      _delay_ms(300);
      soundOn(64);
      _delay_ms(150);
      soucpu tondOn(65);
      _delay_ms(150);
      soundOn(64);
      _delay_ms(300);
      soundOn(60);
      _delay_ms(300);
      soundOn(62);
      _delay_ms(300);
      soundOn(64);
      _delay_ms(150);
      soundOn(65);
      _delay_ms(150);
      soundOn(64);
      _delay_ms(300);
      soundOn(62);
      _delay_ms(300);
      soundOn(60);
      _delay_ms(300);
      soundOn(62);
      _delay_ms(300);
      soundOn(55);
      _delay_ms(600);
      soundOff();
      _delay_ms(300);


        soundOn(64);
        _delay_ms(300);
        soundOn(64);
        _delay_ms(300);
        soundOn(65);
        _delay_ms(300);
        soundOn(67);
        _delay_ms(300);
        soundOn(67);
        _delay_ms(300);
        soundOn(65);
        _delay_ms(300);
        soundOn(64);
        _delay_ms(300);
        soundOn(62);
        _delay_ms(300);
        soundOn(60);
        _delay_ms(300);
        soundOn(60);
        _delay_ms(300);
        soundOn(62);
        _delay_ms(300);
        soundOn(64);
        _delay_ms(300);
        soundOn(62);
        _delay_ms(450);
        soundOn(60);
        _delay_ms(150);
        soundOn(60);
        _delay_ms(600);
        soundOff();
*/
/*
  while (1) {
    switch (counter % 2) {
      case 0:
        //setLight(lib::CouleurDell_Vert);
      break;
      case 1:
        //setLight(lib::CouleurDell_Rouge);
      break;
    }
  }  soundOff();

*/

  initialiserMinuterie(100);
  while (counter < 30) {
    if (counter % 2 == 0)
    {
        setLight(lib::CouleurDell_Vert);
    }
    else
    {
        setLight(lib::CouleurDell_Rouge);
    }
  }
  arreterMinuterie();
  setLight(lib::CouleurDell_Eteint);

  if (dataInput) {
    setLight(lib::CouleurDell_Vert);
    uint16_t vector = 0;
    while (1) {
      unsigned char data;
      while ((UCSR0A & 0x80) == 0x00); // Wait for till the data arrives data
      // USART Receive Complete. Set when data is available and the data register has not be read yet. Donc, quand == 0x00 le data est arrivé.
      data=UDR0;	// Read the data from UDR, as soon as the data arrives
      memoire.ecriture(vector++, data);
    }
  }

  uint16_t sizeofFichier = 0;
  {
    uint8_t lecture[2];
    memoire.lecture(0x0000, lecture, 0x02);
    sizeofFichier |= (lecture[1] | ((0xffff & lecture[0]) << 8));
  }

  {
    uint8_t data[100];
    memoire.lecture(0x0000, data, 100);
    uint16_t i;
    for (i = 0; i < sizeofFichier; i++)
      transmissionUART(data[i]);
  }

  uint8_t instructionNumber = 1;

  uint16_t loopLocation = 0;
  uint8_t loopCompteur = 0;

  bool ended = false;
  bool started = false;
  while ((!ended) && (instructionNumber <= (sizeofFichier - 2) / 2)) {


    uint8_t currentInstruction;
    memoire.lecture(0x0002 * instructionNumber, &currentInstruction, 0x01);

    transmissionUART(instructionNumber);

    if (!started)
    {
      instructionNumber++;
      if (currentInstruction == 0x01)
      {
        //Indique le début du code. Le programme commence ici (et pas avant).
        started = !started;
      }
    }
    else
    {
      uint8_t operande;
      memoire.lecture((0x0002 * instructionNumber++) + 0x0001, &operande, 0x01);

      transmissionUART(currentInstruction);
      transmissionUART(operande);

      switch (currentInstruction){
        case 0x02:
        //attendre 25 ms fois la valeur de l'opérande
        for (int i = 0; i < operande; i++)
          _delay_ms(25);
        break;

        case 0x44:
        //allumer les DEL dont les bits correspondants de l'opérande sont à un.
        //Si une seule DEL est utilisée, l'opérande est ignoré (mais présent).
        setLight(lib::CouleurDell_Vert);
        break;

        case 0x45:
        //éteindre les DEL dont les bits correspondants de l'opérande sont à un.
        //Si une seule DEL est utilisée, l'opérande est ignoré (mais présent).
        setLight(lib::CouleurDell_Eteint);
        break;

        case 0x48:
        //jouer une sonorité du tableau 3. Il faut activer une sortie en mode
        //PWM avec la fréquence donnée dans le tableau. Si la valeur n'est pas
        //dans le tableau, la commande est ignorée.
        soundOn(operande);
        break;

        case 0x09:
        //arrêter de jouer la sonorité en cours (s'il y en a une qui joue).
        soundOff();
        break;

        case 0x60:
        case 0x61:
        //arrêter les deux moteurs
        arreterPWM();
        break;

        case 0x62:
        //avancer en ligne droite à une vitesse donnée par (opérande / 255 * 100%)
        ajusterPWM(operande, lib::Direction_Avancer);
        break;

        case 0x63:
        //reculer en ligne droite à la vitesse (opérande / 255 * 100%)
        ajusterPWM(operande, lib::Direction_Reculer);
        break;

        case 0x64:
        //virage du robot de 90 degrés à droite
        ajusterPWM(0xff, 0xff, lib::Direction_Avancer, lib::Direction_Reculer);
        _delay_ms(2000);
        arreterPWM();
        break;

        case 0x65:
        //virage du robot de 90 degrés à gauche
        ajusterPWM(0xff, 0xff, lib::Direction_Reculer, lib::Direction_Avancer);
        _delay_ms(2000);
        arreterPWM();
        break;

        case 0xc0:
        //emmagasiner l'adresse du présent point d'exécution du code dans une
        //variable pour pouvoir y revenir. De plus, créer une variable qui
        //conservera l'état du compteur de boucle. La boucle s'exécutera une
        //fois de plus que la valeur précisée par l'opérande. Donc, si
        //l'opérande est zéro, le code ne s'exécutera qu'une seule fois. Il ne
        //peut y avoir deux boucles imbriquées (actives au même moment).
        loopLocation = instructionNumber;
        loopCompteur = operande;
        break;

        case 0xc1:
        //si le compteur n'est pas égal à 0, retourner à l'adresse de début de
        //boucle et décrémenter le compteur de boucle. Sinon, ne rien faire.
        if (loopCompteur != 0x00)
        {
          instructionNumber = loopLocation;
          loopCompteur--;
        }
        break;

        case 0xff:
        //fin de l'exécution du code. Le code qui suit cette instruction sera
        //ignoré. Aucun son ne sera émis après cette instruction et le robot
        //s'arrêtera également.
        ended = !ended;
        //arretermusique
        arreterPWM();
        setLight(lib::CouleurDell_Eteint);
        break;
      }
    }

  }


  while(1) {

  }

  return 0;
}
