//
// Created by Vincent on 02/05/2019.
//

#include "processus.h"
#include <iostream>
using namespace std;

Automate a_choix_automate() {
    string choix;
    const int nb_files = 16;

    cout << endl;
    cout << "*****************************************************" << endl;
    cout << "*****            Choix de l'automate            *****" << endl;
    cout << "*****************************************************" << endl;
    cout << "||---- " << nb_files << " automates disponibles " << endl;
    cout << "||-----> Votre choix : ";
    cin >> choix;

    while (stoi(choix) < 1 || stoi(choix) > nb_files) {
        cout << "||---- Choisissez un nombre entre 1 et " << nb_files << endl;
        cout << "||-----> Votre choix :";
        cin >> choix;
    }

    cout << "||------ Ouverture de l'automate " << choix << endl << endl;

    choix = "Automates_test/L2-E4-" + choix + ".txt";

    Automate af(choix);
    af.print_table_transition();
    return af;
}

Automate b_determinisation(Automate af) {
    Automate afdc(0);
    cout << "*****************************************************" << endl;
    cout << "*****      Determinisation et/ou completion     *****" << endl;
    cout << "*****************************************************" << endl;
    if (af.est_automate_asynchrone()){
        afdc = af.determinisation_et_completion_asynchrone();
    }
    else{
        if(af.est_automate_deterministe()){
            if(af.est_automate_complet()){
                cout << "Aucun traitement effectue car l'automate est deja deterministe et complet" << endl;
                afdc = af;
            }
            else{
                afdc = af.completion();
            }
        }
        else{
            afdc = af.determinisation_et_completion();
        }
    }
    afdc.afficher_automate_deterministe_complet();
    return afdc;
}

Automate c_minimisation(Automate afdc) {
    cout << "*****************************************************" << endl;
    cout << "*****                Minimisation               *****" << endl;
    cout << "*****************************************************" << endl;
    Automate afdcm(0);
    afdcm = afdc.minimisation();
    afdcm.afficher_automate_deterministe_complet();
    return afdcm;
}

void d_lecture_de_mot() {

}

