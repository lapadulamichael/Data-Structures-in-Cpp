/* 
 * Squelette minimal pour la classe générique Digraph<T> du TP4.
 * TP4 -- Graphes orientés
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes (Hiver 2025)
 *
 *	Identification.
 *		
 *		Nom et prénom	: Lapadula Michael
 *		Code permanent	: LAPM67010405
 *
 */
 

#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <set>
#include <map>
#include <tuple>
#include <assert.h>
//#include <array>
#include <vector>
//#include <deque>
//#include <forward_list>
//#include <list>
//#include <multiset>
//#include <multimap>
#include <unordered_set>
//#include <unordered_map>
//#include <unordered_multiset>
//#include <unordered_multimap>
//#include <stack>
//#include <queue>
//#include <priority_queue>
#include <limits>

/*
 * 	Remarque.
 *	Tout parcours des structures de données "map" et "set" doit se faire dans	
 *	l'ordre croissant (pour les valeurs numériques) ou l'ordre lexicographique
 *	(pour les caractères ou chaines de caractères). C'est le parcours implémenté
 *	dans le standard C++11 avec le compilateur g++.
 *	Par conséquent, lors de la recherche de circuits, c'est le premier circuit 
 *	induit par parcours en ordre croissant qui sera considéré dans les différents
 *	tests.
 */

template <class T>
class Digraph {
	// Vous n'avez pas le droit de modifier cette interface. Aucun ajout de fonction
	// publique n'est autorisé. Aucune modification des signatures ou des types de
	// retour des déclarations fonctions publiques n'est autorisé.
	public:
		Digraph();
		Digraph(const Digraph & autre);
		~Digraph();
		Digraph<T> & operator = (const Digraph<T> & autre);
		
		/************* Fonctions pour les caractéristiques de graphe *************/
		// Retourne le nombre de sommets du graphe courant.
		int sommets() const;
		// Retourne le nombre d'arcs du graphe courant.
		int arcs() const;
		// Retourne "true" si "u" est un sommet du graphe courant. "false" si 
		// non.
		bool sommet(T u) const;
		// Retourne "true" si "(u,v)" est un arc du graphe courant. "false" si
		// non.
		bool arc(T u, T v) const;

		/***************************** Modificateurs *****************************/
		// Insère le sommet "u" si le graphe ne le contient pas. Ne fait rien
		// si le graphe contient déjà le sommet "u".
		void inserer(T u);

		// Créé un arc entre les sommets "u" et "v" avec le poids "emprunt", 
		// si le graphe ne contient pas l'arc "(u, v)". Ne fait rien si le
		// graphe contient déjà un arc "(u,v)".
		// Si l'arc doit être créé faut s'assurer que,
		// 	- "u" doit être différent de "v",
		// 	- "emprunt" doit être strictement positif,
		// 		- faut arrêter l'exécution avec la fonction "assert" si les 
		// 		deux conditions plus haut ne sont pas satisfaites,
		// 	- si l'arc "(u,v)" existe déjà, peu importe la valeur de "emprunt",
		//	rien ne	sera fait par la fonction inserer.
		// 	- si l'un ou les deux sommets "u" et "v" n'existent pas dans
		// 	le graphe, ils seront crées.
		void inserer(T u, T v, double emprunt);
		
		// Supprime le sommet "u" et tous les arcs qui lui sont incidents.
		void supprimer(T u);
		
		// Supprime l'arc "(u, v)"
		void supprimer(T u, T v);
		
		/*********************** Fonctions financières ***********************/
		// Retourne le montant total que doit rembourser le sommet "u".
		double dette(T u) const;
					
		// Retourne le montant total des remboursements que doit recevoir 
		// le sommet "u".
		double pret(T u) const;

	// Réduit les dettes circulaires du sommet "s". Voir plus d'explications
		// et un exemple dans l'énoncé.
		void reduire(T s);
	
	// Vous n'avez pas le droit de modifier le type de l'attribut "graphe".
	// Vous n'avez pas le droit d'ajouter d'autres attributs privés.		
	private:
		// Par défaut, le "map" et le "set" sont parcourus en ordre croissant, 
		// ils sont ordonnés (standard C++11).
		std::map<T,std::set<std::tuple<T,double>>> graphe;
		bool find_cycle(const T &start, const T &current, std::set<T> &visited, std::vector<T> &path);

		// Vous pouvez ajouter toutes les fonctions privées que vous estimez
		// nécessaire.
};

template<class T>
Digraph<T>::Digraph() {
}

template<class T>
Digraph<T>::Digraph(const Digraph &autre) {
	graphe = autre.graphe;
}

template<class T>
Digraph<T>::~Digraph() {
}

template<class T>
Digraph<T> & Digraph<T>::operator=(const Digraph<T> &autre) {
	if (this != &autre) {
		graphe = autre.graphe;
	}
	return *this;
}

template<class T>
int Digraph<T>::sommets() const {
	return graphe.size();
}

template<class T>
int Digraph<T>::arcs() const {
	int total = 0;
	for (auto it = graphe.begin(); it != graphe.end(); ++it) {
		total += it->second.size();
	}
	return total;
}

