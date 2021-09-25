//
// Created by 18bma on 9/24/2021.
//

#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H
#include "Predicate.h"

class Rule {
private:
public:
    Predicate headPredicate;
    vector<Predicate> bodyPredicateList;
    Rule(vector<Predicate> head, Predicate body);
    Rule();
    void RuleToString();
};


#endif //PROJECT1_STARTER_CODE_RULE_H
