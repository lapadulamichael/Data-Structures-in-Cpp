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

int nbMinAVL(int h){
	if(h == 0) 
		return 0;
	if(h == 1) 
		return 1;
	return 1 + nbMinAVL(h - 2) + nbMinAVL(h - 1);
}

int main() {
	int erreur=0;
	ArbreAVL<int> arbre;
	for(int n = 1; n <= 1000; n++) {
		arbre.inserer(n);
		int h = arbre.hauteur();
		int nbmin = nbMinAVL(h);
		if(n < nbmin) {
			std::cerr << RED << "ECHEC - I (" << n << ")" << RESET << std::endl;
			erreur++;
		}
	}

	ArbreAVL<int> arbre2;
	for(int n = 1; n <= 1000; n++) {
		arbre2.inserer(-n);
		int h = arbre2.hauteur();
		int nbmin = nbMinAVL(h);
		if(n < nbmin){
			std::cerr << RED << "ECHEC - II (" << n << ")" << RESET << std::endl;
			erreur++;
		}
	}
	if(erreur == 0)
	std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
