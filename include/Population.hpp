#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Solution.hpp"

enum class Selection{ ROULETTE, ELITE };

static const string to_str (const Selection s){
    switch (s) 
    {
    case Selection::ROULETTE:
        return "ROULETTE";
    case Selection::ELITE:
       return "ELITE";
    default:
        assert(false);
        break;
    }
    return "";
}


class Population : public vector<Solution>
{
private:
    Selection select;
    void selection_roulette( Population& pop);
    void selection_elite( Population& pop, int);

    friend ostream& operator<<(ostream& stream, Population& pop);

public:
    Population(const Instance* const inst, int n=0, Selection t=Selection::ROULETTE) 
                : vector<Solution>(n,Solution()), select(t){};
    Population( vector<Solution> solutions, Selection t=Selection::ROULETTE): 
                vector<Solution>(solutions), select(t){};

    /******************* OPERATIONS POUR SELECTION *******************/
    void selection( Population& pop, int nb = 2);
    /******************************************************************/

};

// fonction externe
ostream& operator<<(ostream& stream, Population& pop);


#endif