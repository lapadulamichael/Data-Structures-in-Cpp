/*
  INF3105 - Structures de données et algorithmes

  Squellette pour le TP2
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include "historique.h"

int main(int argc, const char** args)
{
    std::istream* entree;
    std::ifstream* entree_fichier = NULL;

    if(argc>1){
         entree = entree_fichier = new std::ifstream(args[1]);
         if(entree->fail())
             std::cerr << "Erreur d'ouverture du fichier '" << args[1] << "'" << std::endl;
    }else
         entree = &std::cin;
   
    Historique historique;
    std::string nompersonne, nomlieu, nompersonne2;
    Date instant;
    Intervalle intervalle;
    
    while(*entree){
         std::string cmd;
         *entree >> cmd;
         if(!(*entree)) break;
         
         if(cmd=="trace"){
             *entree >> instant >> nompersonne >> nomlieu;
             historique.trace(instant, nompersonne, nomlieu);
         }
         else if(cmd=="localiser"){
             *entree >> intervalle >> nompersonne;
             ArbreAVL<std::string> lieux = historique.localiser(intervalle, nompersonne);
             for(ArbreAVL<std::string>::Iterateur iter=lieux.debut();iter;++iter)
                 std::cout << *iter << " ";
             std::cout << std::endl;
         }
         else if(cmd=="presences"){
             *entree >> intervalle >> nomlieu;
             ArbreAVL<std::string> personnes = historique.presences(intervalle, nomlieu);
             for(ArbreAVL<std::string>::Iterateur iter=personnes.debut();iter;++iter)
                 std::cout << *iter << " ";
             std::cout << std::endl;
         }
         else if(cmd=="frequentations"){
             *entree >> intervalle >> nompersonne;
             ArbreAVL<std::string> personnes = historique.frequentations(intervalle, nompersonne);
             for(ArbreAVL<std::string>::Iterateur iter=personnes.debut();iter;++iter)
                 std::cout << *iter << " ";
             std::cout << std::endl;
         }
         else if(cmd=="duree_rencontres"){
             *entree >> intervalle >> nompersonne >> nompersonne2;
             int dr = historique.duree_rencontres(intervalle, nompersonne, nompersonne2);
             std::cout << dr << std::endl;
         }
    }

    delete entree_fichier; // delete est sécuritaire même si entree_fichier==NULL

    return 0;
}

