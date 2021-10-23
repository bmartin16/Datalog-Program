//
// Created by 18bma on 10/21/2021.
//

#include "Relation.h"

Relation::Relation(){}

Relation::Relation(string name, Header header){
    this->name = name;
    this->header = header;
}

Header Relation::getHeader(){
    return header;
}

void Relation::setHeader(Header header){
    this->header = header;
}

void Relation::toString(){
    for (Tuple t : rows) {
        if(t.getValues().size() > 0){
            cout << "  ";
        }
        for(unsigned int i = 0; i < t.getValues().size(); i++){
            cout << header.getAttributes().at(i) << "=" << t.getValues().at(i);
            if(i < t.getValues().size() - 1){
                cout << ", ";
            }
        }
        if(t.getValues().size() > 0){
            cout << endl;
        }
    }
    return;
}

void Relation::addTuple(Tuple t){
    rows.insert(t);
    return;
}

void Relation::setCounter(int num){
    queryCounter = num;
}

void Relation::setVariableTracker(map<string, int> variableTracker){
   this->variableTracker = variableTracker;
}

void Relation::setVariableList(vector<string> variableList){
    this->variableList = variableList;
}

map<string, int> Relation::getVariableTracker(){
    return variableTracker;
}

vector<string> Relation::getVariableList(){
    return variableList;
}

set<Tuple> Relation::getRows(){
    return rows;
}

int Relation::getQueryCounter(){
    return queryCounter;
}

Relation* Relation::Select(int columnNumber, string rowID){
    Relation* relation = new Relation();
    for(Tuple t: rows) {
        if(t.getValues().at(columnNumber) == rowID){
            relation->addTuple(t);
        }
    }
    return relation;
}

Relation* Relation::Select2(int columnNumber, map<string, int> variableTracker, string rowID){
    Relation* relation = new Relation();
    for(Tuple t: rows) {
        if(t.getValues().at(variableTracker[t.getValues().at(columnNumber)]) == t.getValues().at(columnNumber)){
            relation->addTuple(t);
        }
    }
    return relation;
}

Relation* Relation::Project(vector<string> variableList, map<string, int> variableTracker){
    Relation *newRelation = new Relation;
    for(Tuple t: rows){
        Tuple newTuple;
        for(unsigned int i = 0; i < variableList.size(); i++) {
            newTuple.addValue(t.getValues().at(variableTracker[variableList.at(i)]));
        }
        newRelation->addTuple(newTuple);
    }
    return newRelation;
}

Relation* Relation::Rename(Relation *relation, vector<string> variableList, map<string, int> variableTracker){
    for (unsigned int i = 0; i < variableList.size(); i++) {
        relation->header.addAttribute(this->header.getAttributes().at(variableTracker[variableList.at(i)]));
        relation->header.setAttribute(variableList.at(i), i);
    }
    return relation;
}