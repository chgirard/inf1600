#include <iostream>
#include "Article.h"
#include "Editeur.h"

using namespace std;

/*
 * fonction principale
 */
int main(int argc, char** argv) {

    Article* article = new Article(); // Création d'un article

    string DBFile = "DB.txt"; // Fichier qui contient une base des articles
    int operation ; // Opération séléctionnée par l'utilisateur

    do {
        // Afficher les opérations possibles
        std::cout << std::endl << "--------------------------------------" << std::endl;

        std::cout << "0 - Quitter le programme " << std::endl;
        std::cout << "1 - Créer un article " << std::endl;
        std::cout << "2 - Trouver un article " << std::endl;
        std::cout << "3 - Afficher un article " << std::endl;
        std::cout << "4 - Enregistrer l'article " << std::endl;
        std::cout << "--------------------------------------" << std::endl;

        // Lire le choi d'utilisateur
        std::cin >> operation;

        switch (operation) {
            case 1:
            {
                // Informations du nouvel article
                string name;
                string auteur;
                string editeurName;
                string editeurCodePostal;
                string editeurAddress;

                // Demander l'utilisateur de saisir les informatins du nouvel article
                std::cout << "Saisir le nom de l'article : " ;
                std::cin >> name;

                std::cout << "Saisir l'auteur de l'article : " ;
                std::cin >> auteur;

                std::cout << "Saisir le nom de l'editeur : " ;
                std::cin >> editeurName;

                std::cout << "Saisir le code postale de l'editeur : " ;
                std::cin >> editeurCodePostal;

                std::cout << "Saisir l'addresse de l'editeur : " ;
                std::cin >> editeurAddress;

                // Créer un nouvel article
                delete article;

				// Créer un nouvel éditeur.
				Editeur editeur(editeurName, editeurCodePostal, editeurAddress);

                article = new Article (name, auteur, &editeur);

                break;
            }
            case 2:
            {
                // Demander l'utilisateur de saisir le nom d'article à chercher dans la base de données
                string name;
                std::cout << "Saisir le nom de l'article : " ;
                std::cin >> name;

                // Chercher l'article
                Article* tmp = article->trouverArticle(DBFile, name);

                if (tmp != NULL) {
                    // Si l'article est trouvé
                    article = tmp;
                } else {
                    std::cout << "Aucun article trouvé !" << std::endl;
                }

                break;
            }
            case 3:
            {
                // Afficher l'article
                if (article != NULL) {
                    article->afficher();
                } else {
                    std::cout << "Aucun article séléctionné" << std::endl;
                }
                break;
            }
            case 4:
            {
                // Enregistrer l'article dans la base de données.
                if (article != NULL) {
                    article->saveArticle(DBFile);
                    std::cout << "Article enregistré !" << std::endl;
                }
            }
        }


    } while (operation != 0); // Tant que l'utilisateur ne décide pas de quitter le programmme

    return 0;
}
