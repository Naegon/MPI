//
// Created by Vincent on 24/04/2019.
//

#include "Automate.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include "fonction.h"

using namespace std;

Automate::Automate(int _nb_symb, int _nb_etats,
        int _nb_init, std::vector<int> _init,
        int _nb_term, std::vector<int> _term,
        int _nb_trans, std::vector<Transition> _transitions){
        alphabet = get_alpha();
        nb_symb = _nb_symb;
        nb_etats = _nb_etats;
        nb_init = _nb_init;
        init = _init;
        nb_term = _nb_term;
        term = _term;
        nb_trans = _nb_trans;
        transitions = _transitions;
}

Automate::Automate(Automate& A){
    nb_symb = A.nb_symb;
    nb_etats = A.nb_etats;
    nb_init = A.nb_init;
    init = A.init;
    nb_term = A.nb_term;
    term = A.term;
    nb_trans = A.nb_trans;
    transitions = A.transitions;
    alphabet = get_alpha();
}


Automate::Automate(string path) {
    ifstream fichier(path);
    if (fichier) {

        string temp;

        getline(fichier, temp);
        nb_symb = stoi(temp);

        getline(fichier, temp);
        nb_etats = stoi(temp);

        fichier >> temp;
        nb_init = stoi(temp);

        for (int i = 0; i< nb_init; i++) {
            fichier >> temp;
            init.push_back(stoi(temp));
        }

        fichier >> temp;
        nb_term = stoi(temp);

        for (int i = 0; i < nb_term; i++) {
            fichier >> temp;
            term.push_back(stoi(temp));
        }

        fichier >> temp;
        nb_trans = stoi(temp);

        for (int i = 0; i < nb_trans; i++) {
            string p, q;
            char symb;

            fichier >> p;
            fichier >> symb;
            fichier >> q;
            Transition trans_temp(stoi(p), symb, stoi(q));

            transitions.push_back(trans_temp);
        }
        alphabet = get_alpha();
        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        cerr << "ERROR" << strerror(errno);
    }
}

bool Automate::est_automate_asynchrone() {
    bool ok = true;
    cout << "Automate asynchrone ? " << endl;
    for(int i = 0 ; i < transitions.size() ; i++){
        if (transitions[i].getSymb() == '*'){
            ok = false;
            cout << "||--- La transition ";
            transitions[i].print();
            cout << " contient une transition epsilon" << endl;
        }
    }
    if (ok){
        cout << "||--- L'automate est asynchrone" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas asynchrone" << endl;
    }
    return ok;
}

bool Automate::est_automate_standart() {
    bool ok = true;
    cout << "Automate standart ? " << endl;
    if (nb_init > 1){
        cout << "||--- L'automate n'est pas standart car plusieurs etats initiaux" << endl;
        return false;
    }

    for(int i = 0 ; i < transitions.size() ; i++){
        if (transitions[i].getQ() == init[0]){
            ok = false;
            cout << "||--- La transition ";
            transitions[i].print();
            cout << " entre sur l'etat initial" << endl;
        }
    }
    if (ok){
        cout << "||--- L'automate est standart" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas standart" << endl;
    }
    return ok;
}

bool Automate::est_automate_deterministe() {
    bool ok = true;
    cout << "Automate deterministe ? " << endl;
    if (nb_init > 1){
        cout << "||--- L'automate n'est pas deterministe car il a plusieurs d'un etats initiaux" << endl;
        return false;
    }

    for (int i = 0 ; i < transitions.size() ; i++){
        for (int j = (i+1) ; j < transitions.size() ; j++){
            if(i != j){
                if (((transitions[i].getP() == transitions[j].getP()) and (transitions[i].getQ() != transitions[j].getQ())) and (transitions[i].getSymb() == transitions[j].getSymb())){
                    ok = false;
                    cout << "||--- La transition ";
                    transitions[i].print();
                    cout << " et la transition ";
                    transitions[j].print();
                    cout << " ont le meme symbole et etat de depart mais un etat d'arrive different" << endl;
                }
            }
        }
    }

    if (ok){
        cout << "||--- L'automate est deterministe" << endl;
    }
    else{
        cout << "||--- L'automate n'est pas deterministe" << endl;
    }
    return ok;
}


bool Automate::est_automate_complet() {
    bool ok;

    // Le nombre de transitions est égal au produit du nombre de caractères de l'alphabet et du nombre d'états

    if (nb_trans < (nb_symb*nb_etats)){
        ok = false;
    }

    return ok;
}



