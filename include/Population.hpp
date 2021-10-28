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
    Solution best;
    
    friend ostream& operator<<(ostream& stream, Population& pop);

public:
    /*****************************  CONSTRUCTORS *****************************/
    Population(const Instance* const inst, int n=0, Selection t=Selection::ROULETTE) 
                : vector<Solution>(n,Solution(inst)), select(t), best(inst){};
    Population( vector<Solution>& solutions, Selection t=Selection::ROULETTE);
    /*************************************************************************/
    /***************************** GETTERS *****************************/
    Solution best_individual() const { return best; };
    /*******************************************************************/
    /***************************** UPDATES *****************************/
    void update(Solution solution);
    /*******************************************************************/
    /******************* OPERATIONS POUR SELECTION *********************/
    void sort() { std::sort( begin(), end() ); };
    void selection_roulette( Population& pop);
    void selection_elite( Population& pop, int);
    void selection( Population& pop, int nb = 2);
    /********************************************************************/

};


#endif