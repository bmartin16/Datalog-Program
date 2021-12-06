//
// Created by 18bma on 12/4/2021.
//

#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H
#include "iostream"
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Graph {
private:
    map<int, set<int>> adjacencyList;



public:
    Graph();
    map <int, set<int>> getAdjacencyList();
    void setAdjacencyList(map<int, set<int>>);
    map<int, bool> visited;
    long unsigned int counter = 0;
    map<int, int> postorderList;
    vector<set<int>> stronglyConnectedComponents;
    vector<set<int>> getStronglyConnectedComponents();
    bool done = false;
    int beginNode;

};


#endif //PROJECT1_STARTER_CODE_GRAPH_H
