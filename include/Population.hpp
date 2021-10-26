#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Solution.hpp"

enum class Selection{ ROULETTE, ELITE };

class Population : public vector<Solution>
{
private:
    Selection select;
    void selection_roulette( Population& pop);
    void selection_elite( Population& pop);

public:    
    Population(Selection t=Selection::ROULETTE) : select(t){};
    Population( vector<Solution> solutions, Selection t=Selection::ROULETTE): vector<Solution>(solutions), select(t){};
    void selection( Population& pop);
};

// fonction externe
ostream& operator <<(ostream& stream, Population& pop);


#endif