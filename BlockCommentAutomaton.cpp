//
// Created by 18bma on 9/10/2021.
//

#include "BlockCommentAutomaton.h"

int BlockCommentAutomaton::Read(const string& input) {
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

void BlockCommentAutomaton::S1(const string& input) {
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

void BlockCommentAutomaton::S2(const string& input) {
    if(input.at(index) == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == input.size() - 1) {
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

void BlockCommentAutomaton::S3(const string& input) {
    if(input.at(index) == '#') {
        inputRead++;
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}