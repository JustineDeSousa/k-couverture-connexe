#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include <vector>
#include <set>

template <class number>
class Graph
{
private:
    vector<set<int>> list_adjacence;
    Network graph_type; //communication or captation network

public:
    Graph(){};
    Graph(Instance<number> & inst, vector<int> & capt, Network n);

    // getters
    const vector<set<int>> & list_adjacence() const {return list_adjacence;}; // return the list adjacence
    Network type() const {return graph_type;};
    const set<int> & neighbours(int i) const { return list_adjacence()[i];}; // return the set of neighbours of terget i
    int degree(int i) const {return neighbours(i).size() ;};

    // network communication
    //int nb_connected components();
    //vector<int>& BFS(int depart, vector<int> visited); // the set of vertices visited by BFS starting from vertex departure
};

/**
 * @brief Construct a new Graph<number>:: Graph object regarding to the given solution
 * 
 * @tparam number type (int / float) for the positions
 * @param inst instance
 * @param sol solution
 */
template<typename number>
Graph<number>::Graph(Instance<number> & inst, vector<int> & capt, Network network) : graph_type(network) {
    int n = capt.size();

    switch (graph_type)
    {
    case captation:
        // we don't consider the captation for the sink
        list_adjacence[0] = set<int>();

        for (int i = 1; i < n; i++) 
        {
            list_adjacence[i] = set<int>();

            for(int j = 1; j< n; j++){
                if(capt[j] == 0) continue;
                
                if(inst.do_capt(i, j)) list_adjacence[i].insert(j);
            }
        }
        break;


    case communication:
        for (int i = 0; i < n; i++) 
        {
            list_adjacence[i] = set<int>();
            if(capt[i] == 0 && i!=0) continue; // we only consider captors and the sink

            for(int j = 0; j< n; j++){
                if( j == i) continue;
                if(capt[j] == 0) continue;
                
                if(inst.do_communicate(i, j)) list_adjacence[i].insert(j);
            }
        }

        break;
    
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }

}

/*
template <typename number>
vector<int>& DFS(int depart, ){

}
*/


/**
 * @brief Fonction externe affichage
 * 
 * @tparam number 
 * @param stream 
 * @param graph 
 * @return ostream& 
 */
template <typename number>
ostream& operator <<(ostream& stream, const Graph<number>& graph){
    switch (graph.type())
    {
    case captation:
        stream << "Graph captation : {" << endl;
        break;
    
    case communication:
        stream << "Graph communication : {" << endl;
        break;
    
    default:
        cerr << "Invalid Network attribute " << endl;
        exit(-1);
        break;
    }
    vector<set<int>> list_adjacence = graph.list_adjacence();
    int n = list_adjacence.size();
    for(int i = 0; i < n; i++){
        stream << i << " : [ ";
        for(int v : list_adjacence[i]){
            stream << v << ", ";
        }
        stream << " ]; ";
    }
    return stream << endl;
    
}


#endif