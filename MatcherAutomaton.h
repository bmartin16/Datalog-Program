//
// Created by 18bma on 9/9/2021.
//

#ifndef PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#define PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#include "Automaton.h"

class MatcherAutomaton : public Automaton {
private:
    std::string toMatch;
    TokenType tokenType;
public:
    MatcherAutomaton(std::string toMatch, TokenType tokenType) {
        this->toMatch = toMatch;
        this->tokenType = tokenType;
    }

    int Read(const std::string &input);

};
#endif //PROJECT1_STARTER_CODE_MATCHERAUTOMATA_H
