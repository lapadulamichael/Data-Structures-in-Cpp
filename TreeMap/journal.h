/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp3/
 *
 *  	Identification.
 *              Nom et code permanent : Michael Lapadula LAPM67010405
 *
 *
 */
#if !defined(__JOURNAL_H__)
#define __JOURNAL_H__

#include <string>
#include "arbremap.h"
#include "date.h"

using namespace std;

class Journal{
  public:
    void                  enregistrerService(const Date& date, const string& nompersonne, const string& nomcocktail);
    ArbreMap<string, int> requeteQui(const Date& debut, const Date& fin, const ArbreAVL<string>& cocktails) const;
    ArbreMap<string, int> requeteQuoi(const Date& debut, const Date& fin, const ArbreAVL<string>& buveurs) const;
    ArbreAVL<string>  	  requetePresences(const Intervalle& i) const;

  private:
    ArbreMap<Date, ArbreMap<string, ArbreAVL<string>>> services;
};




#endif
