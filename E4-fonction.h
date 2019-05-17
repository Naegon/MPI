#ifndef TESTY_E4_FONCTION_H
#define TESTY_E4_FONCTION_H

#include <string>
#include <iostream>
#include <vector>
#include "E4-Automate.h"

//Chaine et vector
void ordonner_vector_string(std::vector<std::string>&);
void ordonner_vector_transition(std::vector<Transition>&);
void ordonner_vector_int(std::vector<int>&);
void supprimer_doublon_string(std::string&);
void supprimer_doublon_vector_string(std::vector<std::string>&);
void supprimer_doublon_vector_int(std::vector<int>&);
bool string_in_vector(std::string, std::vector<std::string>);
bool int_in_etat_compose(std::string, int);
bool int_in__element_of_vector(int, std::vector<int>);
int get_nb_char_max_in_string(std::vector<std::string>);


//Automate asynchrone
void changement_numero_etat(std::vector<std::string>, std::vector<std::string>&);
std::string get_transition_epsilon(int, const Automate&);
std::string get_transition_epsilon(std::string, const Automate&);

//Transition
bool transition_egale(std::vector<Transition>, std::vector<Transition>);
int get_taille_max_table_transition(std::vector<Transition>);
void affichage_partition(std::vector<Transition>, std::vector<int>, int, std::vector<char>);

//Lecture de mot
void lire_mot(std::string& );
bool reconnaitre_mot(std::string, Automate);

#endif //TESTY_E4_FONCTION_H
