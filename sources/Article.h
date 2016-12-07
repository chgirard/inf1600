#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include "Editeur.h"

using namespace std;

// Cette classe représente un article
class Article {
public:
    // Constructeurs
    Article () {}
    Article(string, string, Editeur*);

    // Setters
    void setName(string);
    void setAuteur(string);

    void associerEditeur (Editeur*);

    // Getters
    string getName();
    string getAuteur();

	Editeur* getEditeur();

    // Enregistrer l'article
    void saveArticle(string);
    // Afficher l'article
    void afficher();
    // Chercher un article dans une base de données par nom
    Article* trouverArticle(string, string);

private:
    // Information sur l'article
    string name;
    string auteur;

    // Pointeur vers l'éditeur de l'article;
	Editeur* editeur;

};

#endif
