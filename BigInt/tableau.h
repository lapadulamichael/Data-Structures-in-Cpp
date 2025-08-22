/** 
 * Squelette pour classe générique Tableau<T>.
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

#ifndef __TABLEAU_H___
#define __TABLEAU_H___

// Vous devez utiliser les assertions pour vérifier les conditions
// de base sur les indices.

#include <assert.h>
#include <locale>

template <class T>
class Tableau {
	/**************** Interface publique ****************
	* 
	* Vous ne devez pas ajouter de nouvelles fonctions 
	* publiques ni modifier les fonctions déjà présentes 
	* (ne pas modifier la signature ni la valeur retournée).
	*
	*****************************************************/
	public:		
		/************ Constructeurs et destructeur ************/
		// Constructeur par défaut 
		Tableau(int capacite_initiale = 4);
		// Constructeur par copie
		Tableau(const Tableau & autre);
		// Constructeur par déplacement
		Tableau(const Tableau && autre);
		// Destructeur
		~Tableau();
		/******************************************************/


		/*************** Fonctions utilitaires ****************/
		// Ajoute un élément e à la fin du tableau.
		// Si la taille == capacité, alors il faut doubler la 
		// capacité.
		// Complexité amortie : O(1)
		void ajouter(const T & e);
  
		// Retourne le nombre d'éléments dans le tableau.
		// Complexité : O(1)
		int taille() const;

		// Insère un élément e à la position i du tableau.
		// Si le tableau est vide, alors on doit avoir i == 0
		// Si le tableau n'est pas vide, alors 0 <= i < nbElements.
		// Si la taille == capacité, alors il faut doubler la 
		// capacité.
		// Complexité : O(n) 
		//	n étant la taille du tableau.
		void inserer(const T & e, int i = 0);
		
		// Enlève un élément à la position i.
		// Complexité : O(n)
		//	n étant la taille du tableau.
		void enlever(int i = 0);
		
		// Inverser les éléments du tableau, le dernier deviendra le premier,
		// l'avant dernier deviendra le deuxièm, et ainsi de suite.'
		// Complexité : O(n)
		//	n étant la taille du tableau.
		void inverser();

		// Vide le tableau sans libérer la mémoire.
		// Complexité : O(1)
		void vider();
		/******************************************************/
		
		
		/********************* Opérateurs *********************/
		// Opérateurs de comparaison
		//
		// Deux tableaux sont égaux s'ils ont exactement la même taille
		// et les mêmes éléments aux mêmes indices.
		// Complexité : O(n)
		//	n étant la taille du tableau.
		bool operator == (const Tableau<T> & autre) const;
		bool operator != (const Tableau<T> & autre) const;
		// Opérateurs d'accès et de modificatiom
		const T & operator [] (int index) const;
		T & operator [] (int index);
		// Opérateurs d'affectation
		Tableau<T> & operator = (const Tableau<T> & autre);
		Tableau<T> & operator = (const Tableau<T> && autre);
		/******************************************************/
	/**************** Représentation ********************
	* 
	* Représentation interne de la classe Tableau<T>,
	* vous n'avez pas le droit de la modifier ni d'y 
	* ajouter des variables/attributs.
	*
	*****************************************************/
	private:
    		T * elements;
    		int nbElements;
    		int capacite;
    	
	    	/**************** Interface privée ******************
		* 
		* Vous pouvez ajouter toutes les fonctions privées
		* que vous estimez nécessaire.
		* N'oubliez pas de bien commenter vos fonctions, de 
		* bien utilisez le mot-clé const et de prendre en 
		* considération les bonnes pratiques.
		*
		*****************************************************/
			void redimensionner();
};

/*************** Fonctions publiques ****************/

