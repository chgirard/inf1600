#include "Article.h"

#include <fstream>
#include <iostream>

// Constructeur
Article::Article (string name, string auteur, Editeur* editeur) {
    // Article information
    this->name = name;
    this->auteur = auteur;

    // Editeur information
    this->editeur = editeur;
}

// Setters
void Article::setName(string name) {
    this->name = name;
}
void Article::setAuteur(string auteur) {
    this->auteur = auteur;
}

// Associer un editeur à l'article
void Article::associerEditeur (Editeur* editeur) {
    this->editeur = editeur;
}

// Getters
string Article::getName() {
    return this->name;
}
string Article::getAuteur() {
    return this->auteur;
}

Editeur* Article::getEditeur(){
	return this->editeur;
}

// Enregistrer l'article dans un fichier
void Article::saveArticle (string fileName) {

    ofstream outfile (fileName.c_str(), std::ofstream::binary);

    // allocate memory for file content
    int size = (this->name + ","
                + this->auteur + ","
                + this->editeur->getName() + ","
                + this->editeur->getCodePostal() + ","
                + this->editeur->getAdresse() + "\n" ).length();

    // write to outfile
    outfile.write ((this->name + ","
                   + this->auteur + ","
                   + this->editeur->getName() + ","
                   + this->editeur->getCodePostal() + ","
                   + this->editeur->getAdresse() + "\n").c_str(),size);


    outfile.close();
}

// Trouver un article avec son nom dans la base de données DB
Article* Article::trouverArticle (string DB, string name) {

    ifstream fichier(DB.c_str(), ios::in); // Ouvrir le fichier "DB.txt"

    if (fichier)
    {
        string line;
        // Lire les articles, un article par ligne dans la base de données (DB.txt)
        while (getline(fichier, line)) {
            string nameDB;
            // Récupérer le nom de l'article
            int i = 0;
            for (i = 0 ; i < line.length() ; i++) {
                if (line[i] != ',') {
                    nameDB += line[i];
                } else {
                    break;
                }
            }


            // Si l'article qu'on lit actuellement est celui qu'on cherche
            if (nameDB == name) {

                // Récupérer le nom de l'auteur
                string auteurDB;
                for (i = i + 1; i < line.length() ; i++) {
                    if (line[i] != ',') {
                        auteurDB += line[i];
                    } else {
                        break;
                    }
                }

                //  Récupérer le nom de l'éditeur
                string editeurNameDB;
                for (i = i + 1; i < line.length() ; i++) {
                    if (line[i] != ',') {
                        editeurNameDB += line[i];
                    } else {
                        break;
                    }
                }

                // Récupérer le code postale de l'éditeur
                string editeurCodePostalDB;
                for (i = i + 1; i < line.length() ; i++) {
                    if (line[i] != ',') {
                        editeurCodePostalDB += line[i];
                    } else {
                        break;
                    }
                }

                // Récupérer l'addresse de l'éditeur
                string editeurAddressDB;
                for (i = i + 1; i < line.length() ; i++) {
                    if (line[i] != ',') {
                        editeurAddressDB += line[i];
                    } else {
                        break;
                    }
                }

				//On crée l'éditeur en fonction des informations trouvées;
				Editeur editeur(editeurNameDB, editeurCodePostalDB, editeurAddressDB);
                // Créer un objet de type article avec les informations récupérées
                Article *a = new Article(nameDB, auteurDB, &editeur);
                // Fermer la base de données
                fichier.close();
                // Retourner l'article sélectionné
                return a;
            }
        }
        // Fermer la base de données
        fichier.close();
    }
    // Si l'article est innexistant, on retourne NULL
    return NULL;

}

// Afficher l'article
void Article::afficher() {
    std::cout << "Name : "                 << this->name                     << std::endl;
    std::cout << "Autheur : "              << this->auteur                   << std::endl;
    std::cout << "Editeur name : "         << this->editeur->getName()       << std::endl;
    std::cout << "Editeur code postale : " << this->editeur->getCodePostal() << std::endl;
    std::cout << "Editeur address : "      << this->editeur->getAdresse()    << std::endl;
}
