//
// Created by Vincent on 24/04/2019.
//

#include "Automate.h"
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

Automate::Automate(int _nb_symb, int _nb_etats,
        int _nb_init, std::vector<int> _init,
        int _nb_term, std::vector<int> _term,
        int _nb_trans, std::vector<Transition> _transitions){
        alphabet = get_alpha();
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

    cout << "||--- " << nb_trans << " transitions : " << endl;
    for (int i = 0; i<transitions.size(); i++) {
        cout << "||------ ";
        transitions[i].print();
        cout << endl;
    }
    cout << endl;
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

Automate::Automate(string path) {
    ifstream fichier(path);
    if (fichier) {

        string temp;

        getline(fichier, temp);
        nb_symb = stoi(temp);

        getline(fichier, temp);
        nb_etats = stoi(temp);

        fichier >> temp;
        nb_init = stoi(temp);

        for (int i = 0; i< nb_init; i++) {
            fichier >> temp;
            init.push_back(stoi(temp));
        }

        fichier >> temp;
        nb_term = stoi(temp);

        for (int i = 0; i < nb_term; i++) {
            fichier >> temp;
            term.push_back(stoi(temp));
        }

        fichier >> temp;
        nb_trans = stoi(temp);

        for (int i = 0; i < nb_trans; i++) {
            string p, q;
            char symb;

            fichier >> p;
            fichier >> symb;
            fichier >> q;
            Transition trans_temp(stoi(p), symb, stoi(q));

            transitions.push_back(trans_temp);
        }

        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        cerr << "ERROR" << strerror(errno);
    }
}

bool Automate::est_automate_complet() {
    bool ok;

    // Le nombre de transitions est égal au produit du nombre de caractères de l'alphabet et du nombre d'états

    if (nb_trans < (nb_symb*nb_etats)){
        ok = false;
    }

    return ok;
}



Automate Automate::completion() {
    Automate temp(*this);

    //ajout de l'etat poubelle
    temp.nb_etats ++;

    //ajout des transitions
    vector<char> alpha_temp;
    for (int i = 0 ; i < temp.nb_etats ; i ++ ){ //pour chaque état de l'automate
        alpha_temp = get_alpha(); // creation du tableau temporaire contenant les symboles de l'alphabet
        for (int j = 0 ; j < temp.nb_trans ; j++){ // pour chaque transition existante
            if(i == temp.transitions[j].getP()){ // si l'etat i à une transition sortante
                alpha_temp.erase(remove(alpha_temp.begin(), alpha_temp.end(), temp.transitions[j].getSymb()), alpha_temp.end()); // le caractere est supprimé du tableau temporaire
            }
        }
        if (!alpha_temp.empty()){ // si pour l'etat i, il existe des symboles sans transition (les symboles restants dans le tableau)
            for (int j = 0 ; j < alpha_temp.size() ; j++){ //on ajoute une transition de i vers le dernier état = etat poubelle
                temp.nb_trans ++;
                temp.transitions.emplace_back(i, alpha_temp[j], nb_etats);
            }
        }
        alpha_temp.clear(); //le tableau est remis à vide pour le prochain état
    }
    return temp;
}

void Automate::setNbEtats(int nbEtats) {
    nb_etats = nbEtats;
}

void Automate::determinisation() {
    vector <int> etat_temp;
    for (int i = 0 ; i < init.size() ; i++){

    }
}

vector<char> Automate::get_alpha() const {
    vector<char> alphabet;

    for(int unsigned i = 0; i < nb_trans; i++){
        char key = transitions[i].getSymb();

        if (find(alphabet.begin(), alphabet.end(), key) == alphabet.end()) {
            alphabet.push_back(key);

        }
    }
    return alphabet;
}


const vector<Transition> &Automate::getTransitions() const {
    return transitions;
}


//Version où on renvoie le tableau d'etat terminaux
/*
vector<int> Automate::langage_complementaire() {
    //Pour chaque état du nouvel automate (de 1 à n)
    //Si l'etat n'est pas dans la liste des etats terminaux de l'automate à completer
    //Alors on l'ajoute à la liste des etats terminaux de l'automate complet
    vector<int> etat_term_complementaire;
    for (int i = 0 ; i < nb_etats ; i++){
        for (int j = 0 ; j < nb_term ; j ++){
            if (i != term[j]){
                etat_term_complementaire.push_back(i);
            }
        }
    }
    return etat_term_complementaire;
}*/

//Version où on renvoie l'automate reconnaissant le langage complementaire
Automate Automate::langage_complementaire() {
    Automate temp(*this);
    //Pour chaque état du nouvel automate (de 1 à n)
    //Si l'etat n'est pas dans la liste des etats terminaux de l'automate à completer
    //Alors on l'ajoute à la liste des etats terminaux de l'automate complet
    vector<int> etat_term_complementaire;
    for (int i = 0 ; i < nb_etats ; i++){
        for (int j = 0 ; j < nb_term ; j ++){
            if (i != term[j]){
                etat_term_complementaire.push_back(i);
            }
        }
    }
    temp.term.clear();
    temp.setTerm(etat_term_complementaire);
    return temp;
}



void Automate::setTerm(std::vector<int> _term) {
    term.clear();
    term = _term;
}

Automate &Automate::operator=(const Automate & Af) {
        nb_symb = Af.nb_symb;
        nb_etats = Af.nb_etats;
        nb_init = Af.nb_init;
        init = Af.init;
        nb_term = Af.nb_term;
        term = Af.term;
        nb_trans = Af.nb_trans;
        transitions = Af.transitions;
        return *this;
}

