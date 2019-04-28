//
// Created by Vincent on 28/04/2019.
//

#include "fonction.h"
#include <iostream>
#include <algorithm>

using namespace std;

void ordonner_string(string& str) {
    sort(str.begin(), str.end());
}

void supprimer_doublon_string(std::string & s) {

    for (int i = 0 ; i < s.size(); i++ )
    {
        int j = i + 1;
        while ( j < s.size() )
        {
            if ( s[i] == s[j] )
            {
                s.erase( j, 1 );
            }
            else
            {
                ++j;
            }
        }
    }
}

bool string_in_vector(string str, vector<string> vector) {
    bool ok = false;
    for (int i = 0 ; i < vector.size() ; i++){
        if (str == vector[i]){
            ok = true;
        }
    }
    return ok;
}
