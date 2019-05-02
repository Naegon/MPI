//
// Created by Vincent on 02/05/2019.
//

#include "processus.h"
#include <iostream>
using namespace std;

Automate a_choix_automate() {
    string choix;
    const int nb_files = 43;

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

    cout << endl << "||------ Ouverture de l'automate " << string(choix.length()%2, '0') << choix << endl;
    choix = "Automates_test/L2-E4-" + string(choix.length()%2, '0') + choix + ".txt";

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

void d_lecture_de_mot(Automate af) {
    cout << "*****************************************************" << endl;
    cout << "*****           Reconnaissance de mot           *****" << endl;
    cout << "*****************************************************" << endl;
    cout << "||---- Pour saisir le mot vide taper 1" << endl;
    cout << "||---- Pour arreter la saisie taper 0" << endl;

    string mot;
    lire_mot(mot);
    bool reconnu;
    if (mot != "0"){
        while(mot != "0"){
            reconnu = reconnaitre_mot(mot, af);
            if((reconnu) and (mot == "1")) {
                cout << "||---- Le mot vide est reconnu par l'automate" << endl;
            }
            else if ((reconnu) and (mot != "1")){
                cout << "||---- Le mot " << mot << " est reconnu par l'automate" << endl;
            }
            else if ((!reconnu) and (mot == "1")){
                cout << "||---- Le mot vide n'est pas reconnu par l'automate" << endl;
            }
            else{
                cout << "||---- Le mot " << mot << " n'est pas reconnu par l'automate" << endl;
            }
            cout << endl;
            lire_mot(mot);
        }
        cout << "||---- Fin de la reconnaissance de mot" << endl;
    }
    else{
        cout << "||---- Fin de la reconnaissance de mot" << endl;
    }
    cout << endl;
}

Automate e_langage_complementaire(Automate afdcm) {
    cout << "*****************************************************" << endl;
    cout << "*****          Langage complementaire           *****" << endl;
    cout << "*****************************************************" << endl;
    Automate afdcm_complementaire(0);
    afdcm_complementaire = afdcm.langage_complementaire();
    afdcm_complementaire.print_table_transition();
    d_lecture_de_mot(afdcm_complementaire);
    return afdcm_complementaire;
}

Automate f_standardisation(Automate afdcm_complementaire) {
    cout << "*****************************************************" << endl;
    cout << "*****              Standardisation              *****" << endl;
    cout << "*****************************************************" << endl;
    Automate afdcms(0);
    afdcms = afdcm_complementaire.standardisation();
    afdcms.print_table_transition();
    d_lecture_de_mot(afdcms);
    return afdcms;
}

