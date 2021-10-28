#include "../include/Graph.hpp"

/**************************************** CONSTRUCTORS ****************************************/
/**
 * @brief Construct a new Graph<number>:: Graph object regarding to the given solution
 * 
 * @tparam number type (int / float) for the positions
 * @param inst instance
 * @param sol solution
 */

Graph::Graph(const Instance * inst, vector<bool>& sol, Network network) : vector< set<int> >(sol.size()), graph_type(network) {
    switch (graph_type)
    {
    case Network::captation:
        // we don't consider the captation for the sink
        for (int i=1; i<size(); i++) {
            for(int j=1; j< size(); j++){
                if(!sol[j]) continue;
                if(inst->capt_linked(i, j)) (*this)[i].insert(j);
            }
        }
        break;
    case Network::communication:
        for (int i=0; i<size(); i++) {
            if(!sol[i] && i!=0) continue; // we only consider captors and the sink

            for(int j=0; j<size(); j++){
                if( j == i ) continue;
                if( !sol[j] ) continue;
                if(inst->com_linked(i, j)) (*this)[i].insert(j);
            }
        }
        break;
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }
}



Graph& Graph::operator=(const Graph& graph){
    if(this == &graph) return *this;
    
    if(this->size() == 0 ) this->resize(graph.size());
    for (int i = 0; i < graph.size(); i++)
    {
        (*this)[i] = graph[i];
    }
    
    graph_type = graph.type();
    return *this;
}
/**********************************************************************************************/
/******************************** OPERATIONS DE GRAPHE ****************************************/
/**
 * @brief Find a connected component (set of vertices) explored by BFS from the departure
 * 
 * @tparam number 
 * @param depart 
 * @param visited modified after the BFS
 */
void Graph::BFS(int depart, vector<bool>& visited, vector<int>& cc) const{
    queue<int> myqueue;
    myqueue.push(depart);

    if( visited.size()!=size() ) {
        visited = vector<bool>(size(), false);
    } 
    while( !myqueue.empty() ) // when there exists vertices to visit
    {
        int v = myqueue.front();
        myqueue.pop();
        if(!visited[v]){ // if the first vertex in queue is not visited
            cc.push_back(v);
            visited[v] = true; // visit the vertex v

            // for each neighbour u of v, if u is not visited, add into the queue
            for(int u : (*this)[v]){
                if(!visited[u]) {myqueue.push(u);}
            }
        }
    }
}
/**
 * @brief While there exixts vertices non visited, we explore the graph communication by BFS.
 *  the number of calls BFS equals to the number of CC.
 * 
 * @tparam number 
 * @return int the number of connected components in graph communication
 */
 int Graph::nb_connected_components(vector<bool>& cap) const{
    vector<bool> visited(size(), false);

    for(int i=0; i < cap.size(); i++ ){if(!cap[i]) visited[i]=true;}

    set<vector<int>> all_cc;

    for (int i=0; i<size(); i++)
    {
        if(!visited[i]) {
            vector<int> cc;
            BFS(i, visited, cc);
            all_cc.insert(cc);
        }
    }
    for(bool v : visited){
        if(!v){
        cerr << "ERROR: still vertices unexplored ! " << endl;
        exit(-1);
        }
    }
    return all_cc.size();
}

void Graph::add_captor(const Instance * inst, vector<bool>& sol, int v){
    switch (graph_type)
    {
    case Network::captation:
        for (uint i=1; i<size(); i++) // we dont consider the sink
        {
            if(inst->capt_linked(v, i)) {
                // i is covered by captor v
                (*this)[i].insert(v); 
                // if i is also a captor, then v is covered by i as well
                if(sol[i]) (*this)[v].insert(i);
            }
        }
        break;
    case Network::communication:
        for (uint i=0; i<size(); i++) {
            if(!sol[i] && i!=0) continue; // we only consider captors and the sink
            if( v == i) continue; // we don't add edge to itself
            if(inst->com_linked(v, i)) {
                (*this)[i].insert(v);
                (*this)[v].insert(i);
            }
        }
        break;
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }
}


void Graph::supprime_captor(int v){
    switch (graph_type)
    {
    case Network::captation:
        for (int i=0; i<size(); i++) // we dont consider the sink
        {
            (*this)[i].erase(v);
        }
        break;
    case Network::communication:
        for (int i=0; i<size(); i++) // we dont consider the sink
        {   
            if(i == v){
                (*this)[i] = set<int>();
            }else{
                (*this)[i].erase(v);
            }
        }
        break;
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }
}
/**********************************************************************************************/

/**
 * @brief Fonction externe affichage
 * 
 * @tparam number 
 * @param stream 
 * @param graph 
 * @return ostream& 
 */
ostream& operator<<(ostream& stream, const Graph& graph){
    switch (graph.type())
    {
    case Network::captation:
        stream << "Graph captation : {" << endl;
        break;
    
    case Network::communication:
        stream << "Graph communication : {" << endl;
        break;
    
    default:
        cerr << "Invalid Network attribute " << endl;
        exit(-1);
        break;
    }
    int i = 0;
    for(auto sommet : graph){
        stream << i++ << " : [ ";
        for(int voisin : sommet){
            stream << voisin << ", ";
        }
        stream << " ]; ";
    }
    return stream << endl;
}
