#include <iostream>
#include "Transition.h"
#include "Automate.h"
#include <vector>

using namespace std;

int main() {
    vector<Transition> transitions;
    transitions.emplace_back(Transition(2, 'a', 3));
    transitions.emplace_back(Transition(4, 'r', 0));
    transitions.emplace_back(Transition(3, 'd', 7));

    vector<int> init;
    init.push_back(2);
    vector<int> term;
    term.push_back(3);
    term.push_back(5);

    Automate test(3, 8, 1, init, 2, term, 3, transitions);
    test.print();

    Automate read("/Automates_test/L2-E4-1.txt");
    return 0;
}