Automate Automate::completion() {
    Automate temp(*this);

    //ajout de l'etat poubelle
    temp.nb_etats ++;

    //ajout des transitions
    vector<char> alpha_temp;
    for (int i = 0 ; i < temp.nb_etats ; i ++ ){ //pour chaque état de l'automate
        alpha_temp = get_alpha(); // creation du tableau temporaire contenant les symboles de l'alphabet
        for (int j = 0 ; j < temp.nb_trans ; j++){ // pour chaque transition existante
            if(i == temp.transitions[j].getP()){ // si l'etat i à une transition sortante
                alpha_temp.erase(remove(alpha_temp.begin(), alpha_temp.end(), temp.transitions[j].getSymb()), alpha_temp.end()); // le caractere est supprimé du tableau temporaire
            }
        }
        if (!alpha_temp.empty()){ // si pour l'etat i, il existe des symboles sans transition (les symboles restants dans le tableau)
            for (int j = 0 ; j < alpha_temp.size() ; j++){ //on ajoute une transition de i vers le dernier état = etat poubelle
                temp.nb_trans ++;
                temp.transitions.emplace_back(i, alpha_temp[j], nb_etats);
            }
        }
        alpha_temp.clear(); //le tableau est remis à vide pour le prochain état
    }
    return temp;
}

Automate Automate::standardisation() {
    Automate temp(*this);
    temp.nb_etats++;

    if(!temp.est_automate_standart()){
        for (int i = 0 ; i < init.size() ; i++){
            for (int j = 0 ; j < transitions.size() ; j++){
                if (init[i] == transitions[j].getP()){
                    temp.transitions.emplace_back(nb_etats, transitions[j].getSymb(), transitions[j].getQ());
                }
            }
        }
        temp.init.clear();
        temp.init.emplace_back(nb_etats);
    }
    return temp;
}

