//
// Created by 18bma on 9/10/2021.
//

#include "StringAutomaton.h"

int StringAutomaton::Read(const string& input) {
    if(input.at(index) == '\'') {
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

void StringAutomaton::S1(const string& input) {
    if(input.at(index) == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if(index == input.size() - 1) {
        Serr();
    }
    else if(input.at(index) == '\n') {
        newLines++;
        inputRead++;
        index++;
        S1(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const string& input) {
    if(input.at(index) != '\'') {
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}


