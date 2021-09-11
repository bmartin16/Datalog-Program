//
// Created by 18bma on 9/10/2021.
//

#ifndef PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
#include "Automaton.h"

class LineCommentAutomaton : public Automaton {
private:
    void S1(const string& input);
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}
    int Read(const string& input);
};


#endif //PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
