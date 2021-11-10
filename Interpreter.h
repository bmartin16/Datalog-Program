//
// Created by 18bma on 10/21/2021.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
private:
    DatalogProgram myDatalogProgram;
    Database myDatabase;

public:
    Interpreter();

    Interpreter(DatalogProgram myDatalogProgram);

    Relation* evaluatePredicate(Predicate p);

    bool evaluateRule(Rule r);

    void evaluateRules();

    void evaluateQueries();

};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
