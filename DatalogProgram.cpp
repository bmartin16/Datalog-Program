//
// Created by 18bma on 9/24/2021.
//

#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(vector<Predicate> schemeList, vector<Predicate> factList, vector<Predicate> queryList, vector<Rule> ruleList){
    this->schemeList = schemeList;
    this->factList = factList;
    this->queryList = queryList;
    this->ruleList = ruleList;
}
DatalogProgram::DatalogProgram(){}

void DatalogProgram::ToString(){
    cout << "Schemes(" << schemeList.size() << "):" << endl;
    for(unsigned int i = 0; i < schemeList.size(); i++){
        schemeList.at(i).SchemeToString();
        cout << endl;
    }
    cout << "Facts(" << factList.size() << "):" << endl;
    for(unsigned int i = 0; i < factList.size(); i++){
        factList.at(i).FactToString();
        cout << endl;
    }
    cout << "Rules(" << ruleList.size() << "):" << endl;
    for(unsigned int i = 0; i < ruleList.size(); i++){
        ruleList.at(i).RuleToString();
        cout << endl;
    }
    cout << "Queries(" << queryList.size() << "):" << endl;
    for(unsigned int i = 0; i < queryList.size(); i++){
        queryList.at(i).QueryToString();
        cout << endl;
    }
    cout << "Domain(" << domainList.size() << "):" << endl;
    set<string>:: iterator it;
    for(it = domainList.begin(); it!=domainList.end(); it++){
        string domain = *it;
        cout << domain << endl;
    }

}

void DatalogProgram::CreateDomains(){

    for(unsigned int i = 0; i < factList.size(); i++){
        for (unsigned int j = 0; j < factList.at(i).parameterList.size(); j++){
            if(factList.at(i).parameterList.at(j).isString == true){
                domainList.insert(factList.at(i).parameterList.at(j).tokenDescription);
            }
        }
    }
}

vector<string> DatalogProgram::returnPredicateNames(vector<Parameter> parameterList){
    vector<string> stringList;
    for(unsigned int i = 0; i < parameterList.size(); i++){
        stringList.push_back(parameterList.at(i).tokenDescription);
    }
    return stringList;
}