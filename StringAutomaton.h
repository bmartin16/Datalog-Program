//
// Created by 18bma on 9/10/2021.
//
#include "Automaton.h"

#ifndef PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
#define PROJECT1_STARTER_CODE_STRINGAUTOMATON_H


class StringAutomaton : public Automaton {
private:
    void S1(const string& input);
    void S2(const string& input);
public:
    StringAutomaton() : Automaton(TokenType::STRING) {}
    int Read(const string& input);
};


#endif //PROJECT1_STARTER_CODE_STRINGAUTOMATON_H
