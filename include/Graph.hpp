#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include "Solution.hpp"
#include <map>

template <class number>
class Graph
{
private:
    map<int, vector<int>> graph; // dictionary

public:
    Graph(Instance<number> & inst, Solution & sol);
    ~Graph();
};

template<typename number>
Graph<number>::Graph(Instance<number> & inst, Solution & sol)
{
    int n = sol.size();
}

#endif