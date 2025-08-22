/*
  INF3105 - Structures de données et algorithmes
  
  Squelette pour Lab5 + TP2

  Michael Lapadula
  LAPM67010405
*/

#if !defined(__ARBRE_H__)
#define __ARBRE_H__

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
    void insererTout(const ArbreAVL&);
    void enlever(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();

    class Iterateur;
    
    const T&  min() const;
    Iterateur debut() const;
    Iterateur fin() const;
    
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);

    ArbreAVL& operator = (const ArbreAVL&);


  private:
    class Noeud;
    Noeud* racine;

    bool inserer(const T&, Noeud*&);

    bool enlever(const T& e, Noeud*& n);
    bool enleverGauche(const T&, Noeud*&);
    bool enleverDroite(const T&, Noeud*&);

    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);

    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;

    class Noeud{
      public:
        Noeud(const T&);
        Noeud *gauche;
        Noeud *droite;
        int equilibre;
        T contenu;
    };

// -------------
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
    
      protected:

        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;
        
        friend class ArbreAVL;
    };

    const T* trouver(const T&) const;
    int  hauteur() const;
    // version lente et complètement récursive
    int  hauteur2() const;

  private:
    const T* trouver(const T&, const Noeud*) const;
    const T& max(Noeud*) const;
    int  hauteur2(const Noeud*) const;
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c):
gauche(NULL), droite(NULL), equilibre(0), contenu(c)
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
void ArbreAVL<T>::insererTout(const ArbreAVL& arbre2){
    typename ArbreAVL::Iterateur iter = arbre2.debut();
    while(iter){
        inserer(*iter);
        ++iter;
    }
}

template <class T>
bool ArbreAVL<T>::inserer(const T& element, Noeud*& noeud)
{
    if(noeud==NULL)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(element, noeud->gauche))
        {
        noeud->equilibre++;
        if(noeud->equilibre == 0) return false;
        if(noeud->equilibre == 1) return true;
        //assert(noeud->equilibre==2);
        if(noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(element, noeud->droite))
        {
            noeud->equilibre--;
            if(noeud->equilibre == 0) return false;
            if(noeud->equilibre == -1) return true;
            //assert(noeud->equilibre==-2);
            if(noeud->droite->equilibre == 1)
                rotationGaucheDroite(noeud->droite);
            rotationDroiteGauche(noeud);
        }
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}


template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    enlever(element, racine);
}

template <class T>
bool ArbreAVL<T>::enlever(const T& e, Noeud*& n)
{
    if(n==NULL) return false;
    //assert(n!=NULL); // l'élément existe?
    if(e<n->contenu) return enleverGauche(e,n);
    if(n->contenu<e) return enleverDroite(e,n);
    Noeud* temp = n;
    if(n->gauche==NULL){
        n = n->droite;
        delete temp;
        return true;
    }
    if(n->droite==NULL){
        n = n->gauche;
        delete temp;
        return true;
    }
    n->contenu = max(n->gauche);
    return enleverGauche(n->contenu, n);
}

template <class T>
bool ArbreAVL<T>::enleverGauche(const T& e, Noeud*& n){
    bool retour=false;
    if(enlever(e, n->gauche)){
        n->equilibre--;
        if(n->equilibre==-1) return false;
        if(n->equilibre==0) return true;
        //assert(n->equilibre==-2);
        retour = n->droite->equilibre!=0;
        if(n->droite->equilibre==1) rotationGaucheDroite(n->droite);
        rotationDroiteGauche(n);
    }
    return retour;
}

