#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

#include "Instance.hpp"

using namespace std;

class Solution{
    private:
    vector<bool> captors;

    public:
    int fitness();
    int nb_captors();
    //bool k_coverage(Instance instance);
    //bool communication(Instance instance);
    Solution neighboor(int d);
};

#endif