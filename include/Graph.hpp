#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Instance.hpp"
#include <vector>
#include <set>
#include <queue>

template <class number>
class Graph
{
private:
    vector<set<int>> list_adjacence;
    Network graph_type; //communication or captation network

public:
    Graph(){};
    Graph(Instance<number> & inst, vector<int> & capt, Network network);

    // getters
    int nb_vertices() const {return list_adjacence.size();}
    Network type() const {return graph_type;};
    set<int> neighbours(int i) const { return list_adjacence[i];} // return the set of neighbours of terget i
    int degree(int i) const {return neighbours(i).size() ;};
    vector<set<int>>::const_iterator begin() const {return list_adjacence.begin(); };
    vector<set<int>>::const_iterator end() const {return list_adjacence.end(); };;

    // network communication
    //int nb_connected components();

    // the set of vertices visited by BFS (a Connected Component) starting from vertex departure
    void BFS(int depart, vector<bool>& visited, vector<int>& cc); 
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
        list_adjacence = vector<set<int>>(n, set<int>());

        for (int i = 1; i < n; i++) 
        {

            for(int j = 1; j< n; j++){
                if(capt[j] == 0) continue;
                
                if(inst.do_capt(i, j)) list_adjacence[i].insert(j);
            }
        }
        break;


    case communication:
        list_adjacence = vector<set<int>>(n, set<int>());
        for (int i = 0; i < n; i++) 
        {
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


/**
 * @brief Return a connected component (set of vertices) explored by BFS from the departure
 * 
 * @tparam number 
 * @param depart 
 * @param visited modified after the BFS
 * @return vector<int>& 
 */
template <typename number>
void Graph<number>::BFS(int depart, vector<bool>& visited, vector<int>& cc){
    int n = nb_vertices();
    
    queue<int> myqueue;
    myqueue.push(depart);

    if(visited.size() != n) {visited = vector<bool>(n, false);} 

    while (!myqueue.empty()) // when there exists vertices to visit
    {
        int v = myqueue.front();
        myqueue.pop();

        if(!visited[v]){ // if the first vertex in queue is not visited
            cc.push_back(v);
            visited[v] = true; // visit the vertex v

            // for each neighbour u of v, if u is not visited, add into the queue
            for(int u : neighbours(v)){
                if(!visited[u]) {myqueue.push(u);}
            }

        }
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

    vector<set<int>>::const_iterator it = graph.begin();
    int i = 0;
    for(; it != graph.end(); ++it){
        stream << i++ << " : [ ";
    
        set<int>::const_iterator it_set = it->begin();
        for(; it_set != it->end(); ++it_set){
            stream << *it_set << ", ";
        }
    
        stream << " ]; ";
    }
    return stream << endl;
    
}


#endif