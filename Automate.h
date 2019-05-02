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
        std::vector<char> alphabet;
        int nb_init;
        std::vector<int> init;
        int nb_term;
        std::vector<int> term;
        int nb_trans;
        std::vector<Transition> transitions;
        int nb_symb;
        int nb_etats;
        std::vector<std::string> etat_compose;


    public :
        //constructeur
        Automate(std::string path);
        Automate(int, int, int, std::vector<int>, int, std::vector<int>, int, std::vector<Transition>, std::vector<std::string>);
        Automate(Automate&);
        Automate(int);

        //test caracteristique automate
        bool est_automate_asynchrone();
        bool est_automate_standard();
        bool est_automate_deterministe();
        bool est_automate_complet();

        //Processus
        Automate completion();
        Automate standardisation();
        Automate determinisation();
        Automate determinisation_asynchrone();
        Automate determinisation_et_completion();
        Automate determinisation_et_completion_asynchrone();
        Automate minimisation();
        //std::vector<int> langage_complementaire();
        Automate langage_complementaire();


        //Get et set
        std::vector<char> get_alpha() const;
        void setNbEtats(int nbEtats);
        void setTerm(std::vector<int>);
        const std::vector<Transition> &getTransitions() const;
        int getNb_init() const;
        int getNb_term() const;
        std::vector<int> getInit() const;
        std::vector<int> getTerm() const;
        int getNb_trans() const;


        //Affichage
        void print() const;
        void print_table_transition();
        void afficher_automate_deterministe_complet();

        //Autre
        Automate& operator=(const Automate&);
        std::vector<std::string> determiner_transition_epsilon();
        std::vector<std::string> determiner_transition_epsilon(std::vector<std::string>);
        std::string determiner_transition_epsilon(std::string);
        void add_epsilon_alphabet();

};

#endif //TESTY_AUTOMATE_H
