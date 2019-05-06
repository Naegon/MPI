#include <iostream>
#include <string>
#include "Transition.h"
#include "Automate.h"
#include <vector>
#include "fonction.h"
#include "processus.h"
using namespace std;

/**
 * Saisie utilisateur pour recommencer le processus avec un autre automate
 * @return booleen
 */
bool again(){
    string choix;
    bool again;
    bool erreur;
    do {
        erreur = true;
        cout << "||---- Voulez-vous continuer d'utiliser un automate ?" << endl;
        cout << "||---- Pour continuer taper 1" << endl;
        cout << "||---- Pour arreter taper 0" << endl;
        cout << "||----> Votre choix :";
        cin >> choix;
        if (choix == "0") {
            again = false;
        } else if (choix == "1") {
            again = true;
        } else {
            erreur = false;
        }
    }while(!erreur); //boucle si saisie incorrecte
    return again;
}


int main() {
    Automate af(0);
    bool recommencer;
    do{
        //enchainement des traitements d'un automate
        af = a_choix_automate();
        if (af.getNb_trans() != (-1)){ //si il n'y a pas eu d'erreur à l'ouverture du fichier
            af.print_table_transition();
            af = b_determinisation(af);
            af = c_minimisation(af);
            d_lecture_de_mot(af);
            af = e_langage_complementaire(af);
            af = f_standardisation(af);
        }
        recommencer = again();
    }while (recommencer);
    return 0;
}
