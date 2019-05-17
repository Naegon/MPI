#include "E4-Transition.h"
#include <iostream>

using namespace std;

Transition::Transition(int _p, char _symb, int _q) {
    p = _p;
    symb = _symb;
    q = _q;
}

int Transition::getP() const {
    return p;
}

char Transition::getSymb() const {
    return symb;
}

int Transition::getQ() const {
    return q;
}

void Transition::print() const {
    cout << p << " " << symb << " " << q;
}
