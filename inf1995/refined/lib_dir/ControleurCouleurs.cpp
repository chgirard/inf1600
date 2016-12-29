#include "ControleurCouleurs.h"
#include "Sound.h"

/////////////////////////////////
// s0 | s1 : min/typ
//  0 |  0 : --Power down--
//  0 |  1 :  10/12  kHz
//  1 |  0 : 100/120 kHz
//  1 |  1 : 500/600 kHz
/////////////////////////////////
// s2 | s3 : filtre
//  0 |  0 : rouge
//  0 |  1 : bleu
//  1 |  0 : --aucun--
//  1 |  1 : vert
/////////////////////////////////
// couleur
// eteint : 0
// rouge  : 1
// vert   : 2
// bleu   : 3
/////////////////////////////////

//////////////////-CONST & DEST-/////////////////////////
ControleurCouleurs::ControleurCouleurs(int suiteFormes[] /*, int facteur*/)
	:filtre_(BLANC), couleur_(BLANC), suiteFormes_(suiteFormes) /*, facteur_(facteur)*/
{
	for (uint8_t i = 0; i < 3; i++){
		suiteCouleurs_[i] = BLANC;
	}
	appliquerFiltre();
}

ControleurCouleurs::~ControleurCouleurs()
{
}
//////////////////////////////////////////////////////
////////////////-MÉTHODES D'ACCÈS-////////////////////

int ControleurCouleurs::obtenirCouleur() const{
	return couleur_;
}

int ControleurCouleurs::obtenirFiltre() const{
	return filtre_;
}

//////////////////////////////////////////////////////
////////////-MÉTHODES DE MODIFICATION-////////////////

void ControleurCouleurs::incrementerFiltre(){
	if (filtre_ == BLEU){
		filtre_ = BLANC;
	}
	else {
		filtre_++;
	}
	appliquerFiltre();
}

void ControleurCouleurs::appliquerFiltre(){
	// On change s2 et s3 du capteur de couleurs en fonction du nouveau filtre.
	switch (filtre_){
	case ROUGE:
		PORTC &= ~(1 << 2); // s2 = 0
		PORTC &= ~(1 << 3); // s3 = 0
		break;
	case VERT:
		PORTC |=  (1 << 2); // s2 = 1
		PORTC |=  (1 << 3); // s3 = 1
		break;
	case BLEU:
		PORTC &= ~(1 << 2); // s2 = 0
		PORTC |=  (1 << 3); // s3 = 1
		break;
	case BLANC:
		PORTC |=  (1 << 2); // s2 = 1
		PORTC &= ~(1 << 3); // s3 = 0
		break;
	default:
		break;
	}
}


void ControleurCouleurs::gererCouleurs(){
	if (couleur_ != filtre_){ // Si la couleur présente est différente de la dernière.
		// Vide le tableau si on est sur du blanc.
		if (tampon_ > 200) {
			if (filtre_ == BLANC){
				PORTB &= ~(1 << 0); // Tout
				PORTB &= ~(1 << 1); // est
				soundOff();         // éteint.

				suiteCouleurs_[2] = BLANC;
				suiteCouleurs_[1] = BLANC;
				suiteCouleurs_[0] = BLANC;
			}
			// Sinon push la nouvelle couleur dans le tableau.
			// [couleur]2 <- [couleur]1 <- [couleur]0 <- nouvelle_couleur
			else {
				switch (filtre_){
				case ROUGE:
					PORTB |=  (1 << 0); // On allume la DEL en rouge.
					PORTB &= ~(1 << 1); //
					soundOff();         //
				break;
				case VERT:
					PORTB &= ~(1 << 0); //
					PORTB |=  (1 << 1); // On allume la DEL en vert
					soundOff();         //
				break;
				case BLEU:
					PORTB &= ~(1 << 0); //
					PORTB &= ~(1 << 1); //
					soundOn(50);        // On émet un son aigu
				break;
				}
				suiteCouleurs_[2] = suiteCouleurs_[1];
				suiteCouleurs_[1] = suiteCouleurs_[0];
				suiteCouleurs_[0] = filtre_;
			}
			couleur_ = filtre_;
			tampon_ = 0;
		}
		else {
			tampon_++;
		}
	}
}
//////////////////////////////////////////////////////

// Compare si la suite de couleurs correspond à celle des formes
// et met estFini à vrai au si c'est le cas.
bool ControleurCouleurs::comparerSuites() const{
	// Si une paire couleur-forme diffère, on revoit faux.
	for (uint8_t i = 0; i < 3; i++){
		if (suiteCouleurs_[i] != suiteFormes_[i]){
			return false;
		}
	}
	// Si toutes les paires couleur-formes sont égales, on renvoit vrai.
	return true;
}

void ControleurCouleurs::detecterCouleur(uint8_t nCycles){
	// On détermine la couleur en fonction du filtre appliqué.
	// La couleur sera mise à jour une fois aux 4 cycles.
	switch (filtre_){
	case ROUGE:
		// Si rouge détecté :
		if (20 < nCycles && nCycles < 36){ //en f() de facteur_ ??????????????????????????????
			gererCouleurs();
		}
		break;
	case VERT:
		// Si vert détecté :
		if (10 < nCycles && nCycles < 30){ //en f() de facteur_ ??????????????????????????????
			gererCouleurs();
		}
		break;
	case BLEU:
		// Si bleu détecté :
		if (15 < nCycles && nCycles < 30){ //en f() de facteur_ ??????????????????????????????
			gererCouleurs();
		}
		break;
	case BLANC:
		// Si blanc détecté :
		if (100 < nCycles){                //en f() de facteur_ ??????????????????????????????
			gererCouleurs();
		}
		break;
	default:
		break;
	}
	incrementerFiltre();
}
