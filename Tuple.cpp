//
// Created by 18bma on 10/21/2021.
//

#include "Tuple.h"
Tuple::Tuple(){}
Tuple::Tuple(vector<string> values){
    this->values = values;
}
vector<string> const Tuple::getValues() const {
    return values;
}

void Tuple::addValue(string value){
    this->values.push_back(value);
}

string Tuple::getValue(string value, int index){
    return values.at(index);
}
