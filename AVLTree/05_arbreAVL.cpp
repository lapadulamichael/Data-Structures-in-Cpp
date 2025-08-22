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
	ArbreAVL<int> arbre;
	arbre.vider();
	if(!arbre.vide()){
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	arbre.inserer(2);
	if(arbre.vide()){
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
		erreur++;
	}
	arbre.vider();
	if(!arbre.vide()){
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;
	}
	arbre.inserer(2);
	arbre.inserer(3);
	arbre.inserer(1);
	if(arbre.vide()){
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	arbre.vider();
	if(!arbre.vide()){
		std::cerr << RED << "ECHEC - V" << RESET << std::endl;
		erreur++;
	}
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
