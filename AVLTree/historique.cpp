/*
  INF3105 - Structures de données et algorithmes

  Squellette pour le TP2
  Michael Lapadula
  LAPM67010405
*/

#include "historique.h"
#include <iostream>

std::istream& operator >> (std::istream& is, Intervalle& intervalle)
{
    char crochetgauche, crochetdroit, virgule;
    is >> crochetgauche >> intervalle.debut >> virgule >> intervalle.fin >> crochetdroit;
    assert(crochetgauche=='[' && virgule==',' && crochetdroit==']');
    return is;
}

std::ostream& operator << (std::ostream& os, const Intervalle& intervalle)
{
    os << '[' << intervalle.debut << ',' << intervalle.fin << ']';
    return os;
}

Historique::Historique()
{
}

void Historique::trace(Date date, const std::string& nompersonne, const std::string& nomlieu)
{
    Changement changement;
    changement.date = date;
    //si deja cette date, ajouter les infos
    if (historique.contient(changement)) {
        const Changement& temp = historique.rechercher(changement).operator*();
        temp.donnees.inserer({nompersonne, nomlieu});
    } else {
        //ajouter un noeud pour chaque date
        changement.donnees.inserer({nompersonne, nomlieu});
        historique.inserer(changement);
    }
}

ArbreAVL<std::string> Historique::localiser(const Intervalle& intervalle, const std::string& nompersonne) const
{
    ArbreAVL<std::string> resultats;
    Changement changement;
    changement.date = intervalle.debut;
    Changement changement_du_debut = historique.debut().operator*();
    // trouver le premier noeud = ou avant l'intervalle
    for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it != historique.fin(); ++it) {
        changement = *it;
        if (changement.date >= intervalle.debut) break;
        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt) {
            const Infos& donne = *jt;
            if (donne.nompersonne == nompersonne)
                changement_du_debut = changement;
        }
    }
    // iterer dans historique a partir de la
    for (ArbreAVL<Changement>::Iterateur it = historique.rechercher(changement_du_debut); it != historique.fin(); ++it)
    {
        changement = *it;
        if (changement.date >= intervalle.fin) break;
        //iterer les infos de chaque noeud
        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt) {
            const Infos& donne = jt.operator*();
            //ajouter les lieux ou on trouve que nompersonne est present
            if (donne.nompersonne == nompersonne) {
                if (donne.lieu != "?")
                    if (!resultats.contient(donne.lieu))
                        resultats.inserer(donne.lieu);
            }
        }

    }

    return resultats;
}

ArbreAVL<std::string> Historique::presences(const Intervalle& intervalle, const std::string& nomlieu) const
{
    ArbreAVL<std::string> resultats;
    ArbreAVL<std::string> deja_test;
    Changement changement;
    changement.date = intervalle.debut;
    //iterer a travers historique
    for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it !=historique.fin(); ++it) {
        changement = *it;
        //iterer dans les infos de chaque noeud d'historique
        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt)
        {
            const Infos& donne = jt.operator*();
            //check si on a deja traiter la personne trouvee
            if (!deja_test.contient(donne.nompersonne))
            {
                deja_test.inserer(donne.nompersonne);
                //check pour chaque personne dans historique si elle est localiser dans le lieu
                //au moment de l'intervalle
                if (localiser(intervalle, donne.nompersonne).contient(nomlieu))
                {
                    resultats.inserer(donne.nompersonne);
                }
            }
        }
    }
    return resultats;
}
ArbreAVL<std::string> Historique::frequentations(const Intervalle& intervalle, const std::string& nompersonne) const
{
    ArbreAVL<std::string> resultats;
    Date current_start = -1;
    std::string current_lieu;
    Changement changement;
    changement.date = intervalle.debut;
    Changement changement_du_debut = historique.debut().operator*();

    //trouver le noeud de depart
    for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it != historique.fin(); ++it) {
        changement = *it;
        if (changement.date >= intervalle.debut) break;
        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt) {
            const Infos& donne = *jt;
            if (donne.nompersonne == nompersonne)
                changement_du_debut = changement;
        }
    }
    //iterer dans historique a partir du noeud de depart
    for (ArbreAVL<Changement>::Iterateur it = historique.rechercher(changement_du_debut); it != historique.fin(); ++it)
    {
        changement = *it;
        if (changement.date >= intervalle.fin) break;

        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt)
        {
            const Infos& donne = *jt;

            if (donne.nompersonne == nompersonne)
            {
                // trouver le depart de l'intervalle lorsque le premier nom contenant nompersonne
                // est trouver
                if (current_start == -1)
                {
                    current_start = changement.date;
                    current_lieu = donne.lieu;
                }
                // Si la personne a changé de lieu, traiter l'intervalle avant de mettre à jour
                else if (donne.lieu != current_lieu)
                {
                    if (current_start < intervalle.debut) current_start = intervalle.debut;
                    //ajuster l'intervalle pour correspondre a celui ou nompersonne etait dans le lieu
                    Intervalle valid_interval = {current_start, changement.date};
                    //trouver les gens presents avec lui
                    ArbreAVL<std::string> presence_results = presences(valid_interval, current_lieu);

                    // ajouter les resultats de presence
                    for (ArbreAVL<std::string>::Iterateur presence_it = presence_results.debut(); presence_it != presence_results.fin(); ++presence_it)
                    {
                      if (*presence_it != nompersonne && changement.date)
                        resultats.inserer(*presence_it);
                    }

                    current_start = changement.date;
                    current_lieu = donne.lieu;
                }
            }
        }
    }

    // le dernier cas
    if (current_start != -1)
    {
        if (current_start < intervalle.debut) current_start = intervalle.debut;
        Intervalle valid_interval = {current_start, intervalle.fin};
        ArbreAVL<std::string> presence_results = presences(valid_interval, current_lieu);

        for (ArbreAVL<std::string>::Iterateur presence_it = presence_results.debut(); presence_it != presence_results.fin(); ++presence_it)
        {
          if (*presence_it != nompersonne)
            resultats.inserer(*presence_it);
        }
    }

    return resultats;
}

