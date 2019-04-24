#include <iostream>
#include "Transition.h"
#include "Automate.h"
#include <vector>

using namespace std;

int main() {
    vector<Transition> transitions;
    transitions[0] = Transition(2, 'a', 3);
    transitions[1] = Transition(4, 'r', 0);
    transitions[2] = Transition(3, 'd', 7);

    transitions[0].print();

    vector<int> init;
    init.push_back(2);
    vector<int> term;
    term.push_back(3);
    term.push_back(5);

    cout << term[0] << endl;

    Automate test(3, 8, 1, init, 2, term, 3, transitions);
    test.print();

    return 0;
}
