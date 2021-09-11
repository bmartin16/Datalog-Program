#include "Lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    ifstream iFile;
    Lexer *lexer = new Lexer();
    string inputString;
    iFile.open("input1.txt", ios::in);
    if(iFile) {
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