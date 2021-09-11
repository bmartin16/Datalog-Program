//
// Created by 18bma on 9/10/2021.
//

#include "LineCommentAutomaton.h"

int LineCommentAutomaton::Read(const string& input) {
    if(input.at(index) == '#') {
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

void LineCommentAutomaton::S1(const string& input) {
    if(input.at(index) == '\n' || index == input.size() - 1) {
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}