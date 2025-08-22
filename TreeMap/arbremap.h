/* Squelette pour classe générique ArbreMap<K, V>.
 * Lab8 -- Dictionnaires et Arbres binaires de recherche
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab8/
 *
 */
#if !defined(_ARBREMAP___H_)
#define _ARBREMAP___H_
#include "arbreavl.h"

template <class K, class V>
class ArbreMap {
  struct Entree;
  public:
    bool contient(const K&) const;

    void enlever(const K&);
    void vider();
    bool vide() const;

    const V& operator[] (const K&) const;
    V& operator[] (const K&);

    class Iterateur {
      public:
        Iterateur(ArbreMap& a) : iter(a.entrees.debut()) {}
        Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}

        operator bool() const {return iter.operator bool();};
        Iterateur& operator++() {++iter; return *this;}

        const K& cle() const {return (*iter).cle;}
        V& valeur()  {return (V&) (*iter).valeur;}

      private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };

    Iterateur debut() { 
      return Iterateur(entrees.debut());
    }
    Iterateur fin() {
      return Iterateur(entrees.fin());
    }
    Iterateur rechercher(const K& cle) {
      return Iterateur(entrees.rechercher(cle));
    }
    Iterateur rechercherEgalOuSuivant(const K& cle) {
        return Iterateur(entrees.rechercherEgalOuSuivant(cle));
    }
    Iterateur rechercherEgalOuPrecedent(const K& cle) {
        return Iterateur(entrees.rechercherEgalOuPrecedent(cle));
    }

    class IterateurConst {
      public:
        IterateurConst(const ArbreMap& a) : iter(a.entrees.debut()) {}
        IterateurConst(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}

        operator bool() const {return iter.operator bool();};
        IterateurConst& operator++() {++iter; return *this;}

        const K& cle() const {return (*iter).cle;}
        const V& valeur() const {return (*iter).valeur;}

      private:
        typename ArbreAVL<Entree>::Iterateur iter;
    };

    IterateurConst debut() const {
      return IterateurConst(entrees.debut());
    }
    IterateurConst fin() const {
      return IterateurConst(entrees.fin());
    }
    IterateurConst rechercher(const K& cle) const {
    }
    IterateurConst rechercherEgalOuSuivant(const K& cle) const {
    }
    IterateurConst rechercherEgalOuPrecedent(const K& cle) const {
    }

private:
  struct Entree {
    K cle;
    V valeur;
    Entree(const K& _cle, const V& _valeur = V()) : cle(_cle), valeur(_valeur) {}
    bool operator < (const Entree& e) const {
      return cle < e.cle;
    }
    bool operator > (const Entree& e) const {
      return cle > e.cle;
    }
    bool operator == (const Entree& e) const {
      return cle == e.cle;
    }
  };
  ArbreAVL<Entree> entrees;
};

template <class K, class V>
void ArbreMap<K,V>::vider(){
    entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const{
  return entrees.vide();

}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c)
{
    entrees.enlever(Entree(c));
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const
{
    return entrees.contient(Entree(c));
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const
{
  Entree entree(c);
  auto it = entrees.rechercher(entree);
  assert(it);
  return (*it).valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c)
{
  Entree entree(c);
  auto it = entrees.rechercher(entree);
  if (!it) {
    entrees.inserer(entree);
    it = entrees.rechercher(entree);
  }
  return const_cast<V&>((*it).valeur);
}


#endif

