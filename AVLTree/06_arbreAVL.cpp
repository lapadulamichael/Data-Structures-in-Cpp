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
	for(int i = 0; i < 131072; i++)
		arbre.inserer(i);
	if(arbre.hauteur() != 18){
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	int taille = 0;
	for(ArbreAVL<int>::Iterateur iter = arbre.debut(); iter; ++iter)
		taille++;
	if(taille != 131072) {
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
		erreur++;
	}
	for(int i = 1; i < 131072; i += 2)
		arbre.enlever(i);
	if(arbre.hauteur() != 17){
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;
	}
	ArbreAVL<int>::Iterateur exac = arbre.rechercher(100000);
	ArbreAVL<int>::Iterateur suiv = arbre.rechercherEgalOuSuivant(100000);
	ArbreAVL<int>::Iterateur prec = arbre.rechercherEgalOuPrecedent(100000);
	if(exac != suiv || suiv != prec || prec != exac) {
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	int old_erreur = erreur;
	for(int i = 2; i < 131072; i += 2) {
		suiv = arbre.rechercherEgalOuSuivant(i - 1);
		prec = arbre.rechercherEgalOuPrecedent(i - 1);
		if(arbre[suiv] != i || arbre[prec] != i - 2)
			erreur++;
	}	
	if(old_erreur != erreur)
		std::cerr << RED << "ECHEC - V" << RESET << std::endl;
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
