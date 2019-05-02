//
// Created by Vincent on 24/04/2019.
//

#include "Automate.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include "fonction.h"

using namespace std;

Automate::Automate(int etat){
    alphabet.clear();
    nb_symb = 0;
    nb_etats = 0;
    nb_init = 0;
    init.clear();
    nb_term = 0;
    term.clear();
    nb_trans = 0;
    transitions.clear();
    etat_compose.clear();
}

Automate::Automate(int _nb_symb, int _nb_etats,
        int _nb_init, std::vector<int> _init,
        int _nb_term, std::vector<int> _term,
        int _nb_trans, std::vector<Transition> _transitions, std::vector<std::string> _etat_compose){
        alphabet = get_alpha();
        nb_symb = _nb_symb;
        nb_etats = _nb_etats;
        nb_init = _nb_init;
        init = _init;
        nb_term = _nb_term;
        term = _term;
        nb_trans = _nb_trans;
        transitions = _transitions;
        etat_compose = _etat_compose;
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
    etat_compose = A.etat_compose;
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
        etat_compose.clear();
        fichier.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        cerr << "ERROR" << strerror(errno);
    }
}

bool Automate::est_automate_asynchrone() {
    bool ok = false;
    cout << "Automate asynchrone ? " << endl;
    for(int i = 0 ; i < transitions.size() ; i++){
        if (transitions[i].getSymb() == '*'){
            ok = true;
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
    cout << endl;
    return ok;
}

bool Automate::est_automate_standard() {
    bool ok = true;
    cout << "Automate standart ? " << endl;
    if (nb_init > 1){
        cout << "||--- L'automate n'est pas standard car plusieurs etats initiaux" << endl;
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
        cout << "||--- L'automate n'est pas deterministe car il a plusieurs etats initiaux" << endl;
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
    cout << endl;
    return ok;
}

bool Automate::est_automate_complet() {
    bool ok;

    // Le nombre de transitions est égal au produit du nombre de caractères de l'alphabet et du nombre d'états
    cout << "Automate est complet ?" << endl;
    if (nb_trans < (nb_symb*nb_etats)){
        ok = false;
        cout << "|--- L'automate n'est pas complet car toutes les transitions ne sont pas presentes" << endl;
    }
    else{
        cout << "||--- L'automate est complet"<< endl;
    }
    cout << endl;

    return ok;
}

Automate Automate::completion() {
    Automate complet(*this);

    //ajout de l'etat poubelle
    complet.nb_etats ++;

    //ajout des transitions
    vector<char> alpha_temp;
    for (int i = 0 ; i < complet.nb_etats ; i ++ ){ //pour chaque état de l'automate
        alpha_temp = get_alpha(); // creation du tableau temporaire contenant les symboles de l'alphabet
        for (int j = 0 ; j < complet.nb_trans ; j++){ // pour chaque transition existante
            if(i == complet.transitions[j].getP()){ // si l'etat i à une transition sortante
                alpha_temp.erase(remove(alpha_temp.begin(), alpha_temp.end(), complet.transitions[j].getSymb()), alpha_temp.end()); // le caractere est supprimé du tableau temporaire
            }
        }
        if (!alpha_temp.empty()){ // si pour l'etat i, il existe des symboles sans transition (les symboles restants dans le tableau)
            for (int j = 0 ; j < alpha_temp.size() ; j++){ //on ajoute une transition de i vers le dernier état = etat poubelle
                complet.nb_trans ++;
                complet.transitions.emplace_back(i, alpha_temp[j], nb_etats);
            }
        }
        alpha_temp.clear(); //le tableau est remis à vide pour le prochain état
    }
    ordonner_vector_transition(complet.transitions);
    if(!complet.etat_compose.empty()){
        complet.etat_compose.push_back(to_string(complet.nb_etats)); // ajout de l'etat poubelle
    }
    else{
        for(int i = 0 ; i < complet.nb_etats ; i++){
            etat_compose.push_back(to_string(i)); // ajout de tous les etats, cas où l'automate etait deja deterministe donc etat_compose non rempli
        }
    }
    return complet;
}

Automate Automate::standardisation() {
    Automate temp(*this);
    temp.nb_etats++;

    if(!temp.est_automate_standard()){
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

    //Chargement des etat compose
    af_deter.etat_compose = etat_traite;

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
    af_deter.etat_compose.clear();

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
            compose = determiner_transition_epsilon(compose); //l'etat construit est remplacé par sa fermeture epsilon
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

    //Chargement des etat compose
    af_deter.etat_compose = etat_traite;


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
    afdc = afdc.completion();
    return afdc;
}

Automate Automate::determinisation_et_completion() {
    Automate afdc(*this);
    afdc = afdc.determinisation();
    afdc = afdc.completion();
    return afdc;
}

Automate Automate::minimisation() {
    Automate afdcm(*this);
    afdcm.nb_etats = 0;
    afdcm.nb_init = 0;
    afdcm.init.clear();
    afdcm.nb_term = 0;
    afdcm.term.clear();
    afdcm.nb_trans = 0;
    afdcm.transitions.clear();

    string tempo;
    vector<int> partition_0;
    vector<int> partition_1;
    vector<Transition> transi_0;
    vector<Transition> transi_1;
    vector<Transition> table_transition;
    int nb_partie = 0;
    bool fini;

    //Partition initial (separation terminaux et autres)
    for (int i = 0 ; i < nb_etats ; i++){
        bool fait = false;
        for (int j = 0 ; j < nb_term ; j++){
            if (i == term[j]){
                partition_0.push_back(2);
                fait = true;
            }
        }
        if (!fait){
            partition_0.push_back(1);
        }
    }
    nb_partie = 2;
    //boucle de minimisation
    do {
        table_transition.clear();
        //Nouvelle table de transition
        for (int i = 0; i < nb_trans ; i++) {
            int p = transitions[i].getP();
            char symb = transitions[i].getSymb();
            int q = partition_0[transitions[i].getQ()]; //q = la partition dans lequel se trouve l'etat d'arrivé
            table_transition.emplace_back(p, symb, q);
        }

        //Determination de la nouvella partition
        nb_partie = 0;
        bool fait;
        int taille_partition;
        for (int i = 0; i < nb_etats; i++) {
            fait = false;
            taille_partition = partition_1.size();
            for (int j = 0; j < taille_partition; j++) {
                for (int k = 0; k < nb_symb; k++) {
                    transi_0.push_back(table_transition[nb_symb * i + k]);
                    transi_1.push_back(table_transition[nb_symb * j + k]);
                }
                if ((transition_egale(transi_0, transi_1)) and (partition_0[i] == partition_0[j]) and (!fait)) { //les transitions doivent être identique et les etats dans la même partition
                    partition_1.push_back(partition_1[j]);
                    fait = true;
                }
                transi_0.clear();
                transi_1.clear();
            }
            if (!fait) {
                partition_1.push_back(nb_partie + 1);
                nb_partie++;
            }
            transi_0.clear();
            transi_1.clear();
        }
        if (partition_0 == partition_1) {
            fini = true;
        } else {
            fini = false;
            partition_0 = partition_1;
            partition_1.clear();
        }
    }while(!fini);



    //Table de transition de l'afdcm
    vector<int> etat_cree;
    for (int i = 0 ; i < partition_0.size() ; i++){
        if (!int_in__element_of_vector(partition_0[i]-1, etat_cree)){
            for (int j = 0 ; j < nb_symb ; j++){
                int p = partition_0[i]-1; //-1 car partition commence à 1 et etat n°1 = 0
                int symb = table_transition[nb_symb * i + j].getSymb();
                int q = table_transition[nb_symb * i + j].getQ()-1;
                afdcm.transitions.emplace_back(p,symb,q);
                afdcm.nb_trans++;
            }
            etat_cree.push_back(partition_0[i]-1);
        }
    }

    //Nombre d'etat
    afdcm.nb_etats = nb_partie;

    //Determiner initiaux
    afdcm.nb_init = 1; //car deterministe
    afdcm.init.push_back(0);

    //Determiner terminaux
    supprimer_doublon_vector_int(partition_0);
    for (int i = 0 ; i < partition_0.size() ; i++){
        for (int j = 0 ; j < nb_term ; j++){
            if (i == term[j]){
                afdcm.term.push_back(partition_0[i]);
                afdcm.nb_term++;
            }
        }
    }

    //Remplissage de l'etat compose

    afdcm.etat_compose.clear();
    tempo = to_string(0);
    for (int i = 1 ; i < partition_1.size() ; i++){
        if (partition_1[i] == partition_1[i-1]){
            tempo += ",";
            tempo += to_string(i);
        }
        else{
            afdcm.etat_compose.push_back(tempo);
            tempo = to_string(i);
        }
    }
    afdcm.etat_compose.push_back(tempo); // ajout du dernier etat

    return afdcm;
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
    ///Affichage sans les etats composé
    int nb_espace_debut = 0;
    int nb_espace = get_taille_max_table_transition(this->getTransitions());
    int taille_max = to_string(nb_etats-1).size();
    bool est_init;
    bool est_async;
    string tempo;

    //si l'automate est asynchrone, on ajoute epsilon
    est_async = est_automate_asynchrone();
    if(est_async){
        add_epsilon_alphabet();
    }

    cout << "*****************************************************" << endl;
    cout << "*****     Table de transitions de l'automate    *****" << endl;
    cout << "*****************************************************" << endl;

    //affichage ligne 1
    cout << string((taille_max+4), ' ') << "|";
    for (int i = 0 ; i < alphabet.size() ; i++){
        cout << string((nb_espace+1), ' ') << alphabet[i] << "|";
    }
    cout << endl;

    //Boucle affichage etat et transition
    for (int i = 0 ; i < nb_etats ; i++){
        //affichage fleche etat init et term
        nb_espace_debut = 4;
        est_init = false;
        for(int j = 0 ; j < init.size() ; j++) {
            if (i == init[j]) {
                cout << "->";
                nb_espace_debut -= 2;
                est_init = true;
            }
        }
        for(int j = 0 ; j < term.size() ; j++) {
            if (i == term[j]) {
                if (est_init){
                    cout << "<-";
                } else{
                    cout << "  <-";
                }
                nb_espace_debut = 0;
            }
        }
        //affichage etat
        cout << string(((taille_max - to_string(i).size()) + nb_espace_debut), ' ') << i << "|";

        //affichage des transitions
        for (int k = 0 ; k < alphabet.size() ; k++){
            for (int j = 0 ; j < transitions.size() ; j++){
                if ((transitions[j].getP() == i) and (transitions[j].getSymb() == alphabet[k])){
                    if (!tempo.empty()){
                        tempo += ",";
                    }
                    tempo += to_string(transitions[j].getQ());
                }
            }
            cout << string(( 2 + nb_espace - (tempo.size())), ' ') << tempo << "|";
            tempo.clear();
        }
        cout << endl;
    }
    if (est_async){
        alphabet.pop_back();
    }
    cout << endl;
}

void Automate::afficher_automate_deterministe_complet(){
    cout << "*****************************************************" << endl;
    cout << "*****     Table de transitions de l'automate    *****" << endl;
    cout << "*****************************************************" << endl;

    int nb_espace_debut = 0;
    int nb_espace = get_taille_max_table_transition(this->getTransitions());
    int nb_espace_etat_compose = 0;
    int taille_max = to_string(nb_etats-1).size();
    bool est_init;
    string tempo;

    //affichage ligne 1
    if (!etat_compose.empty()){
        nb_espace_etat_compose = get_nb_char_max_in_string(this->etat_compose);
    }else{
        for (int i = 0 ; i < nb_etats ; i++){
            etat_compose.push_back(to_string(i));
        }
        nb_espace_etat_compose = taille_max;
    }
    cout << string((7 + taille_max + nb_espace_etat_compose), ' ') << "|";
    for (int i = 0 ; i < alphabet.size() ; i++){
        cout << string((nb_espace+1), ' ') << alphabet[i] << "|";
    }
    cout << endl;

    //Boucle affichage etat et transition
    for (int i = 0 ; i < nb_etats ; i++){
        //affichage fleche etat init et term
        nb_espace_debut = 4;
        est_init = false;
        for(int j = 0 ; j < init.size() ; j++) {
            if (i == init[j]) {
                cout << "->";
                nb_espace_debut -= 2;
                est_init = true;
            }
        }
        for(int j = 0 ; j < term.size() ; j++) {
            if (i == term[j]) {
                if (est_init){
                    cout << "<-";
                } else{
                    cout << "  <-";
                }
                nb_espace_debut = 0;
            }
        }
        //affichage etat
        cout << string(((taille_max - to_string(i).size()) + nb_espace_debut), ' ') << i << " = " << string((nb_espace_etat_compose - etat_compose[i].size()) , ' ') << etat_compose[i] <<"|";

        //affichage des transitions
        for (int k = 0 ; k < alphabet.size() ; k++){
            for (int j = 0 ; j < transitions.size() ; j++){
                if ((transitions[j].getP() == i) and (transitions[j].getSymb() == alphabet[k])){
                    if (!tempo.empty()){
                        tempo += ",";
                    }
                    tempo += to_string(transitions[j].getQ());
                }
            }
            cout << string(( 2 + nb_espace - (tempo.size())), ' ') << tempo << "|";
            tempo.clear();
        }
        cout << endl;
    }
    cout << endl;
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
    etat_compose = Af.etat_compose;
    alphabet = Af.alphabet;
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

void Automate::add_epsilon_alphabet() {
    alphabet.push_back('*');
}




