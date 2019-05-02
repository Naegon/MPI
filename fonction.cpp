//
// Created by Vincent on 28/04/2019.
//

#include "fonction.h"
#include <iostream>
#include <algorithm>

using namespace std;

void ordonner_string(string& str) {
    sort(str.begin(), str.end());
}

void ordonner_string_tri_a_bulle(string & str) {
    bool tab_en_ordre = false;
    int taille = str.size();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < (taille-1) ; i++)
        {
            if(str[i] > str[i+1])
            {
                swap(str[i],str[i+1]);
                tab_en_ordre = false;
            }
        }
        taille--;
    }
}

void supprimer_doublon_string(std::string & s) {

    for (int i = 0 ; i < s.size(); i++ )
    {
        int j = i + 1;
        while ( j < s.size() )
        {
            if ( s[i] == s[j] )
            {
                s.erase( j, 1 );
            }
            else
            {
                ++j;
            }
        }
    }
}

void supprimer_doublon_vector_string(vector<string>& vector) {
    vector.erase( unique( vector.begin(), vector.end() ), vector.end() );
}

void supprimer_doublon_vector_int(vector<int>& vector) {
    vector.erase( unique( vector.begin(), vector.end() ), vector.end() );
}

bool string_in_vector(string str, vector<string> vector) {
    bool ok = false;
    for (int i = 0 ; i < vector.size() ; i++){
        if (str == vector[i]){
            ok = true;
        }
    }
    return ok;
}

bool int_in__element_of_vector(int etat, vector<int> vector) {
    for(int i = 0 ; i < vector.size() ; i++){
        if(etat == vector[i]){
            return true;
        }
    }
    return false;
}


void changement_numero_etat(std::vector<std::string> etat_traite, std::vector<std::string>& vector) {
    //pour chaque etat créé, si on le trouve dans vector, on change la valeur par son indice
    for (int i = 0 ; i < vector.size() ; i++){
        bool changed = false;
        for (int j = 0 ; j < etat_traite.size() ; j++){
            if ((etat_traite[j] == vector[i]) and (!changed)){ //(!changed) car il ne faut pas que la valeur soit modifiée 2 fois
                vector[i] = to_string(j);
                changed = true;
            }
        }
    }
}

void ordonner_vector_string(vector<string>& vector) {
    bool tab_en_ordre = false;
    int taille = vector.size();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < (taille-1) ; i++)
        {
            int a = stoi(vector[i]);
            int b = stoi(vector[i+1]);
            if(a>b)
            {
                swap(vector[i],vector[i+1]);
                tab_en_ordre = false;
            }
        }
        taille--;
    }
}

void ordonner_vector_transition(vector<Transition>& vector){
    bool tab_en_ordre = false;
    int taille = vector.size();
    int p0 = 0;
    int p1 = 0;
    int s0 = 0;
    int s1 = 0;
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < (taille-1) ; i++)
        {
            p0 = vector[i].getP();
            p1 = vector[i+1].getP();
            s0 = (int) vector[i].getSymb();
            s1 = (int) vector[i+1].getSymb();
            if(((p0 == p1) and (s1<s0)) or (p1<p0)){
                swap(vector[i],vector[i+1]);
                tab_en_ordre = false;
            }
        }
    }
}


string get_transition_epsilon(int etat, const Automate& automate) {
    string fermeture;
    vector<string> etat_a_traiter;
    vector<string> etat_traite;
    vector<Transition> transition;

    transition = automate.getTransitions();
    etat_a_traiter.push_back(to_string(etat));
    do{
        for(int i = 0 ; i < automate.getNb_trans() ; i++){
            if ((transition[i].getP() == etat) and (transition[i].getSymb() == '*')){
                string str = to_string(transition[i].getQ());
                if (!(string_in_vector(str, etat_a_traiter)) and (!string_in_vector(str, etat_traite))){
                    etat_a_traiter.push_back(str);
                }
            }
        }
        etat_traite.push_back(to_string(etat));
        etat_a_traiter.erase(etat_a_traiter.begin());
        etat = stoi(etat_a_traiter[0]);
    }while(!etat_a_traiter.empty());

    ordonner_vector_string(etat_traite);
    for (int i = 0 ; i < etat_traite.size() ; i++){
        fermeture += etat_traite[i];
        if ((i+1) != etat_traite.size()){
            fermeture += ".";
        }
    }

    return  fermeture;
}

string get_transition_epsilon(string etat, const Automate& automate){
    string fermeture;
    vector<string> etat_a_traiter;
    vector<string> etat_traite;
    vector<Transition> transition;

    transition = automate.getTransitions();
    supprimer_doublon_string(etat);

    for (int i = 0 ; i < etat.size() ; i++){
        int x = etat[i] - 48;
        if (x >= 0){
            etat_a_traiter.push_back(to_string(etat[i]-48));
        }
    }
    do{
        etat = etat_a_traiter[0];
        int x = stoi(etat);
        for(int i = 0 ; i < automate.getNb_trans() ; i++){
            if ((transition[i].getP() == x) and (transition[i].getSymb() == '*')){
                string str = to_string(transition[i].getQ());
                if (!(string_in_vector(str, etat_a_traiter)) and (!string_in_vector(str, etat_traite))){
                    etat_a_traiter.push_back(str);
                }
            }
        }
        etat_traite.push_back(etat);
        etat_a_traiter.erase(etat_a_traiter.begin());
    }while(!etat_a_traiter.empty());

    ordonner_vector_string(etat_traite);
    for (int i = 0 ; i < etat_traite.size() ; i++){
        fermeture += etat_traite[i];
        if ((i+1) != etat_traite.size()){
            fermeture += ".";
        }
    }
    return fermeture;
}

bool transition_egale(vector<Transition> transition_0, vector<Transition> transition_1) {

    for (int i = 0 ; i < transition_0.size() ; i++){
        char s0 = transition_0[i].getSymb();
        int q0 = transition_0[i].getQ();
        char s1 = transition_1[i].getSymb();
        int q1 = transition_1[i].getQ();
        if ((s0 != s1) or (q0 != q1)){
            return false;
        }
    }
    return true;
}

int get_nb_char_max_in_string(vector<string> vector) {
    int taille = 0;
    for (int i = 0 ; i < vector.size(); i++) {
        if (vector[i].size() > taille) {
            taille = vector[i].size();
        }
    }
    return taille;
}

int get_taille_max_table_transition(std::vector<Transition> transition) {
    int taille_max = 1;
    int taille_etat = 1;
    int p;
    char symb = ' ';
    for (int i = 0 ; i < transition.size() ; i++){
        if((transition[i].getP() == p) and (transition[i].getSymb() == symb)){
            taille_etat += to_string(transition[i].getQ()).size(); //l'etat q et la virgule de separation
            taille_etat++;
        }
        else{
            p = transition[i].getP();
            symb = transition[i].getSymb();
            if (taille_etat > taille_max){
                taille_max = taille_etat;
            }
            taille_etat = to_string(transition[i].getQ()).size();
        }
    }
    return taille_max;
}






