#include "../include/Population.hpp"
#include "../include/Solution.hpp"

//genetic algo

void Population::selection_roulette( Population& pop ){
    assert(pop.size() == 0);
    int sum_fit = 0;
    for( Solution sol : pop){
        sum_fit += sol.fitness();
    }
    for( Solution sol : pop){
        double p = (double)rand() / (double)RAND_MAX ;;
        if( p <= sol.fitness() / sum_fit){
            pop.push_back(sol);
        }
    }
}



void Population::selection_elite( Population& pop, int nb_enf ){
    sort(pop.begin(), pop.end());
    for(int i=0; i<nb_enf; i++){
        pop.push_back((*this)[i]);
    }
}


void Population::selection( Population& pop, int nb_enf){
    switch(select)
    {
    case Selection::ROULETTE:
        selection_roulette(pop);
        break;
    case Selection::ELITE:
        selection_elite(pop, nb_enf);
        break;
    default:
        cerr << "Population::select = " << to_str(select) << "; invalid Type_seletion attribute " << endl;
        exit(-1);
        break;    
    }
}


/**********************************/
/******* fonctions externes *******/
/**********************************/


ostream& operator <<(ostream& stream, Population& pop){
    stream << "Population : (" << pop.size() << " individus) [ " << endl;
    for (Solution sol : pop){
        stream << sol;
    }
    stream << " ]" << endl;
    return stream;
}
