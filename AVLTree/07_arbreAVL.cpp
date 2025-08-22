/* 
 * Tests pour la classe ArbreAVL.
 * TP2 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 *
 */

#include <iostream>
#include "arbreavl.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

int main() {
	int erreur = 0;
	ArbreAVL<int> arbre1;
	for(int i = 0; i < 20; i++)
		arbre1.inserer(i);
	ArbreAVL<int> arbre2;
	arbre2 = arbre1;
	for(int i = 0; i < 20; i++)
		if(!arbre2.contient(i)) {
			std::cerr << RED << "ECHEC - I" << RESET << std::endl;
			erreur++;
		}
	ArbreAVL<int> arbre3;
	arbre2 = arbre3;
	for(int i = 0; i < 20; i++)
		if(arbre2.contient(i)) {
			std::cerr << RED << "ECHEC - II" << RESET << std::endl;
			erreur++;
		}
	arbre1 = arbre1;
	if(arbre1.vide()) {
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;
	}
	for(int i = 0; i < 20; i++)
	if(!arbre1.contient(i)){
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
