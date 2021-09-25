//
// Created by 18bma on 9/23/2021.
//

#include "Parser.h"
#include <iostream>

Parser::Parser(vector<Token*> tokenList) {
    this->tokenList = tokenList;
    this->currToken = 0;
}
void Parser::findComments(){
    if(tokenList[currToken]->getTokenType() == TokenType::COMMENT) {
        tokenList.erase(tokenList.begin() + currToken);
        findComments();
    }
}
void Parser::match(TokenType token){
    findComments();
    if(tokenList[currToken]->getTokenType() == token){
        currToken += 1;
    }
    else{
        throw tokenList[currToken];
    }

}
bool Parser::predict(TokenType token){
    findComments();
    if(tokenList[currToken]->getTokenType() == token){
        return true;
    }
    else{
        return false;
    }
}
DatalogProgram Parser::datalogProgram(){
    DatalogProgram *datalogProgram = new DatalogProgram;
    //Schemes
    match(TokenType::SCHEMES);
    //COLON
    match(TokenType::COLON);
    //scheme
    datalogProgram->schemeList.push_back(scheme());
    //schemeList
    schemeList(datalogProgram->schemeList);
    //FACTS
    match(TokenType::FACTS);
    //COLON AFTER FACTS
    match(TokenType::COLON);
    //factList
    factList(datalogProgram->factList);
    //RULES
    match(TokenType::RULES);
    //COLON AFTER RULES
    match(TokenType::COLON);
    //ruleList
    ruleList(datalogProgram->ruleList);
    //QUERIES
    match(TokenType::QUERIES);
    //COLON AFTER QUERIES
    match(TokenType::COLON);
    //query
    datalogProgram->queryList.push_back(query());
    //queryList
    queryList(datalogProgram->queryList);
    //EOF
    match(TokenType::END);
    datalogProgram->CreateDomains();
    return *datalogProgram;
}
 Predicate Parser::scheme(){
    findComments();
    Predicate *scheme = new Predicate;
    if(predict(TokenType::ID) == true){
        //ID
        scheme->predicateName = tokenList.at(currToken)->getDescription();
        match(TokenType::ID);
        //LEFT_PAREN
        match(TokenType::LEFT_PAREN);
        //ID
        Parameter *firstId = new Parameter(tokenList.at(currToken)->getDescription(), false);
        scheme->parameterList.push_back(*firstId);
        match(TokenType::ID);
        //idList
        idList(scheme->parameterList);
        //RIGHT_PAREN
        match(TokenType::RIGHT_PAREN);
        return *scheme;
    }
    else{
        throw tokenList[currToken+1];
    }
}
void Parser::schemeList(vector<Predicate> &schemes){
    findComments();
    if(predict(TokenType::ID) == true){
        //scheme
        schemes.push_back(scheme());
        //schemeList
        schemeList(schemes);
    }
    else if(predict(TokenType::FACTS) == true){
        return;
    }
    else {
        throw tokenList[currToken];
    }
}
Predicate Parser::fact(){
    findComments();
    Predicate *fact = new Predicate;
    if(predict(TokenType::ID) == true){
        //ID
        fact->predicateName = tokenList.at(currToken)->getDescription();
        match(TokenType::ID);
        //LEFT_PAREN
        match(TokenType::LEFT_PAREN);
        //STRING
        Parameter *firstString = new Parameter(tokenList.at(currToken)->getDescription(), true);
        fact->parameterList.push_back(*firstString);
        match(TokenType::STRING);
        //stringList
        stringList(fact->parameterList);
        //RIGHT_PAREN
        match(TokenType::RIGHT_PAREN);
        //PERIOD
        match(TokenType::PERIOD);
        return *fact;
    }
    else{
        throw tokenList[currToken];
    }
}
void Parser::factList(vector<Predicate> &facts){
    findComments();
    if(predict(TokenType::ID) == true){
        //fact
        facts.push_back(fact());
        //factList
        factList(facts);
    }
    else if(predict(TokenType::RULES) == true){
        return;
    }
    else {
        throw tokenList[currToken];
    }
}
Rule Parser::rule(){
    Rule *rule = new Rule;
    findComments();
    if(predict(TokenType::ID) == true){
        //headPredicate
        rule->headPredicate = headPredicate();
        //COLON_DASH
        match(TokenType::COLON_DASH);
        //predicate
        rule->bodyPredicateList.push_back(predicate());
        //predicateList
        predicateList(rule->bodyPredicateList);
        //PERIOD
        match(TokenType::PERIOD);
        return *rule;
    }
    else{
        throw tokenList[currToken+1];
    }
}
void Parser::ruleList(vector<Rule> &rules){
    findComments();
    if(predict(TokenType::ID) == true){
        //rule
        rules.push_back(rule());
        //ruleList
        ruleList(rules);
    }
    else if(predict(TokenType::QUERIES) == true){
        return;
    }
    else {
        throw tokenList[currToken];
    }
}
Predicate Parser::query(){
    Predicate *query = new Predicate;
    findComments();
    if(predict(TokenType::ID) == true){
        //predicate
        *query = predicate();
        //Q_MARK
        match(TokenType::Q_MARK);
        return *query;
    }
    else{
        throw tokenList[currToken+1];
    }
}
void Parser::queryList(vector<Predicate> &queries){
    findComments();
    if(predict(TokenType::ID) == true){
        //query
        queries.push_back(query());
        //queryList
        queryList(queries);
    }
    else if(predict(TokenType::END) == true){
        return;
    }
    else {
        throw tokenList[currToken];
    }
}
void Parser::idList(vector<Parameter> &ids){
    findComments();
    if(predict(TokenType::COMMA) == true){
        //COMMA
        match(TokenType::COMMA);
        //ID
        Parameter *id = new Parameter(tokenList.at(currToken)->getDescription(), false);
        ids.push_back(*id);
        match(TokenType::ID);
        //idList
        idList(ids);
    }
    else if(predict(TokenType::RIGHT_PAREN) == true){
        return;
    }
    else{
        throw tokenList[currToken];
    }
}
void Parser::stringList(vector<Parameter> &strings){
    findComments();
    if(predict(TokenType::COMMA) == true){
        //COMMA
        match(TokenType::COMMA);
        //STRING
        Parameter *string = new Parameter(tokenList.at(currToken)->getDescription(), true);
        strings.push_back(*string);
        match(TokenType::STRING);
        //stringList
        stringList(strings);
    }
    else if(predict(TokenType::RIGHT_PAREN) == true){
        return;
    }
    else{
        throw tokenList[currToken];
    }
}
Predicate Parser::headPredicate(){
    findComments();
    Predicate *headPredicate = new Predicate;
    if(predict(TokenType::ID) == true){
        //ID
        headPredicate->predicateName = tokenList.at(currToken)->getDescription();
        match(TokenType::ID);
        //LEFT_PAREN
        match(TokenType::LEFT_PAREN);
        //ID
        Parameter *firstId = new Parameter(tokenList.at(currToken)->getDescription(), false);
        headPredicate->parameterList.push_back(*firstId);
        match(TokenType::ID);
        //idList
        idList(headPredicate->parameterList);
        //RIGHT_PAREN
        match(TokenType::RIGHT_PAREN);
        return *headPredicate;
    }
    else{
        throw tokenList[currToken+1];
    }
}
Predicate Parser::predicate(){
    findComments();
    Predicate *predicate = new Predicate;
    if(predict(TokenType::ID) == true){
        //ID
        predicate->predicateName = tokenList.at(currToken)->getDescription();
        match(TokenType::ID);
        //LEFT_PAREN
        match(TokenType::LEFT_PAREN);
        //parameter
        predicate->parameterList.push_back(parameter());
        //parameterList
        parameterList(predicate->parameterList);
        //RIGHT_PAREN
        match(TokenType::RIGHT_PAREN);
        return *predicate;
    }
    else{
        throw tokenList[currToken+1];
    }
}
void Parser::predicateList(vector<Predicate> &predicates){
    findComments();
    if(predict(TokenType::COMMA) == true){
        //COMMA
        match(TokenType::COMMA);
        //predicate
        predicates.push_back(predicate());
        //predicateList
        predicateList(predicates);
    }
    else if(predict(TokenType::PERIOD) == true){
        return;
    }
    else{
        throw tokenList[currToken];
    }
}
Parameter Parser::parameter(){
    findComments();
    if(predict(TokenType::STRING) == true){
        //STRING
        Parameter parameter(tokenList.at(currToken)->getDescription(), true);
        match(TokenType::STRING);
        return parameter;
    }
    else if(predict(TokenType::ID) == true) {
        //ID
        Parameter parameter(tokenList.at(currToken)->getDescription(), false);
        match(TokenType::ID);
        return parameter;
    }
    else{
        throw tokenList[currToken+1];
    }
}
void Parser::parameterList(vector<Parameter> &parameters){
    findComments();
    if(predict(TokenType::COMMA) == true){
        //COMMA
        match(TokenType::COMMA);
        //parameter
        parameters.push_back(parameter());
        //parameterList
        parameterList(parameters);
    }
    else if(predict(TokenType::RIGHT_PAREN) == true){
        return;
    }
    else{
        throw tokenList[currToken];
    }
}