int Historique::duree_rencontres(const Intervalle& intervalle, const std::string& nompersonne1, const std::string& nompersonne2) const
{
    int duree = 0;
    Date debut_rencontre = -1;
    std::string lieu_p1 = "?", lieu_p2 = "?";

    //trouver le noeud de depart
    for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it != historique.fin(); ++it)
    {
        const Changement& changement = *it;
        if (changement.date >= intervalle.debut)
            break;

        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt)
        {
            const Infos& donne = *jt;
            if (donne.nompersonne == nompersonne1)
                lieu_p1 = donne.lieu;
            if (donne.nompersonne == nompersonne2)
                lieu_p2 = donne.lieu;
        }
    }

    if (nompersonne1 == nompersonne2)
    {
        //iterer a travers historique
        for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it != historique.fin(); ++it)
        {
            Changement changement = *it;
            if (changement.date >= intervalle.fin)
                break;
            if (changement.date < intervalle.debut)
                changement.date = intervalle.debut;

            //iterer a travers les infos de chaque noeud
            for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt)
            {
                const Infos& donne = *jt;
                if (donne.nompersonne == nompersonne1)
                    lieu_p1 = donne.lieu;
            }

            if (lieu_p1 != "?"){
                if (debut_rencontre == -1)
                    debut_rencontre = changement.date;
            }
            else if (debut_rencontre != -1){
                duree += changement.date - debut_rencontre;
                debut_rencontre = -1;
            }
        }
        //si dernier changement depasse intervalle
        if (debut_rencontre != -1)
            duree += intervalle.fin - debut_rencontre;

        return duree;
    }

    //iterer a travers historique
    for (ArbreAVL<Changement>::Iterateur it = historique.debut(); it != historique.fin(); ++it)
    {
        Changement changement = *it;
        if (changement.date >= intervalle.fin)
            break;
        if (changement.date < intervalle.debut)
            changement.date = intervalle.debut;

        //iterer a travers les infos de chaque noeud
        for (ArbreAVL<Infos>::Iterateur jt = changement.donnees.debut(); jt != changement.donnees.fin(); ++jt)
        {
            const Infos& donne = *jt;
            if (donne.nompersonne == nompersonne1)
                lieu_p1 = donne.lieu;
            if (donne.nompersonne == nompersonne2)
                lieu_p2 = donne.lieu;
        }

        //on detecte qu'ils se sont croiser
        if (lieu_p1 == lieu_p2 && lieu_p1 != "?")
        {
            if (debut_rencontre == -1)
                debut_rencontre = changement.date;
        }
        //on detecte qu'ils se sont quitter
        else if (debut_rencontre != -1)
        {
            duree += changement.date - debut_rencontre;
            debut_rencontre = -1;
        }
    }

    //si dernier changement depasse l'intervalle
    if (debut_rencontre != -1)
        duree += intervalle.fin - debut_rencontre;

    return duree;
}
