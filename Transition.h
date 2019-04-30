//
// Created by Vincent on 24/04/2019.
//

#ifndef TESTY_TRANSITION_H
#define TESTY_TRANSITION_H


class Transition {
    private:
        int p;
        char symb;
        int q;
    public:
        Transition(int, char, int);

        void print() const;

        int getP() const;
        void setP(int p);
        char getSymb() const;
        void setSymb(char symb);
        int getQ() const;
        void setQ(int q);

};


#endif //TESTY_TRANSITION_H
