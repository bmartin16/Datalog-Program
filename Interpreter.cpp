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

void Interpreter::evaluateQueries(){
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