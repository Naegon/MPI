//
// Created by Vincent on 24/04/2019.
//

#include <vector>
#include <string>
#include "Transition.h"
#include <fstream>

#ifndef TESTY_AUTOMATE_H
#define TESTY_AUTOMATE_H


class Automate {

private:
        int nb_init;
        std::vector<int> init;
        int nb_term;
        std::vector<int> term;
        int nb_trans;
        std::vector<Transition> transitions;
        int nb_symb;
        int nb_etats;



    public :
        //constructeur
        Automate(std::string path);
        Automate(int, int, int, std::vector<int>, int, std::vector<int>, int, std::vector<Transition>);
        Automate(Automate&);

        //test caracteristique automate
        bool est_automate_asynchrone();
        bool est_automate_standart();
        bool est_automate_deterministe();
        bool est_automate_complet();

        //Processus
        void completion();
        void determinisation();
        std::vector<int> langage_complementaire();

        //Get et set
        std::vector<char> get_alpha() const;
        void setNbEtats(int nbEtats);
        void setTerm(std::vector<int>);
        const std::vector<Transition> &getTransitions() const;

        //Autre
        void print() const;
        Automate& operator=(const Automate&);


};

#endif //TESTY_AUTOMATE_H
