#ifndef DEF_SYST
#define DEF_SYST

#include <iostream>
#include <string>
#include <vector>

#include "fraction.h"

class Syst {
private:
    std::vector<std::vector<Fraction> > _equations;
public:
    /** Constructeur du système linéaire
     *  @param le nombre d'inconnues du système
     *  @param le nombre d'équations du système
    **/
    Syst(int nbInconnues, int nbEquations);

    /** Génère l'affichage du système avec les coefficients et les inconnues
     *  @return un string qui représente le système
    **/
    std::string affi();

    /** Résolution du système : trouve s'il y a une solution ou pas. Si non, renvoie un vector vide.
                                si oui, renvoie un vector<string> représentant les solutions (string pour
                                pouvoir représenter les variables secondaires formellement)
    **/
    std::vector<std::string> resolution();
};

/** Trouve la position (n° de ligne) et la valeur du pivot d'une colonne
  * @param un vector<int>, la colonne dont on cherche le pivot
  * @return une pair contenant le numéro de ligne du pivot et sa valeur (si pas de pivot, renvoie {-1,0})
**/
std::pair<int, Fraction> pivot(std::vector<Fraction>& colonne);

/** Génère un vector<int> d'une colonne à partir d'un système et du numéro de colonne
  * @param le vector<vector<int>> représentant le système d'équations
  * @param l'entier qui est le numéro de colonne
  * @return le vector<int> de la colonne correspondante
**/
std::vector<Fraction> genereColonne(std::vector<std::vector<Fraction> >& systeme, int idColonne);

#endif
