#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include "Solution.hpp"
#include <map>


class Graph
{
private:
    map<int, vector<int>> graph; // dictionary
    
public:
    Graph(/* args */);
    ~Graph();
};

Graph::Graph(/* args */)
{
}

Graph::~Graph()
{
}

#endif