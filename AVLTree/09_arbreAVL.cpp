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

int compteurAcomparaisons = 0;
class A {
  private:
    int x;
  public:
    A(int x_ = 0) : x(x_) {}
    bool operator < (const A & o) const {
       compteurAcomparaisons++;
       return x < o.x;
    }
    bool operator <= (const A & o) const {
       compteurAcomparaisons++;
       return x <= o.x;
    }
    bool operator == (const A & o) const {
       compteurAcomparaisons++;
       return x == o.x;
    }
    bool operator != (const A & o) const {
       compteurAcomparaisons++;
       return x != o.x;
    }
    bool operator >= (const A & o) const {
       compteurAcomparaisons++;
       return x >= o.x;
    }
    bool operator > (const A & o) const {
       compteurAcomparaisons++;
       return x > o.x;
    }
};


int main() {
	int erreur = 0;
	ArbreAVL<A> tree;
	for(int i = 0; i < 131072; i++)
		tree.inserer(i);
	for(int i = 0; i < 131072; i += 2) {
		compteurAcomparaisons = 0;
		tree.contient(A(i));
		if(compteurAcomparaisons > tree.hauteur() * 2)
			erreur++;
	}
	if(erreur != 0)
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
	int old_erreur = erreur;
	for(int i = 0; i < 131072; i += 2) {
		compteurAcomparaisons = 0;
		tree.enlever(A(i));
		if(compteurAcomparaisons > tree.hauteur() * 2)
			erreur++;
	}
	if(erreur != old_erreur)
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
	old_erreur = erreur;
	for(int i = 0; i < 131072; i++) {
		compteurAcomparaisons = 0;
		tree.inserer(i + 131072);
		if(compteurAcomparaisons > tree.hauteur() * 2)
			erreur++;
	}
	if(erreur != old_erreur)
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
