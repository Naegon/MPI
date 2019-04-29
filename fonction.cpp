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

bool string_in_vector(string str, vector<string> vector) {
    bool ok = false;
    for (int i = 0 ; i < vector.size() ; i++){
        if (str == vector[i]){
            ok = true;
        }
    }
    return ok;
}

bool int_in__element_of_vector(int entier, std::vector<std::string> vector) {

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