/*
Automate Automate::determinisation() {
    //automate renvoyé
    Automate af_deter(*this);
    af_deter.nb_etats = 0;
    af_deter.nb_init = 0;
    af_deter.init.clear();
    af_deter.nb_term = 0;
    af_deter.term.clear();
    af_deter.nb_trans = 0;
    af_deter.transitions.clear();

    vector<string> etat_a_traiter;
    vector<string> etat_traite;
    vector<string> transition;
    string initiaux;
    vector<string> terminaux;
    string tempo;

    //Determination des etats initiaux
    for (int i = 0 ; i < init.size() ; i++){
        initiaux += to_string(init[i]);
    }
    etat_a_traiter.push_back(initiaux);

    //Fusion des etats initiaux
    for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
        for(int i = 0 ; i < init.size() ; i++){ //pour chaque etat initiaux
            for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                if ((transitions[k].getP() == init[i]) and (transitions[k].getSymb() == alphabet[j])){
                    //si le p de la transition est egal à l'etat initial et le symbole de la T egale au symbole de l'alphabet traités
                    //cout << transitions[k].getP() << transitions[k].getSymb() << transitions[k].getQ() << " " << j << i << k <<  endl;
                    tempo += to_string(transitions[k].getQ());
                }
            }
        }
        ordonner_string(tempo);
        supprimer_doublon_string(tempo);
        if (!tempo.empty()){
           if (!string_in_vector(tempo, etat_traite)){
               etat_a_traiter.push_back(tempo);
           }
        }
        transition.push_back(tempo);
        tempo.clear();
    }
    etat_traite.push_back(initiaux);
    etat_a_traiter.erase(etat_a_traiter.begin());

    //Boucle de determinisation
    do{
        for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
            for(int i = 0 ; i < etat_a_traiter[0].size() ; i++){ //pour chaque etat initiaux
                for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                    int ic = (int) etat_a_traiter[0][i]; //pour la comparaison du caractere avec l'entier designant l'etat p de la transition
                    if (transitions[k].getP() == (ic-48)){ //-48 car le cast donne la table ascii
                        if(transitions[k].getSymb() == alphabet[j]){
                            tempo += to_string(transitions[k].getQ());
                        }
                    }
                }
            }
            ordonner_string(tempo);
            supprimer_doublon_string(tempo);
            if (!tempo.empty()){
                if ((!string_in_vector(tempo, etat_traite)) and (!string_in_vector(tempo, etat_a_traiter))){
                    etat_a_traiter.push_back(tempo);
                }
            }
            transition.push_back(tempo);
            tempo.clear();
        }

        etat_traite.push_back(etat_a_traiter[0]);
        etat_a_traiter.erase(etat_a_traiter.begin());
    }while (!etat_a_traiter.empty());

    //Determination des etats terminaux
    for (int i = 0 ; i < etat_traite.size() ; i++){
        bool in = false;
        int taille_etat_terminal = etat_traite[i].size();
        for (int j = 0 ; j < taille_etat_terminal ; j++){
            for (int k = 0 ; k < term.size() ; k++){
                int ic = (int) etat_traite[i][j];
                if (term[k] == (ic-48)){
                    in = true;
                }
            }
        }
        if (in){
            terminaux.push_back(etat_traite[i]);
        }
    }



    //Reecriture des etats par des numeros entiers de 0 à n
    changement_numero_etat(etat_traite, transition);
    changement_numero_etat(etat_traite, terminaux);

    //Creation de l'automate deterministe
        //nb_etat = nb_etat traite
    af_deter.nb_etats = etat_traite.size();
        //un seul etat initial
    af_deter.nb_init = 1;
        //nb_term = taille du vector d'etat terminal
    af_deter.nb_term = terminaux.size();
        //Calcul du nombre de transition et creation des transitions
    int count = -1;
    for (int i = 0 ; i < transition.size() ; i++){
        if (i%nb_symb == 0){
            count++;
        }
        if (!transition[i].empty()){
            nb_trans++;
            char symb = alphabet[i%nb_symb];
            int p = count;
            int q = ((int) transition[i][0])-48;
            Transition transi(p, symb, q);
            af_deter.transitions.push_back(transi);
        }
    }
        //ajout de l'etat initial
    af_deter.init.push_back(0);
        //ajout des etats terminaux
    for (int i = 0 ; i < terminaux.size() ; i++){
        int a = stoi(terminaux[i][0]);
        af_deter.term.push_back(a-48);
    }
    return af_deter;
}
*/
Automate Automate::determinisation() {
    //automate renvoyé
    Automate af_deter(*this);
    af_deter.nb_etats = 0;
    af_deter.nb_init = 0;
    af_deter.init.clear();
    af_deter.nb_term = 0;
    af_deter.term.clear();
    af_deter.nb_trans = 0;
    af_deter.transitions.clear();

    vector<string> etat_a_traiter;
    vector<string> etat_traite;
    vector<string> transition;
    string initiaux;
    vector<string> terminaux;
    vector<string> tempo;
    string compose;

    //Determination des etats initiaux
    for (int i = 0 ; i < init.size() ; i++){
        if (initiaux.empty()){
            initiaux += to_string(init[i]);
        }
        else{
            initiaux += ".";
            initiaux += to_string(init[i]);
        }
    }
    etat_a_traiter.push_back(initiaux);

    //Fusion des etats initiaux
    tempo.clear();
    for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
        for(int i = 0 ; i < init.size() ; i++){ //pour chaque etat initiaux
            for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                if ((transitions[k].getP() == init[i]) and (transitions[k].getSymb() == alphabet[j])){
                    //si le p de la transition est egal à l'etat initial et le symbole de la T egale au symbole de l'alphabet traités
                    tempo.push_back(to_string(transitions[k].getQ()));
                }
            }
        }
        ordonner_vector_string(tempo);
        supprimer_doublon_vector_string(tempo);
        for (int m = 0; m < tempo.size() ; m++){
            compose += tempo[m];
            if ((m+1) != tempo.size()){
                compose += ".";
            }
        }
        if (!compose.empty()){
            if ((!string_in_vector(compose, etat_traite)) and (!string_in_vector(compose, etat_a_traiter))){
                etat_a_traiter.push_back(compose);
            }
        }
        transition.push_back(compose);
        tempo.clear();
        compose.clear();
    }
    etat_traite.push_back(initiaux);
    etat_a_traiter.erase(etat_a_traiter.begin());


    //Boucle de determinisation
    do{
        for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
            for(int i = 0 ; i < etat_a_traiter[0].size() ; i++){
                for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                    int ic = (int) etat_a_traiter[0][i]; //pour la comparaison du caractere avec l'entier designant l'etat p de la transition
                    if (transitions[k].getP() == (ic-48)){ //-48 car le cast donne la table ascii
                        if(transitions[k].getSymb() == alphabet[j]){
                            tempo.push_back(to_string(transitions[k].getQ()));
                        }
                    }
                }
            }
            ordonner_vector_string(tempo);
            supprimer_doublon_vector_string(tempo);
            for (int m = 0; m < tempo.size() ; m++){
                compose += tempo[m];
                if ((m+1) != tempo.size()){
                    compose += ".";
                }
            }
            if (!compose.empty()){
                if ((!string_in_vector(compose, etat_traite)) and (!string_in_vector(compose, etat_a_traiter))){
                    etat_a_traiter.push_back(compose);
                }
            }
            transition.push_back(compose);
            tempo.clear();
            compose.clear();
        }
        etat_traite.push_back(etat_a_traiter[0]);
        etat_a_traiter.erase(etat_a_traiter.begin());
    }while (!etat_a_traiter.empty());

    //Determination des etats terminaux
    for (int i = 0 ; i < etat_traite.size() ; i++){
        bool in = false;
        int taille_etat_terminal = etat_traite[i].size();
        for (int j = 0 ; j < taille_etat_terminal ; j++){
            for (int k = 0 ; k < term.size() ; k++){
                int ic = (int) etat_traite[i][j];
                if (term[k] == (ic-48)){
                    in = true;
                }
            }
        }
        if (in){
            terminaux.push_back(etat_traite[i]);
        }
    }
    ordonner_vector_string(terminaux);



    //Reecriture des etats par des numeros entiers de 0 à n
    changement_numero_etat(etat_traite, transition);
    changement_numero_etat(etat_traite, terminaux);

    //Creation de l'automate deterministe
    //nb_etat = nb_etat traite
    af_deter.nb_etats = etat_traite.size();
    //un seul etat initial
    af_deter.nb_init = 1;
    //nb_term = taille du vector d'etat terminal
    af_deter.nb_term = terminaux.size();
    //Calcul du nombre de transition et creation des transitions
    int count = -1;
    for (int i = 0 ; i < transition.size() ; i++){
        if (i%nb_symb == 0){
            count++;
        }
        if (!transition[i].empty()){
            af_deter.nb_trans++;
            char symb = alphabet[i%nb_symb];
            int p = count;
            int q = ((int) transition[i][0])-48;
            Transition transi(p, symb, q);
            af_deter.transitions.push_back(transi);
        }
    }
    //ajout de l'etat initial
    af_deter.init.push_back(0);
    //ajout des etats terminaux
    for (int i = 0 ; i < terminaux.size() ; i++){
        af_deter.term.push_back(stoi(terminaux[i]));
    }
    return af_deter;
}

