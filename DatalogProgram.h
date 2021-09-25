//
// Created by 18bma on 9/24/2021.
//

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#include"Rule.h"
#include <set>

class DatalogProgram {
private:
public:
    vector<Predicate> schemeList;
    vector<Predicate> factList;
    vector<Predicate> queryList;
    vector<Rule> ruleList;
    set<string> domainList;
    DatalogProgram(vector<Predicate> schemeList, vector<Predicate> factList, vector<Predicate> queryList, vector<Rule> ruleList);
    DatalogProgram();
    void ToString();
    void CreateDomains();
};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
