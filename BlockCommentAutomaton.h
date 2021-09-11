//
// Created by 18bma on 9/10/2021.
//

#ifndef PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H
#include "Automaton.h"

class BlockCommentAutomaton : public Automaton {
private:
    void S1(const string& input);
    void S2(const string& input);
    void S3(const string& input);
public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}
    int Read(const string& input);

};


#endif //PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H
