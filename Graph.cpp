//
// Created by 18bma on 12/4/2021.
//

#include "Graph.h"
Graph::Graph(){}

map <int, set<int>> Graph::getAdjacencyList(){
    return adjacencyList;
}

void Graph::setAdjacencyList(map<int, set<int>> adjacencyList){
    this->adjacencyList = adjacencyList;
}

vector<set<int>> Graph::getStronglyConnectedComponents(){
    return this->stronglyConnectedComponents;
}