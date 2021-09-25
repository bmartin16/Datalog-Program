#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    vector<Token*> tokenList;
    DatalogProgram myDatalogProgram;
    Lexer *lexer = new Lexer();
    string inputString;
    string fileName = argv[1];
    ifstream iFile(fileName);
    if(iFile.is_open()) {
        ostringstream ss;
        ss << iFile.rdbuf();
        inputString = ss.str();
    }
    lexer->Run(inputString);
    /*
    for(unsigned int i = 0; i < lexer->getTokenVector().size(); i++) {
        cout << lexer->getTokenVector().at(i)->toString() << endl;
    }
    cout << "Total Tokens = " + to_string(lexer->getTokenVector().size());
     */
    tokenList = lexer->getTokenVector();
    Parser *parser = new Parser(tokenList);
    try{
        myDatalogProgram = parser->datalogProgram();
        cout << "Success!" << endl;
        myDatalogProgram.ToString();

    }
    catch(Token* token){
        cout << "Failure!" << endl;
        cout << "  " << token->toString();
    }


    // TODO

    delete lexer;

    return 0;
}