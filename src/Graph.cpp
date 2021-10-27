#include "../include/Graph.hpp"

/**
 * @brief Construct a new Graph<number>:: Graph object regarding to the given solution
 * 
 * @tparam number type (int / float) for the positions
 * @param inst instance
 * @param sol solution
 */

Graph::Graph(const Instance * const inst, vector<bool> & sol, Network network) : graph_type(network) {
    int n = sol.size();

    switch (graph_type)
    {
    case captation:
        // we don't consider the captation for the sink
        list_adjacence = vector<set<int>>(n, set<int>());

        for (int i = 1; i < n; i++) 
        {

            for(int j = 1; j< n; j++){
                if(!sol[j]) continue;
                
                if(inst->capt_linked(i, j)) list_adjacence[i].insert(j);
            }
        }
        break;


    case communication:
        list_adjacence = vector<set<int>>(n, set<int>());
        for (int i = 0; i < n; i++) 
        {
            if(!sol[i] && i!=0) continue; // we only consider captors and the sink

            for(int j = 0; j< n; j++){
                if( j == i) continue;
                if(!sol[j] ) continue;
                
                if(inst->com_linked(i, j)) list_adjacence[i].insert(j);
            }
        }
        break;
    
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }

}


void Graph::add_captor(const Instance * const inst, vector<bool> & sol, int v){
    int n = nb_vertices();

    switch (graph_type)
    {
    case captation:
        for (int i = 1; i < n; i++) // we dont consider the sink
        {
            if(inst->capt_linked(v, i)) {
                // i is covered by captor v
                list_adjacence[i].insert(v); 
                // if i is also a captor, then v is covered by i as well
                if(sol[i]) list_adjacence[v].insert(i);
            }
        }
        break;


    case communication:
        for (int i = 0; i < n; i++) 
        {
            if(!sol[i] && i!=0) continue; // we only consider captors and the sink

            if( v == i) continue; // we don't add edge to itself
            
            if(inst->com_linked(v, i)) {
                list_adjacence[i].insert(v);
                list_adjacence[v].insert(i);
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
    int n = nb_vertices();

    switch (graph_type)
    {
    case captation:
        for (int i = 0; i < n; i++) // we dont consider the sink
        {
            list_adjacence[i].erase(v);
        }
        break;


    case communication:
        for (int i = 0; i < n; i++) // we dont consider the sink
        {   
            if(i == v){
                list_adjacence[i] = set<int>();
            }else{list_adjacence[i].erase(v);}
        }

        break;
    
    default:
        cerr << "Invalid argument Network" << endl;
        exit(-1);
        break;
    }



}




/**
 * @brief Find a connected component (set of vertices) explored by BFS from the departure
 * 
 * @tparam number 
 * @param depart 
 * @param visited modified after the BFS
 */
void Graph::BFS(int depart, vector<bool>& visited, vector<int>& cc){
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
 * @brief While there exixts vertices non visited, we explore the graph communication by BFS.
 *  the number of calls BFS equals to the number of CC.
 * 
 * @tparam number 
 * @return int the number of connected components in graph communication
 */
 int Graph::nb_connected_components(){
    int n = nb_vertices();
    vector<bool> visited(n, false);
    set<vector<int>> all_cc;

    for (int i = 0; i < n; i++)
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





/**
 * @brief Fonction externe affichage
 * 
 * @tparam number 
 * @param stream 
 * @param graph 
 * @return ostream& 
 */
ostream& operator <<(ostream& stream, const Graph& graph){
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
