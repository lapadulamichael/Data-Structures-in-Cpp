/* 
 * Tests pour la classe ArbreAVL.
 * TP2 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 *
 */

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <malloc.h>
#include "arbreavl.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

std::string gen_random() {
    static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string tmp_s;
    tmp_s.reserve(512);

    for (int i = 0; i < 512; ++i) {
        tmp_s += alpha[rand() % (sizeof(alpha) - 1)];
    }
    return tmp_s;
}

int main() {
	int erreur = 0;
	ArbreAVL<std::string> tree;
	for(int i = 0; i < 100000; i++)
		tree.inserer(gen_random());
	if(tree.hauteur() != 20) {
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	struct mallinfo2 info;
	info = mallinfo2();
	size_t tas = info.uordblks;
	if(tas < 51200000) {
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
		erreur++;	
	}
	ArbreAVL<std::string> arbre = tree;
	info = mallinfo2();
	tas = info.uordblks;
	if(tas < 2 * 51200000) {
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;	
	}
	ArbreAVL<std::string>::Iterateur iter = arbre.debut();
	for(;iter; ++iter)
		tree.enlever(arbre[iter]);
	if(!tree.vide() || arbre.vide()) {
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	info = mallinfo2();
	size_t new_tas = info.uordblks;
	if(new_tas >= tas) {
		std::cerr << RED << "ECHEC - V" << RESET << std::endl;
		erreur++;	
	}
	arbre.vider();
	info = mallinfo2();
	tas = info.uordblks;
	if(tas >= 100000) {
		std::cerr << RED << "ECHEC - VI" << RESET << std::endl;
		erreur++;	
	}
	if(erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
