#ifndef TESTY_E4_TRANSITION_H
#define TESTY_E4_TRANSITION_H


class Transition {
    private:
        int p;
        char symb;
        int q;

    public:
        //Constructeur
        Transition(int, char, int);

        //Getter et setter
        void print() const;
        int getP() const;
        char getSymb() const;
        int getQ() const;
};


#endif //TESTY_E4_TRANSITION_H
