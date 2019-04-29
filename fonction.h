//
// Created by Vincent on 28/04/2019.
//

#ifndef TESTY_FONCTION_H
#define TESTY_FONCTION_H

#include <string>
#include <iostream>
#include <vector>

void ordonner_string(std::string&);
void ordonner_vector_string(std::vector<std::string>&);
void supprimer_doublon_string(std::string&);
void supprimer_doublon_vector_string(std::vector<std::string>&);
bool string_in_vector(std::string, std::vector<std::string>);
bool int_in__element_of_vector(int, std::vector<std::string>);
void changement_numero_etat(std::vector<std::string>, std::vector<std::string>&);
#endif //TESTY_FONCTION_H
