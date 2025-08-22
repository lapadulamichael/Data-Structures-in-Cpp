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
	for(int i = 1; i < 65536; i++)
		arbre.inserer(i);
	if(arbre.hauteur() != 16) {
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	ArbreAVL<int>::Iterateur iter = arbre.debut();	
	int i = 1, old_erreur = erreur;
	for(; iter; ++iter) {
		if(arbre[iter] != i)
			erreur++;
		i++;
	}
	if(erreur != 0)
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
	ArbreAVL<int>::Iterateur reti(arbre);	
	for(int i = 1; i < 65536; i++)
		arbre.inserer(i + 65536);
	i = 1;
	old_erreur = erreur;
	for(; reti; reti++) {
		if(arbre[reti] != i)
			erreur++;
		i++;
	}
	if(erreur != old_erreur)
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
	if(i > 65536) {
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
