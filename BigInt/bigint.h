/** 
 * Squelette pour la classe Bint.
 * TP1 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes (Hiver 2025)
 * 
 *
 * IDENTIFICATION.
 *
 * 	Nom et prénom : Lapadula Michael
 * 	Code permanent : LAPM67010405
 * 
 */


#ifndef __BINT_H__
#define __BINT_H__

#include "tableau.h"
#include <iostream>
// Vous devez utiliser les assertions pour vérifier les conditions
// de base de transformation des chiffres.
#include <assert.h>
#include <iterator>
#include <ratio>

using namespace std;

class Bint {
	/**************** Interface publique ****************
	* 
	* Vous ne devez pas ajouter de nouvelles fonctions 
	* publiques ni modifier les fonctions déjà présentes
	* (ne pas modifier la signature ni la valeur retournée).
	*
	*****************************************************/
	public:	
		/************ Constructeurs et destructeur ************/
		// Constructeurs par défaut
		Bint();
		Bint(long long n);
		Bint(const string & s);
		// Constructeur par copie
		Bint(const Bint & bigA);
		// Constructeur par déplacement
		Bint(const Bint && bigA);
		// Destructeur
		~Bint();
		/******************************************************/
 

		/*************** Fonctions utilitaires ****************/
		int taille() const;
		/******************************************************/


		/********************* Opérateurs *********************/
		// Opérateurs de comparaison
		bool operator < (const Bint & bigA) const;
		bool operator > (const Bint & bigA) const;
		bool operator >= (const Bint & bigA) const;
		bool operator <= (const Bint & bigA) const;
		bool operator == (const Bint & bigA) const;
		bool operator != (const Bint & bigA) const;
		
		// Opérateur d'affectation par copie
		Bint & operator = (const Bint & bigA);
		Bint & operator = (const string & s);
		// Opérateur d'affectation par dépalcement
		Bint & operator = (const Bint && bigA);
		Bint & operator = (const string && s);

		// Opérateurs arithmétiques
		Bint & operator += (const Bint & bigA);
		Bint operator + (const Bint & bigA) const;
		Bint & operator *= (const Bint & bigA);
		Bint operator * (const Bint & bigA) const;

		// Opérateurs de lecture et d'écriture
		friend ostream & operator << (ostream & os, const Bint & bigA);		
		friend istream & operator >> (istream & is, Bint & bigA);
		/******************************************************/
	/**************** Représentation ********************
	* 
	* Représentation interne de la classe Bint.
	* Vous n'avez pas le droit de la modifier ni d'y ajouter 
	* des variables/attributs.
	*
	*****************************************************/
	private:
    		Tableau<int> bigint;

		/**************** Interface privée ******************
		* 
		* Vous pouvez ajouter toutes les fonctions privées
		* que vous estimez nécessaire.
		* N'oubliez pas de bien commenter vos fonctions, de 
		* bien utilisez le mot-clé const et de prendre en 
		* considération les bonnes pratiques.
		*
		*****************************************************/
};

/*************** Fonctions publiques ****************/

Bint::Bint() {
}

Bint::Bint(long long n) {
	assert(n >= 0);
	long long digits;
	// traite le cas 0
	if (n == 0) {
		bigint.ajouter(n);
	}
	// ajouter en blocs de 9 digits
	while (n > 0) {
		digits = n%1000000000;
		bigint.ajouter(digits);
		n /=1000000000;
	}
	// inverser pour avoir le bon ordre
	if (bigint.taille() > 1) {
		bigint.inverser();
	}
}

Bint::Bint(const string & s) {
	string temp = s;
	assert(temp.length() > 0);
	for (char digit : temp) {
		assert(isdigit(digit));
	}
	// separer chaque bloc de 9 chars et les ajouter separement apres les avoir
	// convertit en int
	while (temp.length() > 9) {
		string morceau = temp.substr(temp.length()-9);
		int number = stoi(morceau);
		bigint.inserer(number);
		temp = temp.substr(0, temp.length()-9);
	}
	bigint.inserer(stoi(temp));
}

Bint::Bint(const Bint & bigA) {
	// utilisation la fonction deja implementé dans tableau.h
	bigint = bigA.bigint;
}

Bint::Bint(const Bint && bigA) {
	// utilisation la fonction deja implementé dans tableau.h
	bigint = bigA.bigint;
}

Bint::~Bint() {
}

int Bint::taille() const {
	int size = 0;
	// si Bint = 0 alors juste 1 char
	if (bigint.taille() == 1 && bigint[0] == 0) {
		return size = 1;
	}
	// chaque bloc est = 9 chars sauf le dernier
	if (bigint.taille() > 1) {
		size = (bigint.taille() - 1) * 9;
	}
	// add le dernier bloc
	int i = bigint[0];
	while (i > 0) {
		i /= 10;
		size++;
	}	
	return size;
}

bool Bint::operator < (const Bint & bigA) const {
	// si taille plus petite alors chiffre plus petit
	if (bigint.taille() < bigA.bigint.taille()) {
		return true;
	}
	// si taille plus grande alors chiffre plus grand
	if (bigint.taille() > bigA.bigint.taille()) {
		return false;
	}
	// taille == alors check de l'index 0 à max (si debut plus grand alors plus grand).
	for (int i = 0; i < bigint.taille(); i++) {
		if (bigint[i] < bigA.bigint[i]) {
			return true;
		}
		if (bigint[i] > bigA.bigint[i]) {
			return false;
		}
	}
	// les deux sont egaux
	return false;
}

