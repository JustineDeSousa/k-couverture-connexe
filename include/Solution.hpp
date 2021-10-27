#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include <numeric>
#include "Instance.hpp"
#include "Graph.hpp"

using namespace std;

template <class number>
class Solution
{
private:
    vector<int> captors; // captors[i] = 1 => i is a captor, captors[i] = 0 otherwise 
    Graph<number> Graph_capt;
    Graph<number> Graph_com;
    const Instance<number> * const Inst; //const pointer to const object, neither the ptr nor object are modifiable

public:
/**
 * @brief Construct a new Solution object
 * Initially, we consider all targets are placed by captors except the sink
 * And the two graphes are empty
 * 
 * @param size the total number of targets
 */
    Solution(Instance<number>& inst_, int size = 0) : Inst(&inst_) { captors = vector<int>(size, 1); if(size>0) captors[0] = 0;}; 

    // getters
    int size() const {return captors.size();};
    int nb_captors(){ return accumulate(captors.begin(), captors.end(), 0);};
    const vector<int> & get_captors() const {return captors;}
    Graph<number> get_graph_capt() const {return Graph_capt;}
    Graph<number> get_graph_com() const {return Graph_com;}


    // setters
    // update captors values, graphes are updated if g=true
    void set_captors(vector<int>& captors_, bool g) {captors = captors_; if(g) {update_graphs();} } // replace by another vector
    void reverse_target(int t, bool g) {captors[t] = !captors[t]; if(g) {update_graphs(t);}} // change one target's value
    void update_graphs(int t); // update the neighbourhood of target t
    // initilialize graphes
    void update_graphs() {Graph_capt = Graph<number>(Inst, &captors, captation); 
    Graph_com = Graph<number>(Inst, &captors, communication);};


    //print
    ostream& short_print(ostream& stream);

    // fonctions evluation
    int fitness() {return nb_captors() + constraint_k_capt() + nb_connected_component(); };
    int constraint_k_capt(); // accumulate for each target |k - degree|
    int nb_connected_component() { return Graph_com.nb_connected_components(); }; // return the number of connected component in the communication network 
    bool is_k_coverage() {return constraint_k_capt() == 0 ;};
    //Solution neighboor(int d);
};


template <class number>
void Solution<number>::update_graphs(int t){
    if(captors[t] == 1){ // we add a captor
        Graph_com.add_captor(Inst, &captors, t);
        Graph_capt.add_captor(Inst, &captors, t);
    }else{

    }
}

template <class number>
int Solution<number>::constraint_k_capt(){
    int acc = 0;
    int S = size();

    for (int i = 1; i < S; i++)// we don't consider the k-coverage for the sink
    {   
        int d = get_graph_capt().degree(i);
        if ( d < Inst->get_k()) {acc += Inst->get_k() - d; }
    }
    return acc;
}



template <class number>
ostream& Solution<number>::short_print(ostream& stream){
    stream << "Solution : [ " ;

    for (int i = 0; i < size(); i++){
        stream << get_captors()[i] << ", ";
    }

    stream << " ]" << endl;
    return stream;
}


// fonction externe
template <class number>
ostream& operator <<(ostream& stream, const Solution<number> & sol){
    stream << "Solution : [ " ;

    for (int i = 0; i < sol.size(); i++)
    {
        stream << i << " : " << sol.get_captors()[i] << ";\t";
    }

    stream << " ]" << endl;
    return stream;
}


#endif