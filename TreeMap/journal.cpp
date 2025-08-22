/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp3/
 *
 *	Identification.
 *		Nom et code permanent : Michael Lapadula LAPM67010405
 *
 *		 
 */
#include "journal.h"

void Journal::enregistrerService(const Date& date, const string& nompersonne, const string& nomcocktail)
{
  services[date][nomcocktail].inserer(nompersonne);
}

ArbreMap<string, int> Journal::requeteQui(const Date& debut, const Date& fin, const ArbreAVL<string>& cocktails) const
{
  ArbreMap<string, int> resultat;

  for (ArbreMap<Date, ArbreMap<string, ArbreAVL<string>>>::IterateurConst it = services.debut();
    it != services.fin(); ++it) {
    Date date = it.cle();
    if (date > fin) break;
    if (debut <= date) {
      for (ArbreMap<string, ArbreAVL<string>>::IterateurConst jt = it.valeur().debut();
        jt != it.valeur().fin(); ++jt) {
        if (cocktails.contient(jt.cle()) || cocktails.vide()) {
          for (ArbreAVL<string>::Iterateur personnes = jt.valeur().debut(); personnes != jt.valeur().fin(); ++personnes) {
            resultat[personnes.operator*()]++;
          }
        }
      }
    }
  }
  return resultat;
}

ArbreMap<string, int> Journal::requeteQuoi(const Date& debut, const Date& fin, const ArbreAVL<string>& buveurs) const
{
  ArbreMap<string, int> resultat;

  for (ArbreMap<Date, ArbreMap<string, ArbreAVL<string>>>::IterateurConst it = services.debut();
    it != services.fin(); ++it) {
    Date date = it.cle();
    if (date > fin) break;
    if (debut <= date) {
      for (ArbreMap<string, ArbreAVL<string>>::IterateurConst jt = it.valeur().debut();
        jt != it.valeur().fin(); ++jt) {
        for (ArbreAVL<string>::Iterateur ht = jt.valeur().debut(); ht != jt.valeur().fin(); ++ht) {
          if (buveurs.contient(ht.operator*()) || buveurs.vide()) {
            resultat[jt.cle()]++;
          }
        }
      }
    }
  }

  return resultat;
}

ArbreAVL<string> Journal::requetePresences(const Intervalle& i) const
{
  ArbreAVL<string> resultat;
  ArbreMap<string, Date> fete;
  ArbreMap<string, Date> membre_eligible;
  bool terminer = false;
  string dernier_nom;

  for (ArbreMap<Date, ArbreMap<string, ArbreAVL<string>>>::IterateurConst it = services.debut();
    it != services.fin(); ++it) {
    if (terminer == true) break;
    for (ArbreMap<string, ArbreAVL<string>>::IterateurConst jt = it.valeur().debut();
      jt != it.valeur().fin(); ++jt) {
      for (ArbreAVL<string>::Iterateur kt = jt.valeur().debut(); kt != jt.valeur().fin(); ++kt) {
        if (fete.vide() || it.cle() <= fete[dernier_nom]) {
          if (fete.contient(kt.operator*()) && it.cle() <= fete[kt.operator*()]) {
            fete[kt.operator*()] += 900;
            if (fete[kt.operator*()]+ (-900) <= i.fin || membre_eligible.contient(kt.operator*())) {
              membre_eligible[kt.operator*()] = fete[kt.operator*()];
            }
          } else {
            fete[kt.operator*()] = it.cle()+ 900;
            if (it.cle() <= i.fin || membre_eligible.contient(kt.operator*())) {
              membre_eligible[kt.operator*()] = fete[kt.operator*()];
            }
          }
        } // si pas meme fete
        else {
          for (ArbreMap<string, Date>::Iterateur iter_fete = membre_eligible.debut();
            iter_fete != membre_eligible.fin(); ++iter_fete) {
            if (i.debut <= membre_eligible[iter_fete.cle()]) {
              if (!resultat.contient(iter_fete.cle())) resultat.inserer(iter_fete.cle());
            }
          }
          if (it.cle()> i.fin) terminer = true;

          fete.vider();
          membre_eligible.vider();
          fete[kt.operator*()] = it.cle() + 900;
          if (it.cle() <= i.fin || membre_eligible.contient(kt.operator*())) {
            membre_eligible[kt.operator*()] = fete[kt.operator*()];
          }
        }

        dernier_nom = kt.operator*();
      }
    }
  }
  if (terminer == false) {
    for (ArbreMap<string, Date>::Iterateur iter_fete = membre_eligible.debut();
      iter_fete != membre_eligible.fin(); ++iter_fete) {
      if (i.debut <= membre_eligible[iter_fete.cle()]) {
        if (!resultat.contient(iter_fete.cle())) resultat.inserer(iter_fete.cle());
      }
    }
  }
  return resultat;
}

