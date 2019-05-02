//
// Created by Vincent on 02/05/2019.
//

#ifndef TESTY_PROCESSUS_H
#define TESTY_PROCESSUS_H

#include "Transition.h"
#include "Automate.h"
#include "fonction.h"

Automate a_choix_automate();
Automate b_determinisation(Automate);
Automate c_minimisation(Automate);
void d_lecture_de_mot(Automate);
Automate e_langage_complementaire(Automate);
Automate f_standardisation(Automate);

#endif //TESTY_PROCESSUS_H
