#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Solution.hpp"

enum class Selection{ ROULETTE, ELITE };

extern int MAX_VIE;

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
    int best_indic;
    
    friend ostream& operator<<(ostream& stream, Population& pop);

public:
    /*****************************  CONSTRUCTORS *****************************/
    Population(){};
    // n = taille de la population = nbre d'individus
    Population( vector<Solution>& solutions);
    /*************************************************************************/
    /***************************** GETTERS *****************************/
    Solution& best_individual() { update(); return (*this)[best_indic]; }; 
    /*******************************************************************/
    /***************************** UPDATES *****************************/
    // Mise à jour de best
    void update();
    /*******************************************************************/
    /******************* OPERATIONS POUR SELECTION *********************/
    void sort();
    void selection_roulette( Population& pop, int);
    void selection_elite( Population& pop, int);
    void selection( Population& pop, int nb, Selection select);

    void delete_old_sols();
    void generation_older();
    /********************************************************************/

};


#endif