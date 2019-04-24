//
// Created by Vincent on 24/04/2019.
//

#include "Transition.h"
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

void Transition::setP(int _p) {
    p = _p;
}

char Transition::getSymb() const {
    return symb;
}

void Transition::setSymb(char _symb) {
    symb = _symb;
}

int Transition::getQ() const {
    return q;
}

void Transition::setQ(int _q) {
    q = _q;
}

void Transition::print() const {
    cout << p << " " << symb << " " << q << endl;
}
