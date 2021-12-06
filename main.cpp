#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Token.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    vector<Token*> tokenList;
    DatalogProgram myDatalogProgram;
    Graph* myReverseGraph;
    bool dependsOnSelf;
    Graph* myGraph;
    set<int> dummySet;
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
        //myDatalogProgram.ToString();

    }
    catch(Token* token){
        cout << "Failure!" << endl;
        cout << "  " << token->toString() << endl;
    }

    Interpreter *interpreter = new Interpreter(myDatalogProgram);
    myReverseGraph = interpreter->postorderDepthFirstSearch(interpreter->makeReverseGraph(), 0);
    if(myReverseGraph->counter < myReverseGraph->getAdjacencyList().size()){
        for(unsigned int i = 0; i < myReverseGraph->getAdjacencyList().size(); i++) {
            if(myReverseGraph->visited[i] != true) {
                interpreter->postorderDepthFirstSearch(myReverseGraph, i);
            }
        }
    }
    myGraph = interpreter->makeGraph();
    myGraph->postorderList= myReverseGraph->postorderList;
    myGraph->beginNode = myGraph->postorderList[myGraph->getAdjacencyList().size()-1];
    while(myGraph->done == false){
        dummySet = {};
        myGraph->stronglyConnectedComponents.push_back(interpreter->SSCDepthFirstSearch(myGraph, myGraph->beginNode, dummySet));
    }
    interpreter->printGraph(myGraph);
    cout << "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < myGraph->stronglyConnectedComponents.size(); i++) {
        dependsOnSelf = false;
        map<int, set<int>> adjacencyList = myGraph->getAdjacencyList();
        set<int> SSC = myGraph->getStronglyConnectedComponents().at(i);
        set<int>::iterator it2;
        set<int>::iterator it3;
        for(it3 = SSC.begin(); it3 != SSC.end(); it3++) {
            for (it2 = adjacencyList[*it3].begin(); it2 != adjacencyList[*it3].end(); ++it2) {
                if (*it3 == (*it2)) {
                    dependsOnSelf = true;
                }
            }
        }
        cout << "SCC: ";
        set<int>::iterator it1;
        for (it1 = myGraph->stronglyConnectedComponents.at(i).begin(); it1 != myGraph->stronglyConnectedComponents.at(i).end(); it1++) {
            cout << "R" << (*it1);
            if(next(it1) != myGraph->stronglyConnectedComponents.at(i).end()){
                cout << ",";
            }
        }
        cout << endl;
        interpreter->evaluateRules(myGraph->stronglyConnectedComponents.at(i), dependsOnSelf);
        for (it1 = myGraph->stronglyConnectedComponents.at(i).begin(); it1 != myGraph->stronglyConnectedComponents.at(i).end(); it1++) {
            cout << "R" << (*it1);
            if(next(it1) != myGraph->stronglyConnectedComponents.at(i).end()){
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
    interpreter->evaluateQueries();

    // TODO

    delete lexer;

    return 0;
}