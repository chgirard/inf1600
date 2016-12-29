#ifndef CONTROLEUR_COULEURS_H
#define CONTROLEUR_COULEURS_H

#include<avr/io.h>

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

// Ces couleurs valent respectivement
//      0,    1,     2,    3
enum couleur{
	BLANC, ROUGE, VERT, BLEU
};

class ControleurCouleurs {

public:

	/*
	 *  Constructeur du contrôleur de couleurs.
	 * \param [in] suiteFormes  La suite des formes enregistrée par le robot
	 *                          et qui doit correspondre à celle des couleurs.
	 */
	ControleurCouleurs(int suiteFormes[]);

	/*
	 *  Destructeur du contrôleur de couleurs.
	 */
	~ControleurCouleurs();

	/*
	 *  Accès à la couleur pointée.
	 * \return Ladite couleur.
	 */
	int obtenirCouleur() const;

	/*
	 *  Accès au filtre.
	 * \return Ledit filtre.
	 */
	int obtenirFiltre() const;

	/*
	 *  Applique le filtre sur le capteur de couleurs en chageant s2 et s3.
	 * \return void
	 */
 	void appliquerFiltre();

	/*
	 *  Fonction qui est appelée à tous les 5ms et qui gère les couleurs
	 * \return void
	 */
	void detecterCouleur(uint8_t nCycles);

	/*
	 *  Compare si la suite de couleurs correspond à celle des formes.
	 * \return Si les suites correspondent.
	 */
	bool comparerSuites() const;

	/*
	 *  Incrémente le nombre de cycles.
	 * \return void
	 */
	void incrementerFiltre();
	
	int tampon_;/////////////////////////////////

private:
	// Attributs : ///////////////////////////////////////////////////////////////
//	int facteur_;
	int filtre_;  // Filtre sur le capteur.
	int couleur_; // Dernière couleur détectée.
	 // Permet d'ignorer les fausses détections 
	             // lorsque le capteur passe au-dessus du papier collant.
	int suiteCouleurs_[3];
	int* suiteFormes_;

	// Fonctions privées : ///////////////////////////////////////////////////////
	/*
	 *  Push la nouvelle couleur détectée dans le tableau
	 * \return void
	 */
	void gererCouleurs(); //TODO description à compléter.
};


#endif // CONTROLEUR_COULEURS_H
