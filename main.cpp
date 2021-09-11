#include "Lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    Lexer *lexer = new Lexer();
    string inputString;
    string fileName = "input1.txt";
    ifstream iFile(fileName);
    if(iFile.is_open()) {
        ostringstream ss;
        ss << iFile.rdbuf();
        inputString = ss.str();
    }
    lexer->Run(inputString);
    for(unsigned int i = 0; i < lexer->getTokenVector().size(); i++) {
        cout << lexer->getTokenVector().at(i)->toString() << endl;
    }
    cout << "Total Tokens = " + to_string(lexer->getTokenVector().size());

    // TODO

    delete lexer;

    return 0;
}