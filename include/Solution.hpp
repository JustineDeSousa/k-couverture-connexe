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
    Instance<number> Inst;

public:
/**
 * @brief Construct a new Solution object
 * Initially, we consider all targets are placed by captors except the sink
 * 
 * @param size the total number of targets
 */
    Solution(Instance<number> & inst_, int size = 0) : Inst(inst_) { captors = vector<int>(size, 1); captors[0] = 0;}; 

    // getters
    int size() const {return captors.size();};
    int nb_captors(){ return accumulate(captors.begin(), captors.end(), 0);};
    const vector<int> & get_captors() const {return captors;}
    const Graph<number>& get_graph_capt() const {return Graph_capt;}
    const Graph<number>& get_graph_com() const {return Graph_com;}


    // setters
    void set_captors(vector<int>& captors_) {captors = captors_;} // replace by another vector
    void reverse_target(int t) {captors[t] = !captors[t];} // change one target's value

    // metter à jour
    void update_graph_capt() {Graph_capt = Graph<number>(Inst, captors, captation);};
    void update_graph_com() {Graph_com = Graph<number>(Inst, captors, communication);};


    //print
    ostream& short_print(ostream& stream);

    // fonctions evluation
    int fitness() {return nb_captors() + constraint_k_capt() ; };
    int constraint_k_capt(); // accumulate for each target |k - degree|
    int nb_connected_component(); // return the number of connected component in the communication network 
    bool is_k_coverage() {return constraint_k_capt() == 0 ;};
    //bool communication(Instance instance);
    //Solution neighboor(int d);
};


template <class number>
int Solution<number>::constraint_k_capt(){
    int acc = 0;
    int S = size();

    for (int i = 1; i < S; i++)// we don't consider the k-coverage for the sink
    {   
        int d = get_graph_capt().degree(i);
        if ( d < Inst.get_k()) {acc += Inst.get_k() - d; }
    }
    return acc;
}

template <class number>
int Solution<number>::nb_connected_component(){
    int cc = 0;

    return cc;
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