template <class T>
bool ArbreAVL<T>::enleverDroite(const T& e, Noeud*& n){
    bool retour=false;
    if(enlever(e, n->droite)){
        n->equilibre++;
        if(n->equilibre==+1) return false;
        if(n->equilibre==0) return true;
        //assert(n->equilibre==+2);
        retour = n->gauche->equilibre!=0;
        if(n->gauche->equilibre==-1) rotationDroiteGauche(n->gauche);
        rotationGaucheDroite(n);
    }
    return retour;
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
    int  neb = -ea + (ea > 0 ? ea : 0) + 1 + eb;
    int  nea = ea + (neb > 0 ? neb : 0) + 1;

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
bool ArbreAVL<T>::vide() const{
    return racine == NULL;
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    if(noeud!=NULL)
    {
        vider(noeud->gauche);
        vider(noeud->droite);
        delete noeud;
        noeud = NULL;
    }
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    if(source!=NULL)
    {
        noeud = new Noeud(source->contenu);
        noeud->equilibre = source->equilibre;
        copier(source->gauche, noeud->gauche);
        copier(source->droite, noeud->droite);
    }
}

template <class T>
const T* ArbreAVL<T>::trouver(const T& element, const Noeud* noeud) const
{
    if(noeud==NULL)
        return NULL;
    if(element < noeud->contenu)
        return trouver(element, noeud->gauche);
    if(noeud->contenu < element)
        return trouver(element, noeud->droite);
    return &(noeud->contenu);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    return trouver(element)!=NULL;
}

template <class T>
const T* ArbreAVL<T>::trouver(const T& element) const
{
    return trouver(element, racine);
}

template <class T>
int  ArbreAVL<T>::hauteur() const{
    const Noeud* n = racine;
    int h=0;
    while(n!=NULL){
        ++h;
        n = n->equilibre<0 ? n->droite : n->gauche;
    }
    return h;
}

template <class T>
int  ArbreAVL<T>::hauteur2() const{
    return hauteur2(racine);
}
template <class T>
int  ArbreAVL<T>::hauteur2(const Noeud* n) const{
    if(n==NULL) return 0;
    int hg = hauteur2(n->gauche);
    int hd = hauteur2(n->droite);
    return 1 + (hg>hd ? hg : hd);
}

template <class T>
const T& ArbreAVL<T>::min() const{
    assert(racine!=NULL);
    Noeud* n = racine;
    while(n->gauche!=NULL)
        n = n->gauche;
    return n->contenu;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const
{
    //assert(n!=NULL);
    while(n->droite!=NULL)
        n = n->droite;
    return n->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const
{
    Iterateur iter(*this);
    iter.courant = racine;
    if(iter.courant!=NULL)
        while(iter.courant->gauche!=NULL){
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
    Noeud* n = racine;
    while(n){
        if(e < n->contenu){
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if(n->contenu < e)
            n = n->droite;
        else{
            iter.courant = n;
            return iter;
        }
    }
    iter.chemin.vider();
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const
{
    Iterateur iter(*this);
    Noeud* n = racine;
    while(n){
        if(e < n->contenu){
            iter.chemin.empiler(n);
            n = n->gauche;
        }
        else if(n->contenu < e)
            n = n->droite;
        else{
            iter.courant = n;
            return iter;
        }
    }
    if(!iter.chemin.vide()){
        iter.courant = iter.chemin.depiler();
        while(iter && iter.courant->contenu<e)
            ++iter;
    }
    return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const
{
    Noeud* n = racine;
    Pile<Noeud*> pile;
    while(n){
        pile.empiler(n);
        if(e < n->contenu){
            n = n->gauche;
        }
        else if(n->contenu < e)
            n = n->droite;
        else{
            break;
        }
    }
    while(!pile.vide()){
       n = pile.depiler();
       if(!(e<n->contenu))
           return rechercher(n->contenu);
    }
    return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const
{
    //assert(&iterateur.arbre_associe == this);
    //assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur)
{
    //assert(&iterateur.arbre_associe == this);
    //assert(iterateur.courant);
    return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
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

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++()
{
    //assert(courant);
    Noeud* suivant = courant->droite;
    while(suivant){
        chemin.empiler(suivant);
        suivant = suivant->gauche;
    }
    if(!chemin.vide())
        courant = chemin.depiler();
    else
        courant = NULL;
    return *this;
}

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
    //assert(&arbre_associe==&o.arbre_associe);
    return courant==o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const{
    //assert(&arbre_associe==&o.arbre_associe);
    return courant!=o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const
{
    //assert(courant!=NULL);
    return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre){
    //assert(&arbre_associe==&autre.arbre_associe);
    courant = autre.courant;
    chemin = autre.chemin;
    return *this;
}

#endif