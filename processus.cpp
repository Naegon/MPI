#include "processus.h"
#include <iostream>
using namespace std;



/**
 * Choix de l'automate à traiter
 * @return l'automate à traiter
 */
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

    //Boucle de saisie du numero de l'automate
    while (stoi(choix) < 1 || stoi(choix) > nb_files) {
        cout << "||---- Choisissez un nombre entre 1 et " << nb_files << endl;
        cout << "||-----> Votre choix :";
        cin >> choix;
    }

    cout << endl << "||------ Ouverture de l'automate " << string(choix.length()%2, '0') << choix << endl;
    choix = "Automates_test/L2-E4-" + string(choix.length()%2, '0') + choix + ".txt";

    Automate af(choix);
    return af;
}

/**
 * Processus de determinisation et completion en fonction du type d'automate en entrée(asynchrone, af, afd, afdc)
 * @param af, l'automate à determiniser et completer
 * @return afdcm, l'automate deterministe complet
 */
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

/**
 * Minimisation de l'automate
 * @param afdc, l'automate à minimiser
 * @return afdcm, l'automate minimal
 */
Automate c_minimisation(Automate afdc) {
    cout << "*****************************************************" << endl;
    cout << "*****                Minimisation               *****" << endl;
    cout << "*****************************************************" << endl;
    Automate afdcm(0);
    afdcm = afdc.minimisation();
    afdcm.afficher_automate_deterministe_complet();
    return afdcm;
}

/**
 * Lecture de mot
 * @param af, l'automate à utiliser pour la reconnaissance de mot
 */
void d_lecture_de_mot(Automate af) {
    cout << "*****************************************************" << endl;
    cout << "*****           Reconnaissance de mot           *****" << endl;
    cout << "*****************************************************" << endl;
    cout << "||---- Pour saisir le mot vide taper 1" << endl;
    cout << "||---- Pour arreter la saisie taper 0" << endl;

    string mot;
    lire_mot(mot); // saisie du mot à lire
    bool reconnu;
    if (mot != "0"){
        while(mot != "0"){ //reconnaissance tant que la saisie n'est pas 0 = sortie
            reconnu = reconnaitre_mot(mot, af); //test de reconnaissance du mot par l'automate
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
            lire_mot(mot); //nouvelle saisie utilisateur
        }
        cout << "||---- Fin de la reconnaissance de mot" << endl;
    }
    else{
        cout << "||---- Fin de la reconnaissance de mot" << endl;
    }
    cout << endl;
}

/**
 * Creation de l'automate reconnaissant le langage complemenataire de l'automate en entree
 * Lecture de mot avec ce langage
 * @param afdcm
 * @return afdcm_complementaire, le langage reconnaissant le langage complementaire
 */
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

/**
 * Standardisation de l'automate reconnaissant le langage complementaire
 * @param afdcm_complementaire
 * @return afdcms, l'automate standard
 */
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

