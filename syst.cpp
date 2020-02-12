#include "syst.h"

std::pair<int, Fraction> pivot(std::vector<Fraction>& colonne) {
    for (int indice = 0; indice < colonne.size(); indice++)
        if (colonne[indice] != 0)
            return {indice, colonne[indice]};

    //pas de pivot, on return {-1,0}
    return {-1,0};
}

std::vector<Fraction> genereColonne(std::vector<std::vector<Fraction> >& systeme, int idColonne) {
    if (systeme.size() == 0) return std::vector<Fraction>(0);

    std::vector<Fraction> resultat = std::vector<Fraction>(systeme[0].size() - idColonne, 0);

    for (int idLigne = idColonne; idLigne < systeme.size(); idLigne++) {
        resultat[idLigne] = systeme[idLigne][idColonne];
    }

    return resultat;
}

Syst::Syst(int nbInconnues, int nbEquations) {
    _equations = std::vector<std::vector<Fraction> >(nbEquations, std::vector<Fraction>(nbInconnues+1));

    for (int i = 0; i < nbEquations; i++) {
        std::cout << "Equation n°" << i+1 << std::endl;

        for (int j = 0; j < nbInconnues; j++) {
            std::cout << "Quel est le " << j+1 << "e coefficient de cette équation (entier seulement) ?" << std::endl;

            int coef;
            std::cin >> coef;
            _equations[i][j] = Fraction(coef);
        }

        std::cout << "A quoi la ligne est-elle égale ?" << std::endl;
        int reponse;
        std::cin >> reponse;
        _equations[i][nbInconnues] = Fraction(reponse);
    }
}

std::string Syst::affi() {
    std::string affichage = "";

    for (std::vector<Fraction>& ligne : _equations) {
        for (int i = 0; i < ligne.size() - 1; i++) {
            affichage += to_string(ligne[i]) + " ";
        }

        affichage += "= " + to_string(ligne[ligne.size() - 1]) += ",\n";
    }

    return affichage;
}

std::vector<std::string> Syst::resolution() {
    int nbInconnues = 0;
    if (_equations.size() != 0) nbInconnues = _equations[0].size() - 1;
    else return std::vector<std::string>(0);

    std::vector<std::vector<Fraction> > systeme = std::vector<std::vector<Fraction> >(_equations.size(), std::vector<Fraction>(0));
    for (int idLigne = 0; idLigne < _equations.size(); idLigne++)
        for (int idColonne = 0; idColonne < _equations[idLigne].size(); idColonne++)
            systeme[idLigne].push_back(Fraction(_equations[idLigne][idColonne]));

    //On applique la méthode du pivot de gauss pour écheloner le système
    for (int idInconnue = 0; idInconnue < nbInconnues; idInconnue++) {
        std::vector<Fraction> colonne = genereColonne(systeme, idInconnue);
        std::pair<int, Fraction> infosPivot = pivot(colonne);
        //infosPivot.first -> numéro de ligne
        //infosPivot.second -> valeur du pivot

        if (infosPivot.first != -1) {
            //on met la ligne du pivot de la i-ème inconnue en i-ème
            std::vector<Fraction> temp = systeme[idInconnue];
            systeme[idInconnue] = systeme[infosPivot.first];
            systeme[infosPivot.first] = temp;

            //on normalise la ligne du pivot pour mettre le pivot à 1, c'est plus facile
            for (int i = 0; i < nbInconnues; i++) systeme[idInconnue][i] /= infosPivot.second;

            std::cout << "Hello" << std::endl;
            //on retire l'inconnue en cours de traitement dans toutes les lignes suivantes
            for (int idLigne = idInconnue + 1; idLigne < systeme.size(); idLigne++)
                if (systeme[idLigne][idInconnue] != 0)
                    for (int i = 0; i < nbInconnues; i++)
                        systeme[idLigne][i] -= systeme[idLigne][idInconnue] * systeme[idInconnue][i];
        }

        _equations = systeme;
    }

    return std::vector<std::string>(0);
}