Automate Automate::determinisation_asynchrone(){
    //automate renvoyé
    Automate af_deter(*this);
    af_deter.nb_etats = 0;
    af_deter.nb_init = 0;
    af_deter.init.clear();
    af_deter.nb_term = 0;
    af_deter.term.clear();
    af_deter.nb_trans = 0;
    af_deter.transitions.clear();

    vector<string> etat_a_traiter;
    vector<string> etat_traite;
    vector<string> transition;
    string initiaux;
    vector<string> terminaux;
    vector<string> tempo;
    string compose;
    vector<string> transition_epsilon_etat_original = determiner_transition_epsilon();

    //Determination des etats initiaux
    for (int i = 0 ; i < init.size() ; i++){
        if (initiaux.empty()){
            initiaux += to_string(init[i]);
        }
        else{
            initiaux += ".";
            initiaux += to_string(init[i]);
        }
    }
    initiaux = determiner_transition_epsilon(initiaux);
    etat_a_traiter.push_back(initiaux);

    //Fusion des etats initiaux
    tempo.clear();
    for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
        for(int i = 0 ; i < initiaux.size() ; i++){ //pour chaque etat initiaux
            for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                int ic = (int) etat_a_traiter[0][i]; //pour la comparaison du caractere avec l'entier designant l'etat p de la transition
                if (transitions[k].getP() == (ic-48)){ //-48 car le cast donne la table ascii
                    if(transitions[k].getSymb() == alphabet[j]){
                        tempo.push_back(to_string(transitions[k].getQ()));
                    }
                }
            }
        }
        ordonner_vector_string(tempo);
        supprimer_doublon_vector_string(tempo);
        for (int m = 0; m < tempo.size() ; m++){
            compose += tempo[m];
            if ((m+1) != tempo.size()){
                compose += ".";
            }
        }
        if (!compose.empty()){
            compose = determiner_transition_epsilon(compose);
            if ((!string_in_vector(compose, etat_traite)) and (!string_in_vector(compose, etat_a_traiter))){
                etat_a_traiter.push_back(compose);
            }
        }
        transition.push_back(compose);
        tempo.clear();
        compose.clear();
    }
    etat_traite.push_back(initiaux);
    etat_a_traiter.erase(etat_a_traiter.begin());


    //Boucle de determinisation
    do{
        for (int j = 0 ; j < alphabet.size() ; j++){ //pour chaque transition
            for(int i = 0 ; i < etat_a_traiter[0].size() ; i++){ //pour chaque etat initiaux
                for (int k = 0 ; k < transitions.size() ; k++){ // pour chaque symbole de l'alphabet
                    int ic = (int) etat_a_traiter[0][i]; //pour la comparaison du caractere avec l'entier designant l'etat p de la transition
                    if (transitions[k].getP() == (ic-48)){ //-48 car le cast donne la table ascii
                        if(transitions[k].getSymb() == alphabet[j]){
                            tempo.push_back(to_string(transitions[k].getQ()));
                        }
                    }
                }
            }
            ordonner_vector_string(tempo);
            supprimer_doublon_vector_string(tempo);
            for (int m = 0; m < tempo.size() ; m++){
                compose += tempo[m];
                if ((m+1) != tempo.size()){
                    compose += ".";
                }
            }
            if (!compose.empty()){
                compose = determiner_transition_epsilon(compose);
                if ((!string_in_vector(compose, etat_traite)) and (!string_in_vector(compose, etat_a_traiter))){
                    etat_a_traiter.push_back(compose);
                }
            }
            transition.push_back(compose);
            tempo.clear();
            compose.clear();
        }
        etat_traite.push_back(etat_a_traiter[0]);
        etat_a_traiter.erase(etat_a_traiter.begin());
    }while (!etat_a_traiter.empty());

    //Determination des etats terminaux
    for (int i = 0 ; i < etat_traite.size() ; i++){
        bool in = false;
        int taille_etat_terminal = etat_traite[i].size();
        for (int j = 0 ; j < taille_etat_terminal ; j++){
            for (int k = 0 ; k < term.size() ; k++){
                int ic = (int) etat_traite[i][j];
                if (term[k] == (ic-48)){
                    in = true;
                }
            }
        }
        if (in){
            terminaux.push_back(etat_traite[i]);
        }
    }
    ordonner_vector_string(terminaux);



    //Reecriture des etats par des numeros entiers de 0 à n
    changement_numero_etat(etat_traite, transition);
    changement_numero_etat(etat_traite, terminaux);

    //Creation de l'automate deterministe
    //nb_etat = nb_etat traite
    af_deter.nb_etats = etat_traite.size();
    //un seul etat initial
    af_deter.nb_init = 1;
    //nb_term = taille du vector d'etat terminal
    af_deter.nb_term = terminaux.size();
    //Calcul du nombre de transition et creation des transitions
    int count = -1;
    for (int i = 0 ; i < transition.size() ; i++){
        if (i%nb_symb == 0){
            count++;
        }
        if (!transition[i].empty()){
            af_deter.nb_trans++;
            char symb = alphabet[i%nb_symb];
            int p = count;
            int q = ((int) transition[i][0])-48;
            Transition transi(p, symb, q);
            af_deter.transitions.push_back(transi);
        }
    }
    //ajout de l'etat initial
    af_deter.init.push_back(0);
    //ajout des etats terminaux
    for (int i = 0 ; i < terminaux.size() ; i++){
        af_deter.term.push_back(stoi(terminaux[i]));
    }
    return af_deter;
}

