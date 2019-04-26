#include <iostream>
#include "Transition.h"
#include "Automate.h"
#include <vector>

using namespace std;
void loop();
bool continuer();

string menu() {
    string choix;
    const int nb_files = 3;

    cout << endl;
    cout << "||---- Choix de l'automate" << endl;
    cout << "||---- " << nb_files << " automates disponibles " << endl << endl;
    cout << "||-----> Votre choix : ";
    cin >> choix;

    while (stoi(choix) < 1 || stoi(choix) > nb_files) {
        cout << "||---- Choisir un nombre entre 1 et " << nb_files << endl;
        cout << "||-----> Votre choix :";
        cin >> choix;
    }

    cout << endl << "||------ Ouverture automate " << choix <<  endl << endl;

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


    Automate det("Automates_test/L2-E4-2.txt");
    Automate co(det);
    co.print();
    co = det.langage_complementaire();
    co.print();

    //loop();
    return 0;
}
