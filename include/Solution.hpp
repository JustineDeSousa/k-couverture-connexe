#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include "Instance.hpp"
#include "Graph.hpp"

using namespace std;

template <class number>
class Solution
{
private:
    vector<int> captors; // captors[i] = 1 => i is a captor, captors[i] = 0 otherwise 
    Graph<number> graph_capt;
    Graph<number> graph_com;


public:
/**
 * @brief Construct a new Solution object
 * Initially, we consider all targets are placed by captors except the sink
 * 
 * @param size the total number of targets
 */
    Solution(int size = 0){ captors = vector<int>(size, 1); captors[0] = 0;}; 

    int size() const {return captors.size();};
    const vector<int> & get_captors() const {return captors;}

    void update_graph_capt(Instance<number> & inst) {graph_capt = Graph<number>(inst, captors, captation);};
    void update_graph_com(Instance<number> & inst) {graph_capt = Graph<number>(inst, captors, communication);};


    const Graph<number>& get_graph_capt() const {return graph_capt;}
    const Graph<number>& get_graph_com() const {return graph_com;}

    //print
    ostream& short_print(ostream& stream);

    //int fitness();
    //bool k_coverage(Instance instance);
    //bool communication(Instance instance);
    //Solution neighboor(int d);
};
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