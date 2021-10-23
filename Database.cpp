//
// Created by 18bma on 10/21/2021.
//

#include "Database.h"
Database::Database(){}
Relation* Database::findRelation(string name){
    return myDatabase.at(name);
}
map<string, Relation*> Database::getDatabase(){
    return myDatabase;
}
void Database::setDatabase(map<string, Relation*> myMap){
    this->myDatabase = myMap;
}