template <class T>
Tableau<T>::Tableau(int capacite_initiale) {
	// création du tableau de base
	capacite = capacite_initiale;
	nbElements = 0;
	elements = new T[capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau & autre) {
	capacite = autre.capacite;
	nbElements = autre.nbElements;
	elements = new T[capacite];

	// recopier les elements proprement
	for (int i = 0; i < nbElements; i++) {
		elements[i] = autre.elements[i];
	}
}

template <class T>
Tableau<T>::Tableau(const Tableau && tab) {
	capacite = tab.capacite;
	nbElements = tab.nbElements;
	elements = new T[capacite];

	// recopier les elements proprement
	for (int i = 0; i < nbElements; i++) {
		elements[i] = tab.elements[i];
	}
}

template <class T>
Tableau<T>::~Tableau() {
	delete[] elements;
}

template <class T>
void Tableau<T>::ajouter(const T & element) {
	// si pas de place pour ajouter alors redimensionner
	if (nbElements == capacite) {
		redimensionner();
	}

	elements[nbElements++] = element;
}

template <class T>
int Tableau<T>::taille() const {
	return nbElements;
}

template <class T>
void Tableau<T>::inserer(const T & element, int index) {
	assert(index >= 0);
	assert(index <= nbElements);

	// si pas de place pour ajouter alors redimensionner
	if (nbElements == capacite) {
		redimensionner();
	}
	// iterer jusqu'a l'index puis deplacer tous les elements apres celui-ci
	for (int i = nbElements-1; i >= index; i--) {
		elements[i+1] = elements[i];
	}
	nbElements++;
	// inserer l'element sur l'index pret a acceuillir un element
	elements[index] = element;
}

template <class T>
void Tableau<T>::enlever(int index) {
	assert(index >= 0);
	assert(index < nbElements);

	nbElements--;
	// deplacer tous les elements apres l'index une fois
	// vers la gauche pour 'supprimer' ce qu'il y avait dessus
	for (int i = index; i < nbElements; i++) {
		elements[i] = elements [i+1];
	}
}

template <class T>
void Tableau<T>::inverser() {
	assert(nbElements > 1);

	// inverser les extremites jusqu'a temps qu'on arrive au milieu
	for (int i = 0; i < (nbElements/2); i++) {
		T temp = elements[i];
		elements[i] = elements[taille()-1-i];
		elements[taille()-1-i] = temp;
	}
}

template <class T>
void Tableau<T>::vider() {
	// reset nbElements et elements
	nbElements = 0;
	delete[] elements;
	elements = new T[capacite];
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T> & autre) const {
	// si pas le meme nbElement ou capacite alors peut pas etre le meme
	if (nbElements != autre.nbElements || capacite != autre.capacite) {
		return false;
	}
	// iterer à travers chaque element pour les comparer
	for (int i = 0; i < nbElements; i++) {
		if (elements[i] != autre.elements[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool Tableau<T>::operator != (const Tableau<T> & autre) const {
	// si pas le meme nbElement ou capacite alors peut pas etre le meme
	if (nbElements != autre.nbElements || capacite != autre.capacite) {
		return true;
	}
	// iterer à travers chaque element pour les comparer
	for (int i = 0; i < nbElements; i++) {
		if (elements[i] != autre.elements[i]) {
			return true;
		}
	}
	return false;
}

template <class T>
const T & Tableau<T>::operator [] (int index) const {
	assert(index >= 0);
	assert(index < nbElements);
	return elements[index];
}

template <class T>
T & Tableau<T>::operator [] (int index) {
	assert(index >= 0);
	assert(index < nbElements);
	return elements[index];
}

template <class T>
Tableau<T> & Tableau<T>::operator = (const Tableau<T> & autre) {
	// s'assurer qu'on ne copie pas exactement le meme tableau
	if (this != &autre) {
		delete[] elements;
		capacite = autre.capacite;
		nbElements = autre.nbElements;
		elements = new T[capacite];

		// recopier les elements proprement
		for (int i = 0; i < nbElements; i++) {
			elements[i] = autre.elements[i];
		}
	}
	return *this;
}

template <class T>
Tableau<T> & Tableau<T>::operator = (const Tableau<T> && autre) {
	// s'assurer qu'on ne copie pas exactement le meme tableau
	if (this != &autre) {
		delete[] elements;
		capacite = autre.capacite;
		nbElements = autre.nbElements;
		elements = new T[capacite];

		// recopier les elements proprement
		for (int i = 0; i < nbElements; i++) {
			elements[i] = autre.elements[i];
		}
	}
	return *this;
}

template <class T>
void Tableau<T>::redimensionner() {
	// doubler la capacite
	capacite = capacite * 2;
	T* temp = elements;
	elements = new T[capacite];

	// recopier les elements proprement
	for (int i = 0; i < nbElements; i++) {
		elements[i] = temp[i];
	}
	delete [] temp;
}

/**************** Fonctions privées *****************/

#endif
