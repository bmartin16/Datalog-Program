#include "Lexer.h"
#include "MatcherAutomaton.h"
#include "StringAutomaton.h"
#include "IncompleteStringAutomaton.h"
#include "IdAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "InvalidBlockCommentAutomaton.h"
#include "Token.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton(":", TokenType::COLON));
    automata.push_back(new MatcherAutomaton(":-", TokenType::COLON_DASH));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new StringAutomaton());
    automata.push_back(new IncompleteStringAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new InvalidBlockCommentAutomaton());

    // TODO: Add the other needed automata here
}

vector<Token*> Lexer::getTokenVector() {
    return tokens;
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    int lineNumber = 1;
    int inputRead = 0;
    while(input.size() > 0) {
        int maxRead = 0;
        if(input.at(0) == '\n'){
            lineNumber += 1;
        }
        Automaton *maxAutomaton = automata[0];
        for (unsigned int i = 0; i < automata.size(); i++) {
            inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (maxRead > 0) {
            string value = input.substr(0, maxRead);
            Token *newToken = maxAutomaton->CreateToken(value, lineNumber);
            tokens.push_back(newToken);
            lineNumber += maxAutomaton->NewLinesRead();
            input.erase(0, maxRead);
        }
        else if (!isspace(input.at(0))){
            maxRead = 1;
            char c = input.at(0);
            Token *newToken = new Token(TokenType::UNDEFINED, c, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
            input.erase(0, maxRead);


        }
        else {
            maxRead = 1;
            input.erase(0, maxRead);
        }
    }
    Token *newToken = new Token(TokenType::END, "", lineNumber);
    tokens.push_back(newToken);
}
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
