#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h> 
#include <cmath>

#include "Solution.hpp"

using namespace std;

template <typename number>
class Instance
{

private:
    int N; // grid size N * N
    vector< pair<number,number> > targets; // vector of targets' positions
    int R_capt; // radius captation
    int R_com; // radius communication
    int k; // k connectivity
    //float borne_PL; 
    //Solution best_solution; // best solution found by genetic algorithm



public:
/**
 * @brief Construct a new Instance object
 * 
 * @param res vector of targets' positions
 * @param n grid length
 * @param capt radius captation, =1 by defaut
 * @param com radius communication, =1 by defaut
 * @param K connectivity, =1 by defaut
 */
    Instance(vector< pair<number,number> > & res, int n, int capt = 1, int com = 1, int K = 1) 
                : N(n), targets(res), R_capt(capt), R_com(com), k(K) {}

    // getters 
    vector< pair<number,number> > get_targets() const {return targets;}
    int get_R_capt() const {return R_capt;}
    int get_R_com() const {return R_com;}
    int get_k() const {return k;}
    int get_N() const {return N;}

    // return the distance euclidean of two targets i and j
    float dist_euclidean(int i, int j) const {return sqrt(pow(targets[i].first - targets[j].first, 2) +
     pow(targets[i].second - targets[j].second, 2) );}
    
    // return true, if targets i and j can be capted by each other
    bool is_capted(int i, int j) const { return dist_euclidean(i, j) <= R_capt;}

    // return true, if two targets/captors can communicate
    bool is_communicatable(int i, int j) const { return dist_euclidean(i, j) <= R_com;}


};

// fonctions externes

template <typename number>
ostream& operator <<(ostream& stream, const Instance<number>& inst){
    stream << "Instance {"<<endl << "grid size : " << inst.get_N() << "*" << inst.get_N()<<
    "; R_capt=" << inst.get_R_capt() << "; R_com=" << inst.get_R_com() << "; k=" << inst.get_k()<<"; "<<endl;
    
    stream << "list of targets : ["<<endl;
    int i = 0;
    for(pair<number, number> t : inst.get_targets()){
        stream << i << " : " << "(" <<t.first<<", "<<t.second<<")"<<endl;
        i +=1;
    }

      
    return stream <<"]" <<endl;

}

#endif