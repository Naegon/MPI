//
// Created by Vincent on 28/04/2019.
//

#ifndef TESTY_FONCTION_H
#define TESTY_FONCTION_H

#include <string>
#include <iostream>
#include <vector>
#include "Automate.h"

//Chaine et vector
void ordonner_string(std::string&);
void ordonner_string_tri_a_bulle(std::string&);
void ordonner_vector_string(std::vector<std::string>&);
void supprimer_doublon_string(std::string&);
void supprimer_doublon_vector_string(std::vector<std::string>&);
void supprimer_doublon_vector_int(std::vector<int>&);
bool string_in_vector(std::string, std::vector<std::string>);
bool int_in__element_of_vector(int, std::vector<int>);
int get_nb_char_max_in_string(std::vector<std::string>);


//Automate asynchrone
void changement_numero_etat(std::vector<std::string>, std::vector<std::string>&);
std::string get_transition_epsilon(int, const Automate&);
std::string get_transition_epsilon(std::string, const Automate& );

//Transition
bool transition_egale(std::vector<Transition>, std::vector<Transition>);

#endif //TESTY_FONCTION_H
