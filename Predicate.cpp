//
// Created by 18bma on 9/24/2021.
//

#include "Predicate.h"

Predicate::Predicate(string name, vector<Parameter> parameters){
    predicateName = name;
    parameterList = parameters;
}

Predicate::Predicate() {}

void Predicate::SchemeToString() {
    cout << "  " << predicateName << "(";
    for(unsigned int i = 0; i < parameterList.size(); i++){
        cout << parameterList.at(i).tokenDescription;
        if(i != parameterList.size() - 1){
            cout << ",";
        }
        else{
            cout << ")";
        }
    }
}

void Predicate::FactToString() {
    cout << "  " << predicateName << "(";
    for(unsigned int i = 0; i < parameterList.size(); i++){
        cout << parameterList.at(i).tokenDescription;
        if(i != parameterList.size() - 1){
            cout << ",";
        }
        else{
            cout << ").";
        }
    }
}

void Predicate::QueryToString() {
    cout << "  " << predicateName << "(";
    for(unsigned int i = 0; i < parameterList.size(); i++){
        cout << parameterList.at(i).tokenDescription;
        if(i != parameterList.size() - 1){
            cout << ",";
        }
        else{
            cout << ")?";
        }
    }
}

void Predicate::PredicateToString() {
    cout << predicateName << "(";
    for(unsigned int i = 0; i < parameterList.size(); i++){
        cout << parameterList.at(i).tokenDescription;
        if(i != parameterList.size() - 1){
            cout << ",";
        }
        else{
            cout << ").";
        }
    }
}