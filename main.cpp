#include <iostream>
#include <string>
#include "Transition.h"
#include "Automate.h"
#include <vector>
#include "fonction.h"
using namespace std;
void loop();
bool continuer();

string menu() {
    string choix;
    const int nb_files = 13;

    cout << endl;
    cout << "||---- Choix de l'automate" << endl;
    cout << "||---- " << nb_files << " automates disponibles " << endl << endl;
    cout << "||-----> Votre choix : ";
    cin >> choix;

    while (stoi(choix) < 1 || stoi(choix) > nb_files) {
        cout << "||---- Choisissez un nombre entre 1 et " << nb_files << endl;
        cout << "||-----> Votre choix :";
        cin >> choix;
    }

    cout << endl << "||------ Ouverture de l'automate " << choix <<  endl << endl;

    choix = "Automates_test/L2-E4-" + choix + ".txt";

    return choix;
}

bool continuer() {
    string rep;
    cin >> rep;
    if (rep == "y") {
        loop();
        return true;
    }
    else if (rep == "n") {
        return false;
    }
    else {
        return continuer();
    }
}


void loop() {
    Automate loop(menu());
    loop.print();

    cout << "||---- Voulez-vous continuer ?" << endl;
    cout << "||---- > y/n" << endl;

    if (continuer()) {
        loop;
    }
}

void lire_mot(string& mot){

    cout << "||---- Reconnaissance de mot" << endl;
    cout << "||---- Pour saisir le mot vide taper 1" << endl;
    cout << "||---- Pour arreter la saisie taper 0" << endl;
    cout << "||---- Saisissez un mot comprenant des lettres de l'alphabet : ";
    cin >> mot;
}

bool reconnaitre_mot(string mot, Automate af){
    cout << "||---- Reconnaissance du mot " << mot << endl;
    bool reconnu = false;
    vector<int> term = af.getTerm();
    vector<int> init = af.getInit();
    vector<Transition> trans = af.getTransitions();
    int etat_courant = init[0];
    char symbole_courant = mot[0];
    int compteur_symbole = 0;
    int sortie = 0;

    ///Reconnaissance du mot vide
    if (mot == "1"){
        for (int i = 0 ; i < af.getNb_term() ; i++){
            if (init[0] == term[i]){
                return true;
            }
        }
        return false;
    }
    ///Reconnaissance du mot
    else{
        //boucle pour le mot en entier
        do {
            bool suivant = false;
            int compteur_transition = 0;
            //boucle pour le symbole et etat courant
            do {
                //si il existe une transition donc le p est l'etat courant et le symbole est le symbole courant
                if ((etat_courant == trans[compteur_transition].getP()) and (symbole_courant == trans[compteur_transition].getSymb())) {
                    compteur_symbole++;
                    sortie++; //structure de controle
                    etat_courant = trans[compteur_transition].getQ(); //on passe à l'etat suivant (cad le q de la transition)
                    symbole_courant = mot[compteur_symbole]; //on passe au symbole suivant
                    suivant = true; //sortie de boucle
                }
                else{
                    compteur_transition++; //on test la transition suivante
                    if (compteur_transition == af.getNb_trans()){ //si il n'y a plus de transition à tester
                        suivant = true; //sortie de boucle
                        sortie++;
                    }
                }
            }while (!suivant);
        }while(sortie != mot.size()); //sortie si sortie = taille du mot
        //le mot est reconnu si l'etat courant est un etat terminal et si on est passé sur tout les symboles
        for (int i = 0 ; i < term.size() ; i++){
            if ((etat_courant == term[i]) and (mot.size() == compteur_symbole)){
                return true;
            }
        }
    }
    return reconnu;
}

void reconnaissance_de_mot(){
    string mot;
    lire_mot(mot);
    bool reconnu;
    if (mot != "0"){
        while(mot != "0"){
            string choix_automate = menu();
            Automate af(choix_automate);
            ///TODO determiniser et completer l'automate pour l'utiliser
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
}

int main() {
 /*
    vector<Transition> transitions;
    transitions.emplace_back(Transition(2, 'a', 3));
    transitions.emplace_back(Transition(2, 'b', 0));
    transitions.emplace_back(Transition(3, 'a', 7));

    vector<int> init;
    init.push_back(2);
    vector<int> term;
    term.push_back(3);
    term.push_back(5);

    Automate test(3, 8, 1, init, 2, term, 3, transitions);
    test.print();
    bool est_AF_async = test.est_automate_asynchrone();
    bool est_AF_standart = test.est_automate_standart();
    bool est_AF_deterministe = test.est_automate_deterministe();

    test.completion();
    //Automate read("/Automates_test/L2-E4-1.txt");
*/
    vector<string> h;
    h.push_back(to_string(12));
    int i = stoi(h[0]);
    cout << i ;

   Automate test("Automates_test/L2-E4-13.txt");
   test.print();
   Automate a(test);
   a = test.determinisation();

   //test.print();

    return 0;
}
