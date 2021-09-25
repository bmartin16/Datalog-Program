//
// Created by 18bma on 9/24/2021.
//

#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H
#include "Parameter.h"
#include <vector>
#include <iostream>

class Predicate {
private:
public:
    string predicateName;
    vector<Parameter> parameterList;
    Predicate(string name, vector<Parameter> parameters);

    Predicate();

    void SchemeToString();
    void FactToString();
    void QueryToString();
    void PredicateToString();
};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H