Automate Automate::determinisation_et_completion_asynchrone() {
    Automate afdc(*this);
    afdc = afdc.determinisation_asynchrone();
    ///check si completion identique pour async
    //afdc = afdc.completion();
    return afdc;
}

Automate Automate::determinisation_et_completion() {
    Automate afdc(*this);
    afdc = afdc.determinisation();
    afdc = afdc.completion();
    return afdc;
}



void Automate::setNbEtats(int nbEtats) {
    nb_etats = nbEtats;
}

vector<char> Automate::get_alpha() const {
    vector<char> alphabet;

    for(int unsigned i = 0; i < nb_trans; i++){
        char key = transitions[i].getSymb();

        if (find(alphabet.begin(), alphabet.end(), key) == alphabet.end()) {
            if (key != '*'){
                alphabet.push_back(key);
            }
        }
    }
    return alphabet;
}


const vector<Transition> &Automate::getTransitions() const {
    return transitions;
}


//Version où on renvoie le tableau d'etat terminaux
/*
vector<int> Automate::langage_complementaire() {
    //Pour chaque état du nouvel automate (de 1 à n)
    //Si l'etat n'est pas dans la liste des etats terminaux de l'automate à completer
    //Alors on l'ajoute à la liste des etats terminaux de l'automate complet
    vector<int> etat_term_complementaire;
    for (int i = 0 ; i < nb_etats ; i++){
        for (int j = 0 ; j < nb_term ; j ++){
            if (i != term[j]){
                etat_term_complementaire.push_back(i);
            }
        }
    }
    return etat_term_complementaire;
}*/

