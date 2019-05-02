#include <iostream>
#include <string>
#include "Transition.h"
#include "Automate.h"
#include <vector>
#include "fonction.h"
#include "processus.h"
using namespace std;

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
    }while(!erreur);
    return again;
}


int main() {
    Automate af(0);
    bool recommencer;

    do{
        af = a_choix_automate();
        af = b_determinisation(af);
        af = c_minimisation(af);
        d_lecture_de_mot(af);
        af = e_langage_complementaire(af);
        af = f_standardisation(af);
        recommencer = again();
    }while (recommencer);
    return 0;
}
