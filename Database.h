//
// Created by 18bma on 10/21/2021.
//

#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H
#include "Relation.h"
#include <map>

class Database {
private:
    map<string, Relation*> myDatabase;
public:
    Database();
    Relation* findRelation(string name);
    map<string, Relation*> getDatabase();
    void setDatabase(map<string, Relation*> myMap);
};


#endif //PROJECT1_STARTER_CODE_DATABASE_H
