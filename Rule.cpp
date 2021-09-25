//
// Created by 18bma on 9/24/2021.
//

#include "Rule.h"

Rule::Rule(vector<Predicate> body, Predicate head) {
    headPredicate = head;
    bodyPredicateList = body;
}
Rule::Rule() {}

void Rule::RuleToString(){
    cout << "  ";
    headPredicate.PredicateToString();
    cout << " :- ";
    for(int i = 0; i < bodyPredicateList.size(); i++){
        bodyPredicateList.at(i).PredicateToString();
    }
}