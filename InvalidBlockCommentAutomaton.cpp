//
// Created by 18bma on 9/10/2021.
//

#include "InvalidBlockCommentAutomaton.h"

int InvalidBlockCommentAutomaton::Read(const string& input) {
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

void InvalidBlockCommentAutomaton::S1(const string& input) {
    if(input.at(index) == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
        inputRead = 0;
    }
}

void InvalidBlockCommentAutomaton::S2(const string& input) {
    if(input.at(index) == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == input.size() - 1) {
         newLines++;
         inputRead++;
    }
    else if(input.at(index) == '\n') {
        newLines++;
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void InvalidBlockCommentAutomaton::S3(const string& input) {
    if(input.at(index) == '#') {
        Serr();
    }
    else if(input.at(index) == '\n') {
        newLines++;
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}