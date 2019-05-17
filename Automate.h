#ifndef TESTY_AUTOMATE_H
#define TESTY_AUTOMATE_H

#include <vector>
#include <string>
#include "Transition.h"
#include <fstream>

class Automate {


    private:
        int nb_init;
        std::vector<int> init;
        int nb_term;
        std::vector<int> term;
        int nb_trans;
        std::vector<Transition> transitions; //vecteur de Transition <p><symbole><q>
        int nb_symb;
        int nb_etats;
        std::vector<std::string> etat_compose; //vecteur des etats composé (Ex : 0.2.5.11)
        std::vector<char> alphabet;

    public :
        //constructeur
        Automate(std::string path);
        Automate(Automate&);
        Automate(int);

        //test caracteristique automate
        bool est_automate_asynchrone();
        bool est_automate_asynchrone_simple();//sans affichage
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
        Automate langage_complementaire();

        //Get et set
        std::vector<char> get_alpha() const;
        const std::vector<Transition> &getTransitions() const;
        int getNb_term() const;
        std::vector<int> getInit() const;
        std::vector<int> getTerm() const;
        int getNb_trans() const;
        int getNbEtats() const;
        const std::vector<char> &getAlphabet() const;

        //Affichage
        void print_table_transition();
        void afficher_automate_deterministe_complet();//sert aussi pour l'automate minimal

        //Autre
        Automate& operator=(const Automate&);
        std::string determiner_transition_epsilon(std::string);
        void add_epsilon_alphabet();

};

#endif //TESTY_AUTOMATE_H
