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
    Network graph_type;

public:
    Graph(Instance<number> & inst, Solution & sol, Network n);

    const map<int, vector<int>> & get_graph() const {return graph;}
    Network type() const {return graph_type;}
};

/**
 * @brief Construct a new Graph<number>:: Graph object regarding to the given solution
 * 
 * @tparam number type (int / float) for the positions
 * @param inst instance
 * @param sol solution
 */
template<typename number>
Graph<number>::Graph(Instance<number> & inst, Solution & sol, Network network) : graph_type(network) {
    int n = sol.size();

    switch (graph_type)
    {
    case captation:
        graph[0] = vector<int>(); // we don't consider the captation for the sink

        for (int i = 1; i < n; i++) 
        {
            graph[i] = vector<int>();

            for(int capt : sol.get_captors()){
                if(capt == 0) continue;
                
                if(inst.is_capted(i, capt)) graph[i].push_back(capt);
            }
        }
        break;


    case communication:
        for (int i = 0; i < n; i++) 
        {
            graph[i] = vector<int>();

            for(int capt : sol.get_captors()){
                if(capt == 0) continue;
                
                if(inst.is_communicatable(i, capt)) graph[i].push_back(capt);
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

#endif