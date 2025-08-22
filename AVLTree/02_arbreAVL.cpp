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
	for(int i = 0; i < 10; i += 2)
		arbre.inserer(i);
	for(int i = 0; i < 10; i += 2)
		if(!arbre.contient(i)){
			std::cerr << RED << "ECHEC - I (" << i << ")" << RESET << std::endl;
			erreur++;
		}
	for(int i = 1; i < 10; i += 2)
		if(arbre.contient(i)){
			std::cerr << RED << "ECHEC - II (" << i << ")" << RESET << std::endl;
			erreur++;
		}
	for(int i = 1; i < 10; i += 2)
		arbre.inserer(i);

	for(int i = 0; i < 10; i++)
		if(!arbre.contient(i)){
			std::cerr << RED << "ECHEC - III (" << i << ")" << RESET << std::endl;
			erreur++;
		}
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
