#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include <vector>
#include <set>
#include <queue>


class Graph
{
private:
    vector<set<int>> list_adjacence;
    Network graph_type; //communication or captation network

public:
    Graph(){};
    Graph(const Instance * const inst, vector<bool> & sol, Network network);

    // getters
    int nb_vertices() const {return list_adjacence.size();}

    Network type() const {return graph_type;};

    set<int> neighbours(int i) const { return list_adjacence[i];} // return the set of neighbours of terget i

    int degree(int i) const {return neighbours(i).size() ;};

    // iterate list adjacency lecture only
    vector<set<int>>::const_iterator begin() const {return list_adjacence.begin(); };
    vector<set<int>>::const_iterator end() const {return list_adjacence.end(); };;

    // network communication
    int nb_connected_components();
    // the set of vertices visited by BFS (a Connected Component) starting from vertex departure
    void BFS(int depart, vector<bool>& visited, vector<int>& cc);

    // update the adjacency for the captor v
    void add_captor(const Instance * const inst, vector<bool> & sol, int v); 
    void supprime_captor(int v);
};


ostream& operator <<(ostream& stream, const Graph& graph);


#endif