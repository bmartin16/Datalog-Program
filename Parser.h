//
// Created by 18bma on 9/23/2021.
//

#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H

#include "token.h";
#include "DatalogProgram.h"
#include <vector>;
using namespace std;

class Parser {
private:
    vector<Token*> tokenList;
    int currToken;
public:
    Parser(vector<Token*> tokenList);
    ~Parser();
     void findComments();
     void match(TokenType token);
     bool predict(TokenType token);
     DatalogProgram datalogProgram();
     Predicate scheme();
     void schemeList(vector<Predicate> &schemes);
     Predicate fact();
     void factList(vector<Predicate> &facts);
     Rule rule();
     void ruleList(vector<Rule> &rules);
     Predicate query();
     void queryList(vector<Predicate> &queries);
     void idList(vector<Parameter> &ids);
     void stringList(vector<Parameter> &strings);
     Predicate headPredicate();
     Predicate predicate();
     void predicateList(vector<Predicate> &predicates);
     Parameter parameter();
     void parameterList(vector<Parameter> &parameters);
};


#endif //PROJECT1_STARTER_CODE_PARSER_H
