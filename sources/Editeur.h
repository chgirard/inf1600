#ifndef EDITEUR_H
#define EDITEUR_H

#include <string>

using namespace std;

class Editeur{
public:
	Editeur(string, string, string);
	~Editeur();

	string getName();
	string getCodePostal();
	string getAdresse();
private:
	string name;
	string codePostal;
	string adresse;
};

#endif // EDITEUR_H
