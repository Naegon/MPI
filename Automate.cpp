//
// Created by Vincent on 24/04/2019.
//

#include "Automate.h"
#include <iostream>
#include <cstring>

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

Automate::Automate(Automate& A){
    nb_symb = A.nb_symb;
    nb_etats = A.nb_etats;
    nb_init = A.nb_init;
    init = A.init;
    nb_term = A.nb_term;
    term = A.term;
    nb_trans = A.nb_trans;
    transitions = A.transitions;
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
        cout << endl;
    }
    cout << endl;
}

Automate::Automate(string path) {
    ifstream fichier(path);
    if (fichier) {
        string temp;

        getline(fichier, temp);
        nb_symb = stoi(temp);
        cout << nb_symb << endl;

        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        cerr << "ERROR" << strerror(errno);
    }
}

const vector<Transition> &Automate::getTransitions() const {
    return transitions;
}

bool Automate::est_automate_asynchrone() {
    bool ok = true;
    cout << "Automate asynchrone ? " << endl;
    for(int i = 0 ; i < transitions.size() ; i++){
        if (transitions[i].getSymb() == '*'){
            ok = false;
            cout << "||--- La transition ";
            transitions[i].print();
            cout << " contient une transition epsilon" << endl;
        }
    }
    if (ok){
        cout << "||--- L'automate est asynchrone" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas asynchrone" << endl;
    }
    return ok;
}

bool Automate::est_automate_standart() {
    bool ok = true;
    cout << "Automate standart ? " << endl;
    if (nb_init > 1){
        cout << "||--- L'automate n'est pas standart car plusieurs etats initiaux" << endl;
        return false;
    }

    for(int i = 0 ; i < transitions.size() ; i++){
        if (transitions[i].getQ() == init[0]){
            ok = false;
            cout << "||--- La transition ";
            transitions[i].print();
            cout << " entre sur l'etat initial" << endl;
        }
    }
    if (ok){
        cout << "||--- L'automate est standart" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas standart" << endl;
    }
    return ok;
}

bool Automate::est_automate_deterministe() {
    bool ok = true;
    cout << "Automate deterministe ? " << endl;
    if (nb_init > 1){
        cout << "||--- L'automate n'est pas deterministe car il a plusieurs d'un etats initiaux" << endl;
        return false;
    }

    for (int i = 0 ; i < transitions.size() ; i++){
        for (int j = (i+1) ; j < transitions.size() ; j++){
            if(i != j){
                if (((transitions[i].getP() == transitions[j].getP()) and (transitions[i].getQ() != transitions[j].getQ())) and (transitions[i].getSymb() == transitions[j].getSymb())){
                    ok = false;
                    cout << "||--- La transition ";
                    transitions[i].print();
                    cout << " et la transition ";
                    transitions[j].print();
                    cout << " ont le meme symbole et etat de depart mais un etat d'arrive different" << endl;
                }
            }
        }
    }

    if (ok){
        cout << "||--- L'automate est deterministe" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas deterministe" << endl;
    }
    return ok;
}

bool Automate::est_automate_complet() {
    bool ok;

    // Le nombre de transitions est égal au produit du nombre de caractères de l'alphabet et du nombre d'états

    if (nb_trans < (nb_symb*nb_etats)){
        ok = false;
    }

    return ok;
}

void Automate::completion() {
    Automate complet(*this); //création de l'automate qui sera renvoyé

    complet.setNbEtats(complet.nb_etats+1);

    for (int i = 0 ; i < nb_etats ; i++){ // pour chaque état de l'autpomate initial

    }

}

void Automate::setNbEtats(int nbEtats) {
    nb_etats = nbEtats;
}


