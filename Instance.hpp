#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Solution.hpp"

enum mode { alea, truncatedGrid };
using namespace std;

class Instance
{
public:
    Instance(): gridSize(0), targets(gridSize), R_capt(1), R_comm(1), k(1) {};
    void lecture_instance( const string instanceName, const mode mod, int gridSize = 0 );
    int grid_size(){return gridSize;};
    vector< pair<float,float> > get_targets(){return targets;};
    int get_R_capt(){return R_capt;};
    int get_R_comm(){return R_comm;}
    int get_k(){return k;};
private:
    int gridSize;
    vector< pair<float,float> > targets;
    int R_capt;
    int R_comm;
    int k;
    float borne_PL;
    Solution best_solution;
};



#endif