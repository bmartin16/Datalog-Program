//
// Created by 18bma on 9/10/2021.
//

#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H
#include "Automaton.h"

class IdAutomaton : public Automaton {
private:
    void S1(const string& input);
public:
    IdAutomaton() : Automaton(TokenType::ID) {}
    int Read(const string& input);
};


#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
