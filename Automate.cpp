//
// Created by Vincent on 24/04/2019.
//

#include "Automate.h"
#include <iostream>

using namespace std;

Automate::Automate(int _nb_symb, int _nb_etats,
        int _nb_init, std::vector<int> _init,
        int _nb_term, std::vector<int> _term,
        int _nb_trans, std::vector<Transition> _transitions){
    nb_symb = _nb_symb;
    nb_etats = _nb_etats;
    nb_init = _nb_init;
    init = _init;
    nb_term = _nb_term;
    term = _term;
    nb_trans = _nb_trans;
    transitions = _transitions;
}

void Automate::print() const {
    cout << "Automate :" << endl;
    cout << "||--- Etats initiaux : ";
    for (int i = 0; i<init.size(); i++) {
        cout << init[i] << " ";
    }
    cout << endl;

    cout << "||--- Etats terminaux : ";
    for (int i = 0; i<term.size(); i++) {
        cout << term[i] << " ";
    }
    cout << endl;

    cout << "||--- Transitions : " << endl;
    for (int i = 0; i<transitions.size(); i++) {
        cout << "||------ ";
        transitions[i].print();
    }
}
