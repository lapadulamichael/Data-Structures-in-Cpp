/*
  INF3105 - Structures de données et algorithmes
  
  Squelette pour Lab5 + TP2

  Michael Lapadula
  LAPM67010405
*/
#if !defined(__ARBREAVL_H__)
#define __ARBREAVL_H__

#include <assert.h>
#include <stdio.h>
#include "pile.h"

template <class T>
class ArbreAVL {
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    void inserer(const T&);
    void enlever(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();
    int  hauteur() const;

    ArbreAVL& operator = (const ArbreAVL&);

    // Puisque les fonctions suivantes retournent des itérateurs, il faut *annoncer* la décalaration classe Iterateur
    // On ne peut pas déclarer Iterateur tout de suite, car Iterateur a besoin de Noeud.
    class Iterateur;
    
    Iterateur debut() const;
    Iterateur fin() const;

    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);

  private:
    class Noeud;
    Noeud* racine;

    bool inserer(const T&, Noeud*&);

    bool enlever(const T& e, Noeud*& n);
    int hauteur(Noeud *n) const;
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);

    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    Noeud* max(Noeud* n) const;

  public:
    class Iterateur{
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);
        Iterateur(const ArbreAVL& a, Noeud* c);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;
        
        const T& operator*() const;

        Iterateur& operator++();
        Iterateur operator++(int);
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
      friend class ArbreAVL;
    };

  private:
    class Noeud{
      public:
        Noeud(const T&);
        Noeud *gauche;
        Noeud *droite;
        int equilibre;
        T element;
    };
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
gauche(NULL), droite(NULL), equilibre(0), element(c)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL& autre) : racine(NULL)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(element, racine);
}

template <class T>
bool ArbreAVL<T>::inserer(const T& element, Noeud*& noeud)
{
    if (noeud == nullptr) {
        noeud = new Noeud(element);
        return true;
    }
    if (element < noeud->element) {
        if (inserer(element, noeud->gauche)) {
            noeud->equilibre++;
            if (noeud->equilibre == 0) return false;
            if (noeud->equilibre == 1) return true;
            assert(noeud->equilibre == 2);

            if (noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    } else if (noeud->element < element) {
        if(inserer(element, noeud->droite))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;
            assert(noeud->equilibre==-2);

            if(noeud->droite->equilibre == 1)
                rotationGaucheDroite(noeud->droite);
            rotationDroiteGauche(noeud);
        }
        return false;
    }

    // element == noeud->element
    noeud->element = element;  // Mise à jour
    return false;
}


template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
  enlever(element, racine);
}