bool Bint::operator > (const Bint & bigA) const {
	// si taille plus grande alors chiffre plus grand
	if (bigint.taille() > bigA.bigint.taille()) {
		return true;
	}
	// si taille plus petite alors chiffre plus petit
	if (bigint.taille() < bigA.bigint.taille()) {
		return false;
	}
	// taille == alors check de l'index 0 à max (si debut plus grand alors plus grand).
	for (int i = 0; i < bigint.taille(); i++) {
		if (bigint[i] > bigA.bigint[i]) {
			return true;
		}
		if (bigint[i] < bigA.bigint[i]) {
			return false;
		}
	}
	// les deux sont egaux
	return false;
}

bool Bint::operator <= (const Bint & bigA) const {
	return *this < bigA || *this == bigA;
}

bool Bint::operator >= (const Bint & bigA) const {
	return *this > bigA || *this == bigA;
}

bool Bint::operator == (const Bint & bigA) const {
	// utilisation de celle deja implementer dans tableau.h
	if (bigA.bigint == bigint) {
		return true;
	}
	return false;
}

bool Bint::operator != (const Bint & bigA) const {
	return !(*this == bigA);
}

Bint & Bint::operator = (const Bint & bigA) {
	// utilisation de celle deja implementé dans tableau.h
	bigint = bigA.bigint;
	return *this;
}

Bint & Bint::operator = (const string & s) {
	Bint bigA(s);
	return *this = bigA;
}

Bint & Bint::operator = (const Bint && bigA) {
	// utilisation de celle deja implementé dans tableau.h
	bigint = bigA.bigint;
	return *this;
}

Bint & Bint::operator += (const Bint & bigA) {
	return *this = *this + bigA;
}

Bint Bint::operator + (const Bint & bigA) const {
	Bint result;

	// remplir le Bint qui est le plus petit de 0 pour qu'il ai la meme
	// bigint.taille() et l'autre
	Bint courant;
	courant.bigint = bigint;
	Bint A = bigA;
	if (bigint.taille() > bigA.bigint.taille()) {
		while (courant.bigint.taille() != A.bigint.taille()) {
				A.bigint.inserer(0,0);
		}
	} if (bigint.taille() < A.bigint.taille()) {
		while (courant.bigint.taille() != A.bigint.taille()) {
			courant.bigint.inserer(0,0);
		}
	}

	int chiffre;
	int retenue = 0;
	int size = courant.bigint.taille();
	// iterer à travers les deux bints
	for (int i = size-1; i >= 0; --i) {
		chiffre = courant.bigint[i] + A.bigint[i] + retenue;
		if (chiffre > 999999999) {
			retenue = 1;
			result.bigint.inserer(chiffre%1000000000);

			// s'il reste une retenue mais qu'on a déja fini d'iterer,
			// inserer un autre element 1
			if (i == 0) {
				result.bigint.inserer(1);
			}
		} else {
			retenue = 0;
			result.bigint.inserer(chiffre);
		}
	}
	return result;
}

Bint & Bint::operator *= (const Bint & bigA) {
	*this = *this * bigA;
	return *this;
}

Bint Bint::operator * (const Bint & bigA) const {
	Bint result;
	long long chiffreamulti;
	long long chiffrequimulti;
	long long retenue = 0;
	long long produit = 0;
	int maxSize = bigint.taille() + bigA.bigint.taille();

	// iterer à travers les 2 chiffres pour les multiplier aux bons indexes 
	for (int step = 0; step <= maxSize; step++) {
		produit = 0;

		for (int i = 0;  i <= step; i++) {
			int index_i = bigint.taille() - 1 - i;
			int index_j = bigA.bigint.taille() - 1 - (step - i);

			// verifier que les deux indexes sont valides
			if (index_i >= 0 && index_j >= 0) {
				chiffreamulti = bigint[index_i];
				chiffrequimulti = bigA.bigint[index_j];
				produit += chiffreamulti * chiffrequimulti;
			}
		}
		// ajouter seulement les 9 premiers digits (+la retenue) et sauvegarder le surplus dans retenue
		result.bigint.inserer((produit+ retenue)%1000000000);
		retenue = (produit + retenue)/1000000000;
		produit = 0;
	}
	// enlever toutes les parties de bigint qui sont vides
	while (result.taille() > 1 && result.bigint[0] == 0) {
		result.bigint.enlever();
	}
	// s'il reste une retenue apres toutes les iterations, l'ajouter
	if (retenue > 0) {
		result.bigint.inserer(retenue);
	}
	// La capacite de result n'est plus adequate donc pour des soucis de constance je
	// remets la capacite comme qu'elle devrait l'etre avant de return result.
	Bint temp;
	for (int i = 0; i <= result.bigint.taille() - 1; i++) {
		temp.bigint.ajouter(result.bigint[i]);
	}
	result = temp;
	return result;
}

ostream & operator << (ostream & os, const Bint & bigA) {
	string output = "";

	// s'assure de mettre les 0 qui ne sont au debut des chiffres
	for (int i = 0; i < bigA.bigint.taille(); ++i) {
		string chiffre = to_string(bigA.bigint[i]);
		if (i != 0 && chiffre.length() != 9) {
			while (chiffre.length() < 9) {
				chiffre.insert(0, "0");
			}
		}
		output += chiffre;
	}
	os << output;
	return os;
}	

istream & operator >> (istream & is, Bint & bigA) {
	string input;
	is >> input;
	// check que le input est composé seulement de digits
	for (char digit : input) {
		assert(isdigit(digit));
	}
	// creer le Bint avec l'input
	bigA = Bint(input);
	return is;
}

/**************** Fonctions privées *****************/


#endif
