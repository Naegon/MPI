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
        int nb_symb;
        int nb_etats;
        int nb_init;
        std::vector<int> init;
        int nb_term;
        std::vector<int> term;
        int nb_trans;
        std::vector<Transition> transitions;
public:
    const std::vector<Transition> &getTransitions() const;

public :
        Automate(std::string path);
        Automate(int, int, int, std::vector<int>, int, std::vector<int>, int, std::vector<Transition>);
        Automate(Automate&);
        bool est_automate_asynchrone();
        bool est_automate_standart();
        bool est_automate_deterministe();
        bool est_automate_complet();
        void completion();
        void print() const;
};

#endif //TESTY_AUTOMATE_H
