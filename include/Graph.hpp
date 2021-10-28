
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"


class Graph : public vector< set<int> >
{
private:
    Network graph_type; //communication or captation network
    friend ostream& operator <<(ostream& stream, const Graph& graph);

public:
    /**************************************** CONSTRUCTORS ****************************************/
    Graph(){}; // permet d'avoir un objet vraiment vide
    Graph(const Instance * const inst, vector<bool>& sol, Network network);
    /**********************************************************************************************/
    /**************************************** GETTERS *********************************************/
    Network type() const {return graph_type;};
    int degree(int i) const {return (*this)[i].size() ;};
    /**********************************************************************************************/
    /******************************** OPERATIONS DE GRAPHE ****************************************/
    // the set of vertices visited by BFS (a Connected Component) starting from vertex departure
    void BFS(int depart, vector<bool>& visited, vector<int>& cc) const;
    // network communication
    int nb_connected_components() const;
    
    // update the adjacency for the captor v
    void add_captor(const Instance * const inst, vector<bool>& sol, int v); 
    void supprime_captor(int v);
    /**********************************************************************************************/

};



#endif
