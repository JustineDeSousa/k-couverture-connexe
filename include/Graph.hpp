#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include <map>
#include <set>

template <class number>
class Graph
{
private:
    map<int, set<int>> graph; // dictionary: {sommet, {sommets adjacents} }
    Network graph_type; //communication or captation

public:
    Graph(){};
    Graph(Instance<number> & inst, vector<int> & capt, Network n);

    const map<int, set<int>> & get_graph() const {return graph;};
    Network type() const {return graph_type;};
    const set<int> & get_neighbours(int i) const;
    int degree(int i) const {return get_neighbours(i).size() ;};
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
        for (int i = 1; i < n; i++) 
        {
            graph[i] = set<int>();

            for(int j = 1; j< n; j++){
                if(j==i) continue;
                if(capt[j] == 0) continue;
                
                if(inst.is_capted(i, j)) graph[i].insert(j);
            }
        }
        break;


    case communication:
        for (int i = 0; i < n; i++) 
        {
            graph[i] = set<int>();
            if(capt[i] == 0 && i!=0) continue;

            for(int j = 0; j< n; j++){
                if( j == i) continue;
                if(capt[j] == 0) continue;
                
                if(inst.is_communicatable(i, j)) graph[i].insert(j);
            }
        }

        break;
    
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }

}


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

    for(auto item: graph.get_graph()){
        stream << item.first << " : [ ";
        for(auto v : item.second){
            stream << v << ", ";
        }
        stream << " ]; ";
    }
    return stream;
    
}


template <typename number>
const set<int>& Graph<number>::get_neighbours(int i) const{
    auto search = graph.find(i);
    if (search != graph.end()) {
        return search->second;
    } else {
        cerr << "Invalid argument  get_neighbours(int i)" << endl;
        exit(-1);
    }
}

#endif