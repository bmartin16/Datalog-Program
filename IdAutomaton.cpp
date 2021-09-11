//
// Created by 18bma on 9/10/2021.
//

#include "IdAutomaton.h"

int IdAutomaton::Read(const string& input) {
    if(isalpha(input.at(index))) {
        inputRead++;
        index++;
        S1(input);
        return inputRead;
    }
    else {
        Serr();
        return 0;
    }
}

void IdAutomaton::S1(const string& input) {
    if(isalnum(input.at(index))) {
        inputRead++;
        index++;
        S1(input);
    }
    else{
    }
}