template <class T>
bool ArbreAVL<T>::enlever(const T& element, Noeud*& noeud)
{
    if (noeud == nullptr) return false;

    if (element < noeud->element) {
        if (enlever(element, noeud->gauche)) {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;
            assert(noeud->equilibre==-2);
            if (noeud->gauche != nullptr) {
                if(noeud->gauche->equilibre == 1)
                    rotationGaucheDroite(noeud->droite);
                rotationDroiteGauche(noeud);
            }
            if (noeud->gauche == nullptr) {
                rotationDroiteGauche(noeud);
            }
        }
        return false;

    } else if (element > noeud->element) {
        if (enlever(element, noeud->droite)) {
            noeud->equilibre++;
            if (noeud->equilibre == 0) return false;
            if (noeud->equilibre == 1) return true;
            assert(noeud->equilibre == 2);

            if (noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    } else { // élément trouvé
        if (noeud->gauche == nullptr && noeud->droite == nullptr) {
            delete noeud;
            noeud = nullptr;
            return true;
        } else if (noeud->gauche == nullptr) {
            Noeud* temp = noeud;
            noeud = noeud->droite;
            delete temp;
            return true;
        } else if (noeud->droite == nullptr) {
            Noeud* temp = noeud;
            noeud = noeud->gauche;
            delete temp;
            return true;
        } else {
            Noeud* temp = max(noeud->gauche);
            noeud->element = temp->element;
            enlever(temp->element, noeud->gauche);
            noeud->equilibre++;
        }
    }

    return true;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;
    int  neb = -(ea > 0 ? 0 : ea) + 1 + eb;
    int  nea = (neb > 0 ? neb : 0) + 1 + ea;
    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
  if(noeud!=nullptr) {
    vider(noeud->gauche);
    vider(noeud->droite);
    noeud = nullptr;
    delete noeud;
  }
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if (source != nullptr){
        if (noeud == nullptr){
            noeud = new Noeud(source->element);
            copier(source, noeud);
        }
        else{
            noeud->element = source->element;
            noeud->equilibre = source->equilibre;
            if (source->gauche != nullptr){
                copier(source->gauche, noeud->gauche);
            }
            if (source->droite != nullptr){
                copier(source->droite, noeud->droite);
            }
        }
    }
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    Noeud* temp = racine;
    while(temp != nullptr){
        if(temp->element == element)
            return true;
        if(temp->element > element)
            temp = temp->gauche;
        else if(temp->element < element)
            temp = temp->droite;
    }
    return false;
}


template <class T>
bool ArbreAVL<T>::vide() const {
    if (racine == nullptr) return true;
    return false;

}

template <class T>
int ArbreAVL<T>::hauteur() const {
    return hauteur(racine);
}

template <class T>
int ArbreAVL<T>::hauteur(Noeud* n) const {
    if (n == nullptr) return -1;

    int hGauche = hauteur(n->gauche);
    int hDroite = hauteur(n->droite);

    if (hGauche > hDroite) {
        return 1 + hGauche;
    } else {
        return 1 + hDroite;
    }
}

template <class T>
typename ArbreAVL<T>::Noeud *ArbreAVL<T>::max(Noeud *n) const
{
    if (n == nullptr) return nullptr;
    while (n->droite != nullptr) {
        n = n->droite;
    }
    return n;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    if (!iter) return iter;

    while (iter.courant->gauche != nullptr) {
        iter.chemin.empiler(iter.courant);
        iter.courant = iter.courant->gauche;
    }
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const
{
    return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const
{
    Iterateur iter(*this);
    Noeud* noeud = racine;

    while (noeud) {
        if (e < noeud->element) {
            iter.chemin.empiler(noeud);
            noeud = noeud->gauche;
        }else if (e > noeud->element) {
            noeud = noeud->droite;
        }else {
            iter.courant = noeud;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
    Iterateur iter = rechercherEgalOuPrecedent(e);
    if (!iter) {
        return debut();
    }
    return iter.courant->element == e ? iter : ++iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
    Noeud* noeud = racine, *parent = nullptr;
    while (noeud) {
        if (e < noeud->element) {
            noeud = noeud->gauche;
        } else if (e > noeud->element) {
            parent = noeud;
            noeud = noeud->droite;
        } else {
            return rechercher(e);
        }
    }
    return parent ? rechercher(parent->element) : Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->element;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    assert(&iterateur.arbre_associe == this);
    assert(iterateur.courant);
    return iterateur.courant->element;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre){
    if (this == &autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

//-----------------------
template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a)
 : arbre_associe(a), courant(NULL)
{
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
: arbre_associe(a.arbre_associe)
{
    courant = a.courant;
    chemin = a.chemin;
}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    if (courant == nullptr) return *this;
    if (courant->droite) {
        courant = courant->droite;
        while (courant->gauche) {
            chemin.empiler(courant);
            courant = courant->gauche;
        }
    }

    else {
        if (!chemin.vide()) courant = chemin.depiler();
        else courant = nullptr;
    }
    return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int)
{
    Iterateur copie(*this);
    operator++();
    return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const
{
    return courant!=NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const{
    return courant==NULL;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    assert(courant!=NULL);
    return courant->element;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}


#endif


