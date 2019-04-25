#include <iostream>
#include "Transition.h"
#include "Automate.h"
#include <vector>

using namespace std;





int main() {
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
    //Automate read("/Automates_test/L2-E4-1.txt");
    return 0;
}
