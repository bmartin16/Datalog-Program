//
// Created by 18bma on 10/21/2021.
//

#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H
#include "iostream"
#include <vector>
using namespace std;

class Tuple {
private:
    vector<string> values;
public:
    Tuple();
    Tuple(vector<string> values);
    bool operator< (const Tuple &other) const {
        return values < other.values;
    }
    vector<string> getValues();
    void addValue(string value);
    string getValue(string value, int index);
};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
