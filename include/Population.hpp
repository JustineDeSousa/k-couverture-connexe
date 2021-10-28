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
    Population(){};
    // n = taille de la population = nbre d'individus
    Population( vector<Solution>& solutions, Selection t) 
                : vector<Solution>(solutions), select(t){};
    /*************************************************************************/
    /***************************** GETTERS *****************************/
    Solution best_individual() { update(); return best; };
    /*******************************************************************/
    /***************************** UPDATES *****************************/
    // Mise à jour de best
    void update();
    /*******************************************************************/
    /******************* OPERATIONS POUR SELECTION *********************/
    void sort() { std::sort( begin(), end() ); };
    void selection_roulette( Population& pop, int);
    void selection_elite( Population& pop, int);
    void selection( Population& pop, int nb = 2);
    /********************************************************************/

};


#endif