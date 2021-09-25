//
// Created by 18bma on 9/24/2021.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H
#include <string>
using namespace std;

class Parameter {
private:
public:
    string tokenDescription;
    bool isString;
    Parameter(string description, bool isString);
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
