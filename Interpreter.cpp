//
// Created by 18bma on 10/21/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(){}

Interpreter::Interpreter(DatalogProgram myDatalogProgram){
    this->myDatalogProgram = myDatalogProgram;
    map<string, Relation*> myMap;
    for(unsigned int i = 0; i < this->myDatalogProgram.schemeList.size(); i++){
        Header header(this->myDatalogProgram.returnPredicateNames(this->myDatalogProgram.schemeList.at(i).parameterList));
        Relation *relation = new Relation(this->myDatalogProgram.schemeList.at(i).predicateName, header);
        myMap[this->myDatalogProgram.schemeList.at(i).predicateName] = relation;
    }
    myDatabase.setDatabase(myMap);
    for(unsigned int i = 0; i < this->myDatalogProgram.factList.size(); i++){
        Relation *myRelation = myDatabase.findRelation(this->myDatalogProgram.factList.at(i).predicateName);
        Tuple tuple(this->myDatalogProgram.returnPredicateNames(this->myDatalogProgram.factList.at(i).parameterList));
        myRelation->addTuple(tuple);
        myDatabase.findRelation(this->myDatalogProgram.factList.at(i).predicateName) -> addTuple(tuple);
    }
}

Relation* Interpreter::evaluatePredicate(Predicate p) {
    Relation *original = myDatabase.findRelation(p.predicateName);
    map<string, int> variableTracker;
    vector<string> variableList;
    Relation *newRelation = new Relation;
    newRelation->setHeader(original->getHeader());
    for(unsigned int i = 0; i < p.parameterList.size(); i++){
        if(p.parameterList.at(i).isString == true){
            newRelation = original->Select(i, p.parameterList.at(i).tokenDescription);
            newRelation->setHeader(original->getHeader());
            original = newRelation;
        }
    }
    for(unsigned int i = 0; i < p.parameterList.size(); i++){
        if(p.parameterList.at(i).isString == false){
            if(variableTracker.find(p.parameterList.at(i).tokenDescription) != variableTracker.end()){
                newRelation = original->Select2(i, variableTracker, p.parameterList.at(i).tokenDescription);
                newRelation->setHeader(original->getHeader());
                original = newRelation;
            }
            else{
                variableTracker[p.parameterList.at(i).tokenDescription] = i;
                variableList.push_back(p.parameterList.at(i).tokenDescription);
            }
        }
    }
    newRelation = original->Project(variableList, variableTracker);
    newRelation = original->Rename(newRelation, variableList, variableTracker);
    newRelation->setCounter(newRelation->getRows().size());
    newRelation->setVariableList(variableList);
    newRelation->setVariableTracker(variableTracker);
    return newRelation;
}

bool Interpreter::evaluateRule(Rule r){
    bool repeat;
    vector<string> headPredicateAttributes;
    map<string, int> variableTracker;
    Relation *newRelation = evaluatePredicate(r.bodyPredicateList.at(0));
    for(unsigned int i = 0; i < r.bodyPredicateList.size()-1; i++){
        newRelation = newRelation->Join(evaluatePredicate(r.bodyPredicateList.at(i+1)));
    }
    for(unsigned int i = 0; i < newRelation->getHeader().getAttributes().size(); i++){
        variableTracker[newRelation->getHeader().getAttributes().at(i)] = i;
    }
    for(unsigned int i = 0; i < r.headPredicate.parameterList.size(); i++){
        headPredicateAttributes.push_back(r.headPredicate.parameterList.at(i).tokenDescription);
    }
    newRelation = newRelation->Project(headPredicateAttributes, variableTracker);
    newRelation->setHeader(headPredicateAttributes);
    repeat = myDatabase.findRelation(r.headPredicate.predicateName)->FusionHa(newRelation);
    return repeat;
}

void Interpreter::evaluateRules(set<int> SSC, bool dependsOnSelf){
    bool repeat = true;
    int count = 0;
    if(SSC.size() > 1 || dependsOnSelf == true) {
        while (repeat == true) {
            int checkCount = 0;
            set<int>::iterator it;
            for (it = SSC.begin(); it != SSC.end(); it++) {
                myDatalogProgram.ruleList.at(*it).RuleToString();
                cout << endl;
                bool check = evaluateRule(this->myDatalogProgram.ruleList.at(*it));
                if (check == true) {
                    checkCount++;
                }
            }
            count++;
            if (checkCount == 0) {
                repeat = false;
            }
        }
    }
    else{
        int checkCount = 0;
        set<int>::iterator it;
        for (it = SSC.begin(); it != SSC.end(); it++) {
            myDatalogProgram.ruleList.at(*it).RuleToString();
            cout << endl;
            bool check = evaluateRule(this->myDatalogProgram.ruleList.at(*it));
            if (check == true) {
                checkCount++;
            }
        }
        count++;
        if (checkCount == 0) {
            repeat = false;
        }
    }
    cout << count << " passes: ";
}



