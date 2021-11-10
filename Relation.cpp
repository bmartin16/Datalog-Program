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

Relation* Relation::Join(Relation *relation){
    Relation *newRelation = new Relation;
    newRelation->setHeader(this->getHeader());
    vector<int> matchingIndicies;
    vector<int> differentIndicies;
    vector<pair<int, int>> pairList;
    bool same;
    bool combine;
    for(unsigned int i = 0; i < relation->getHeader().getAttributes().size(); i++){
        same = false;
        for(unsigned int j = 0; j < this->getHeader().getAttributes().size(); j++){
            if(relation->getHeader().getAttributes().at(i) == this->getHeader().getAttributes().at(j)){
                same = true;
                pair<int, int> whereDoTheyMatch;
                whereDoTheyMatch.first = i;
                whereDoTheyMatch.second = j;
                pairList.push_back(whereDoTheyMatch);
            }
        }
        if(same == true){
            matchingIndicies.push_back(i);
        }
        else{
            differentIndicies.push_back(i);
        }
    }
    //Combine Headers
    for(unsigned int i = 0; i < differentIndicies.size(); i++){
        newRelation->header.addAttribute(relation->getHeader().getAttributes().at(differentIndicies.at(i)));
    }
    //check if the tuples are able to be combined
    for(Tuple t: relation->getRows()){
        for(Tuple t2: rows){
            combine = false;
            for(unsigned int i = 0; i < pairList.size(); i++){
                if(t.getValues().at(pairList.at(i).first) == t2.getValues().at(pairList.at(i).second)){
                    combine = true;
                }
                else {
                    combine = false;
                    break;
                }
            }
            if(combine == true && differentIndicies.size() > 0){
                Tuple newTuple;
                newTuple = t2;
                for(unsigned int i = 0; i < differentIndicies.size(); i++) {
                        newTuple.addValue(t.getValues().at(differentIndicies.at(i)));
                }
                newRelation->addTuple(newTuple);
            }
            if(combine == true && differentIndicies.size() == 0){
                Tuple newTuple;
                newTuple = t2;
                for(unsigned int i = 0; i < matchingIndicies.size(); i++) {
                    newTuple.addValue(t.getValues().at(matchingIndicies.at(i)));
                }
                newRelation->addTuple(newTuple);
            }
            if(matchingIndicies.size() == 0){
                Tuple newTuple;
                newTuple = t2;
                for(unsigned int i = 0; i < t.getValues().size(); i++) {
                    newTuple.addValue(t.getValues().at(i));
                }
                newRelation->addTuple(newTuple);
            }
        }
    }
    return newRelation;
}

bool Relation::FusionHa(Relation *relation) {
    bool newTuples = false;
    for(Tuple t: relation->getRows()){
        bool combine = true;
        for(Tuple t2: rows){
            if(t.getValues() == t2.getValues()){
                combine = false;
            }
        }
        if(combine == true) {
            newTuples = true;
            this->addTuple(t);
            for(unsigned int i = 0; i < this->getHeader().getAttributes().size(); i++){
                if(i == 0){
                    cout << "  ";
                }
                cout << this->getHeader().getAttributes().at(i) << "=" << t.getValues().at(i);
                if(i < this->getHeader().getAttributes().size() - 1){
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    return newTuples;
}