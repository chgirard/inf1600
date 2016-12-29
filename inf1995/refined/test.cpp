#include "lib_dir/Settings.h"
#include "lib_dir/Util.h"
#include "lib_dir/Minuterie.h"
#include "lib_dir/PulseWidthModulation.h"
#include "lib_dir/Dell.h"
#include "lib_dir/ControleurCouleurs.h"
#include "SuiveurDeLigne.h"

volatile bool tick = false;
volatile uint8_t nCycles = 0;


int suiteFormes[3] = {BLEU, VERT, ROUGE};


ISR(TIMER1_COMPA_vect){
	tick = true;
}

ISR(INT0_vect){
	nCycles++;
}

int main()
{
	initialisation();
	_delay_ms(1000);

	initialiserMinuterie(5);
//	uint8_t pieceNo = 0;
//	uint16_t i = 300;

	// TEST
	ControleurCouleurs controleurCouleurs(suiteFormes);

//	uint8_t compteur = 0;
//	uint8_t facteur = 0;

//	PORTC &= ~(1 << 2); // s2 = 0
//	PORTC |=  (1 << 3); // s3 = 1
//	PORTC &= ~(1 << 3); // s2 = 0
//	PORTC |=  (1 << 2); // s3 = 1

	while (!controleurCouleurs.comparerSuites()){
		if (tick){


	/*		if (compteur < 20){
				//setFacteur();
				facteur = nCycles;
				transmissionUART(facteur);
				compteur++;
			}*/
			tick = false;
			transmissionUART(controleurCouleurs.tampon_);
		//	transmissionUART(nCycles);
			controleurCouleurs.detecterCouleur(nCycles);
			nCycles = 0;
		}
	}


















	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB |= (1 << 0);  // On allume la DEL en rouge.
	PORTB &= ~(1 << 1); //
	_delay_ms(250);
	PORTB &= ~(1 << 0); //
	PORTB |= (1 << 1);  // On allume la DEL en vert
	_delay_ms(250);
	PORTB &= ~(1 << 1); //

	return 0;
}
