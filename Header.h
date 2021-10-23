//
// Created by 18bma on 10/21/2021.
//

#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H
#include "iostream"
#include <vector>
using namespace std;

class Header {
private:
    vector<string> attributes;

public:
    Header();
    Header(vector<string> attributes);
    void addAttribute(string attribute);
    void setAttribute(string attribute, int index);
    vector<string> getAttributes();

};


#endif //PROJECT1_STARTER_CODE_HEADER_H