//Version où on renvoie l'automate reconnaissant le langage complementaire
Automate Automate::langage_complementaire() {
    Automate temp(*this);
    //Pour chaque état du nouvel automate (de 1 à n)
    //Si l'etat n'est pas dans la liste des etats terminaux de l'automate à completer
    //Alors on l'ajoute à la liste des etats terminaux de l'automate complet
    vector<int> etat_term_complementaire;
    for (int i = 0 ; i < nb_etats ; i++){
        for (int j = 0 ; j < nb_term ; j ++){
            if (i != term[j]){
                etat_term_complementaire.push_back(i);
            }
        }
    }
    temp.term.clear();
    temp.setTerm(etat_term_complementaire);
    return temp;
}




void Automate::setTerm(std::vector<int> _term) {
    term.clear();
    term = _term;
}

int Automate::getNb_init() const {
    return nb_init;
}

int Automate::getNb_term() const {
    return nb_term;
}

vector<int> Automate::getInit() const {
    return init;
}

vector<int> Automate::getTerm() const {
    return term;
}

int Automate::getNb_trans() const {
    return nb_trans;
}

void Automate::print() const {
    cout << "Automate :" << endl;
    cout << "||--- Etats initiaux : ";
    for (int i = 0; i<init.size(); i++) {
        cout << init[i] << " ";
    }
    cout << endl;

    cout << "||--- Etats terminaux : ";
    for (int i = 0; i<term.size(); i++) {
        cout << term[i] << " ";
    }
    cout << endl;

    cout << "||--- " << nb_trans << " transitions : " << endl;
    for (int i = 0; i<transitions.size(); i++) {
        cout << "||------ ";
        transitions[i].print();
        cout << endl;
    }
    cout << endl;
}

void Automate::print_table_transition() {
    cout << "*****************************************************" << endl;
    cout << "*****     Table de transitions de l'automate    *****" << endl;
    cout << "*****************************************************" << endl;
    cout << "   |";
    for (int i = 0 ; i < alphabet.size() ; i++){
        cout << "  " << alphabet[i];
    }
    cout << endl;
    for (int i = 0 ; i < nb_etats ; i++){
        //affichage des etats
        if (i >= 10){
            cout << " " << i << "|";
        }
        else{
            cout << "  " << i << "|";
        }

        //affichage des transitions
        for (int j = 0 ; j < alphabet.size() ; j++){
            for (int k = 0 ; k < nb_trans ; k++){
                if ((transitions[k].getP() == i) and (transitions[k].getSymb() == alphabet[j])){
                    cout << "  " << transitions[k].getQ();
                }
            }
        }
        cout << endl;
    }
}

Automate &Automate::operator=(const Automate & Af) {
    nb_symb = Af.nb_symb;
    nb_etats = Af.nb_etats;
    nb_init = Af.nb_init;
    init = Af.init;
    nb_term = Af.nb_term;
    term = Af.term;
    nb_trans = Af.nb_trans;
    transitions = Af.transitions;
    return *this;
}

vector<string> Automate::determiner_transition_epsilon() {
    vector<string> transition_epsilon;
    for (int i = 0 ; i < nb_etats ; i++){
        transition_epsilon.push_back(get_transition_epsilon(i, *this));
    }
    return transition_epsilon;
}

vector<string> Automate::determiner_transition_epsilon(vector<string> etat) {
    vector<string> transition_epsilon;
    for (int i = 0 ; i < etat.size() ; i++){
        transition_epsilon.push_back(get_transition_epsilon(etat[i], *this));
    }
    return transition_epsilon;
}

string Automate::determiner_transition_epsilon(string etat) {
    string transition_epsilon;
    etat = get_transition_epsilon(etat, *this);
    return etat;
}