void Interpreter::evaluateQueries(){
    cout << "Query Evaluation" << endl;
    Relation *newRelation = new Relation;
    for(unsigned int i = 0; i < this->myDatalogProgram.queryList.size(); i++){
        newRelation = evaluatePredicate(this->myDatalogProgram.queryList.at(i));
        myDatalogProgram.queryList.at(i).QueryToString();
        cout << " ";
        if(newRelation->getQueryCounter() > 0){
            cout << "Yes(" << newRelation->getQueryCounter() << ")" << endl;
            newRelation->toString();
        }
        else{
            cout << "No" << endl;
        }
    }
}

Graph* Interpreter::makeGraph() {
    Graph *forwardGraph = new Graph();
    map<int, set<int>> adjacencyList;
    for(unsigned int i = 0; i < this->myDatalogProgram.ruleList.size(); i++){
        set<int> adjacencies;
        for(unsigned int j = 0; j < this->myDatalogProgram.ruleList.size(); j++){
            for(unsigned int k = 0; k < this->myDatalogProgram.ruleList.at(i).bodyPredicateList.size(); k++) {
                if(this->myDatalogProgram.ruleList.at(j).headPredicate.predicateName == this->myDatalogProgram.ruleList.at(i).bodyPredicateList.at(k).predicateName){
                    adjacencies.insert(j);
                }
            }
        }
      adjacencyList[i] = adjacencies;
    }
    forwardGraph->setAdjacencyList(adjacencyList);
    return forwardGraph;
}

Graph* Interpreter::makeReverseGraph() {
    Graph *forwardGraph = makeGraph();
    map<int, set<int>> adjacencyList = forwardGraph->getAdjacencyList();
    Graph *reverseGraph = new Graph();
    map<int, set<int>> reverseAdjacencyList;
    for(unsigned int i = 0; i < adjacencyList.size(); i++){
        set<int>::iterator it;
        for(it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it){
                reverseAdjacencyList[(*it)].insert(i);
        }
        if(reverseAdjacencyList[i].size() == 0){
            reverseAdjacencyList[i] = {};
        }
    }
    reverseGraph->setAdjacencyList(reverseAdjacencyList);
    return reverseGraph;
}

Graph* Interpreter::postorderDepthFirstSearch(Graph *reverseGraph, int node) {
    map<int, set<int>> reverseAdjacencyList = reverseGraph->getAdjacencyList();
    set<int>::iterator it;
    reverseGraph->visited[node] = true;
    for(it = reverseAdjacencyList[node].begin(); it != reverseAdjacencyList[node].end(); ++it){
        if(reverseGraph->visited[*it] != true){
            postorderDepthFirstSearch(reverseGraph, (*it));
        }
    }

    reverseGraph->postorderList[reverseGraph->counter] = node;
    reverseGraph->counter++;

    return reverseGraph;
}

set<int> Interpreter::SSCDepthFirstSearch(Graph *forwardGraph, int node, set<int> &component){
    map<int, set<int>> adjacencyList = forwardGraph->getAdjacencyList();
    set<int>::iterator it;
    forwardGraph->visited[node] = true;
    forwardGraph->counter++;
    for(it = adjacencyList[node].begin(); it != adjacencyList[node].end(); ++it){
        if(forwardGraph->visited[*it] != true){
            SSCDepthFirstSearch(forwardGraph, (*it), component);
        }
    }
    component.insert(node);
    forwardGraph->beginNode = forwardGraph->postorderList[forwardGraph->getAdjacencyList().size()-((forwardGraph->counter)+1)];

    if(forwardGraph->counter == adjacencyList.size()){
        for(unsigned int i = 0; i < adjacencyList.size(); i++) {
            if(forwardGraph->visited[i] != true) {
                forwardGraph->beginNode = i;
            }
        }
        forwardGraph->done = true;
    }

    return component;
}

void Interpreter::printGraph(Graph *forwardGraph){
    cout << "Dependency Graph" << endl;
    map<int, set<int>> adjacencyList;
    adjacencyList = forwardGraph->getAdjacencyList();
    for(unsigned int i = 0; i < adjacencyList.size(); i++){
        cout << "R" << i << ":";
        set<int>::iterator it;
        for(it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it){
            cout << "R" << (*it);
            if(next(it) != adjacencyList[i].end()){
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}
