#include <avr/io.h>

#include "CouleurDell.h"
#include "Direction.h"
#include "Roue.h"
#include "Prescaler.h"

/**
 * @brief Effectue un delais de 10 ms pour l'anti-rebond
 */
void debounce();

/**
 * @brief Verifie si le bouton est pese
 * @return true si le boutton est pese, false sinon
 */
bool isButtonPressed();

/**
 * @brief Verifie si le bouton n'est pese
 * @return true si le boutton n'est pas pese, false sinon
 */
bool isButtonReleased();

/**
 * @brief Change la couleur de la dell ea la couleur desiree
 * @param couleur Couleur desiree de la dell
 */
void setLight(lib::CouleurDell couleur);

/**
 * @brief Initialise les entrees et sorties des differents ports de la carte mère
 * @param portA Valeurs d'entree ou de sortie du port A
 * @param portB Valeurs d'entree ou de sortie du port B
 * @param portC Valeurs d'entree ou de sortie du port C
 * @param portD Valeurs d'entree ou de sortie du port D
 */
void initialisation(uint8_t portA, uint8_t portB, uint8_t portC, uint8_t portD);

/**
 * @brief Ajuste le PWM au ratio desire
 * @param ratio Valeur du ratio deeire
 * @param direction Sens de la rotation des roues deeire
 */
void ajusterPWM(uint8_t ratio, lib::Direction direction);

/**
 * @brief Ajuste le PWM au ratio desire
 * @param ratioRoueDroite Valeur du ratio de la roue droite desire
 * @param ratioRoueGauche Valeur du ratio de la roue gauche desire
 * @param direction Sens de la rotation des roues deeire
 */
void ajusterPWM(uint8_t ratioRoueGauche, uint8_t ratioRoueDroite, lib::Direction direction);

/**
 * @brief Ajuste le PWM au ratio desire
 * @param ratioRoueDroite Valeur du ratio de la roue droite desire
 * @param ratioRoueGauche Valeur du ratio de la roue gauche desire
 * @param directionRoueDroite Sens de la rotation de la roue droite deeire
 * @param directionRoueGauche Sens de la rotation de la roue gauche deeire
 */
void ajusterPWM(uint8_t ratioRoueGauche, uint8_t ratioRoueDroite, lib::Direction directionRoueGauche, lib::Direction directionRoueDroite);


/**
 * @brief Retire les interruptions en queue d'execution
 */
void clairInterruptions();

/**
 * @brief Ajuste le sens de rotation de la roue
 * @param roue Roue a laquelle apliquer le sens de la rotation
 * @param direction Sens de rotation de la roue
 */
void ajusterDirection(lib::Roue roue, lib::Direction direction);

/**
 * @brief Commence une minuterie qui fera des interruptions après un certain temps
 * @param ms Nombre de milisecondes de la minuterie
 */
void initialiserMinuterie(uint16_t ms);

/**
 * @brief Ajuste un compteur
 * @param duree Valeur de la comparaison avec le compteur pour lancer l'interruption
 */
void initialiserCompteur(uint16_t duree);

/**
 * @brief Ajuste un compteur
 * @param duree Valeur de la comparaison avec le compteur pour lancer l'interruption
 * @param prescaler Prescaler qui faut defenir au compteur
 */
void initialiserCompteur(uint16_t duree, lib::Prescaler prescaler);

/**
 * @brief Ajuste le prescaler du compteur
 * @param prescaler Prescaler qui faut defenir au compteur
 */
void definirPrescaler(lib::Prescaler prescaler);
