#include "Editeur.h"

using namespace std;

// Constructeur
Editeur::Editeur(string name, string codePostal, string adresse)
	: this->name(name), this->codePostal(codePostal), this->adresse(adresse);
{
}

// Destructeur
Editeur::~Editeur()
{
}


/*****************************Méthodes d'accès******************************/

// Accès au nom de l'éditeur.
string Editeur::getName(){
	return this->name;
}

// Accès au code postal de l'éditeur.
string Editeur::getCodePostal(){
	return this->codePostal;
}

// Accès à l'adresse de l'éditeur.
string Editeur::getAdresse(){
	return this->adresse;
}
