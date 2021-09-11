//
// Created by 18bma on 9/9/2021.
//

#include "MatcherAutomaton.h"

int MatcherAutomaton::Read(const std::string& input) {
    bool isMatch = true;
    int inputRead = 0;
    for (unsigned int i = 0; i < toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if(isMatch) {
        inputRead = toMatch.size();
        type = tokenType;
    }
    return inputRead;
}