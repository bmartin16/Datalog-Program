//
// Created by 18bma on 10/21/2021.
//

#include "Header.h"

Header::Header(){}

Header::Header(vector<string> attributes){
    this->attributes = attributes;
}

void Header::addAttribute(string attribute){
    this->attributes.push_back(attribute);
}

void Header::setAttribute(string attribute, int index){
    this->attributes.at(index) = attribute;
}

vector<string> Header::getAttributes(){
    return attributes;
}
