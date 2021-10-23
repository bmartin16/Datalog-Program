//
// Created by 18bma on 10/21/2021.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <map>
#include <set>

class Relation {
private:
    string name;
    Header header;
    set<Tuple> rows;
    int queryCounter;
    map<string, int> variableTracker;
    vector<string> variableList;
public:
    Relation();
    Relation(string name, Header header);
    Header getHeader();
    void setHeader(Header header);
    void toString();
    void addTuple(Tuple t);
    void setCounter(int num);
    void setVariableTracker(map<string, int> variableTracker);
    void setVariableList(vector<string> variableList);
    map<string, int> getVariableTracker();
    vector<string> getVariableList();
    int getQueryCounter();
    set<Tuple> getRows();
    Relation* Select(int columnNumber, string rowID);
    Relation* Select2(int columnNumber, map<string, int> variableTracker, string rowID);
    Relation* Project(vector<string> variableList, map<string, int> variableTracker);
    Relation* Rename(Relation *relation, vector<string> variableList, map<string, int> variableTracker);
};


#endif //PROJECT1_STARTER_CODE_RELATION_H
