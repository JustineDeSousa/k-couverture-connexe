#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Solution.hpp"

using namespace std;

class Instance
{

private:
    int N; // grid size N * N
    vector< pair<float,float> > targets; // vector of targets' positions
    int R_capt; // radius captation
    int R_com; // radius communication
    int k; // k connectivity
    //float borne_PL; 
    Solution best_solution; // best solution found by genetic algorithm



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
    Instance(vector< pair<float,float> > & res, int n, int capt = 1, int com = 1, 
    int K = 1) : N(n), targets(res), R_capt(capt), R_com(com), k(K) {}

    /*
    pair<int,int> jl;
    for( int j=0; j<grid_size; j++ ){
        for(int l=0; l<grid_size; l++){
            jl = make_pair( j,l );
            for( auto elmt : to_be_deleted ){
                if( elmt != jl ){
                    res.push_back( jl );        
                }
            }
        }
    }
    */

    // getters 
    vector< pair<float,float> > get_targets() const {return targets;}
    int get_R_capt() const {return R_capt;}
    int get_R_com() const {return R_com;}
    int get_k() const {return k;}
    int get_N() const {return N;}


};

// fonctions externes
ostream& operator <<(ostream& stream, const Instance& inst);




#endif