template<class T>
bool Digraph<T>::sommet(T u) const {
	return graphe.find(u) != graphe.end();
}

template<class T>
bool Digraph<T>::arc(T u, T v) const {
	//check si u existe
	auto it = graphe.find(u);
	if (it == graphe.end()) return false;

	//arc u, v?
	for (auto arcsIt = it->second.begin(); arcsIt != it->second.end(); ++arcsIt) {
		if (std::get<0>(*arcsIt) == v)
			return true;
	}

	return false;
}

template<class T>
void Digraph<T>::inserer(T u) {
	if (graphe.find(u) == graphe.end())
		graphe[u] = std::set<std::tuple<T, double>>();
}

template<class T>
void Digraph<T>::inserer(T u, T v, double emprunt) {
	assert(u != v);
	assert(emprunt > 0.0);
	if (arc(u, v)) return;
	inserer(u);
	inserer(v);
	graphe[u].emplace(v, emprunt);
}

template<class T>
void Digraph<T>::supprimer(T u) {
	graphe.erase(u);
	for (auto it = graphe.begin(); it != graphe.end(); ++it) {
		for (auto arcsIt = it->second.begin(); arcsIt != it->second.end(); ) {
			if (std::get<0>(*arcsIt) == u)
				arcsIt = it->second.erase(arcsIt);
			else {
				++arcsIt;
			}
		}
	}
}

template<class T>
void Digraph<T>::supprimer(T u, T v) {
	if (!arc(u, v)) return;

	auto it = graphe.find(u);
	for (auto arcsIt = it->second.begin(); arcsIt != it->second.end(); ) {
		if (std::get<0>(*arcsIt) == v)
			arcsIt = it->second.erase(arcsIt);
		else {
			++arcsIt;
		}
	}
}

template<class T>
double Digraph<T>::dette(T u) const {
	if (!sommet(u)) return 0.0;

	double total = 0.0;
	for (auto it = graphe.begin(); it != graphe.end(); ++it) {
		const auto& arcs = it->second;
		for (auto arcIt = arcs.begin(); arcIt != arcs.end(); ++arcIt) {
			if (std::get<0>(*arcIt) == u) {
				total += std::get<1>(*arcIt);
			}
		}
	}
	return total;
}

template<class T>
double Digraph<T>::pret(T u) const {
	double total = 0.0;
	if (!sommet(u)) return total;
	auto it = graphe.find(u);
	for (auto arcsIt = it->second.begin(); arcsIt != it->second.end(); ++arcsIt) {
		total += std::get<1>(*arcsIt);
	}
	return total;
}

template<class T>
void Digraph<T>::reduire(T start) {
	if (!sommet(start) || graphe[start].empty())
		return;

	typedef typename std::set<std::tuple<T, double>>::iterator it_arc;

	bool found;
	do {
		found = false;
		std::vector<T> stack;
		std::vector<it_arc> cur_arc, end_arc;
		std::unordered_set<T> seen, closed;
		std::vector<std::tuple<T, T, double>> trace;

		stack.push_back(start);
		cur_arc.push_back(graphe[start].begin());
		end_arc.push_back(graphe[start].end());
		seen.insert(start);
		while (!stack.empty() && !found) {
			T u = stack.back();
			auto& arc = cur_arc.back();
			auto& arc_end = end_arc.back();
			if (arc == arc_end) {
				cur_arc.pop_back();
				end_arc.pop_back();
				stack.pop_back();
				seen.erase(u);
				closed.insert(u);
				if (!trace.empty()) trace.pop_back();
				continue;
			}
			T v = std::get<0>(*arc);
			double cost = std::get<1>(*arc);
			++arc;
			if (closed.count(v))
				continue;
			if (seen.insert(v).second) {
				cur_arc.push_back(graphe[v].begin());
				end_arc.push_back(graphe[v].end());
				stack.push_back(v);
				trace.emplace_back(u, v, cost);
			} else if (v == start) {
				found = true;
				trace.emplace_back(u, v, cost);
			}
		}
		if (!found)
			break;

		double min_w = std::numeric_limits<double>::infinity();
		for (int i = 0; i < trace.size(); ++i) {
			T u = std::get<0>(trace[i]);
			T v = std::get<1>(trace[i]);
			for (auto arcsIt = graphe.find(u)->second.begin(); arcsIt != graphe.find(u)->second.end(); ++arcsIt) {
				if (std::get<0>(*arcsIt) == v) {
					min_w = std::min(min_w, std::get<1>(*arcsIt));
					break;
				}
			}
		}
		for (int i = 0; i < trace.size(); ++i) {
			T u = std::get<0>(trace[i]);
			T v = std::get<1>(trace[i]);
			for (auto arcsIt = graphe.find(u)->second.begin(); arcsIt != graphe.find(u)->second.end(); ) {
				if (std::get<0>(*arcsIt) == v) {
					double new_w = std::get<1>(*arcsIt) - min_w;
					arcsIt = graphe.find(u)->second.erase(arcsIt);
					if (new_w > 0.0)
						graphe[u].emplace(v, new_w);
				} else {
					++arcsIt;
				}
			}
		}

	} while (found);
}
//version finale

#endif
