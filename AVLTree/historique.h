/*
  INF3105 - Structures de données et algorithmes

  Squellette pour le TP2
  Michael Lapadula
  LAPM67010405
*/

#if !defined(__HISTORIQUE__)
#define __HISTORIQUE__

#include <iostream>
#include <string>
#include "arbreavl.h"

typedef int Date; // optionnel

struct Intervalle{
    Date debut, fin;
    friend std::istream& operator >> (std::istream& is, Intervalle& itervale);
    friend std::ostream& operator << (std::ostream& os, const Intervalle& itervale);
};

struct Infos {
  std::string nompersonne;
  std::string lieu;
  bool operator<(const Infos& autre) const {
    if (nompersonne != autre.nompersonne) {
      return nompersonne < autre.nompersonne;
    }
    return lieu < autre.lieu;
  }
  bool operator>(const Infos& autre) const {
    return autre > *this;
  }
  bool operator==(const Infos& autre) const {
    return nompersonne == autre.nompersonne;
  }
};

struct Changement {
  Date date;
  mutable ArbreAVL<Infos> donnees;

  bool operator<(const Changement& autre) const {
    return date < autre.date;
  }
  bool operator>(const Changement& autre) const {
    return date > autre.date;
  }
  bool operator==(const Changement& autre) const {
    return date == autre.date;
  }

};

class Historique{
  public:
    Historique();
    
    void                  trace(Date date, const std::string& nompersonne, const std::string& lieu);
    ArbreAVL<std::string> localiser(const Intervalle&, const std::string& nompersonne) const;
    ArbreAVL<std::string> presences(const Intervalle&, const std::string& nomlieu) const;
    ArbreAVL<std::string> frequentations(const Intervalle&, const std::string& nompersonne) const;
    int                   duree_rencontres(const Intervalle&, const std::string& nompersonne1, const std::string& nompersonne2) const;
    
  private:
  ArbreAVL<Changement> historique;
};

#endif

