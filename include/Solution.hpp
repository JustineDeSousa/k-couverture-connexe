#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include "Instance.hpp"

using namespace std;


class Solution
{
private:
    vector<int> captors; // captors[i] = 1 => i is a captor, captors[i] = 0 otherwise 


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

    //print
    ostream& short_print(ostream& stream);

    //int fitness();
    //bool k_coverage(Instance instance);
    //bool communication(Instance instance);
    //Solution neighboor(int d);
};

// fonction externe
ostream& operator <<(ostream& stream, const Solution & sol);


#endif