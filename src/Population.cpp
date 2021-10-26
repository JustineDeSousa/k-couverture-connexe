#include "Population.hpp"
#include "Solution.hpp"

//genetic algo
/*
void Population::selection_roulette( Population& pop ){
    assert(pop.size() == 0);
    int sum_fit = 0;
    for( Solution sol : pop.solutions()){
        sum_fit += sol.fitness();
    }
    for( Solution sol : pop.solutions()){
        double p = (double)rand() / (double)RAND_MAX ;;
        if( p <= sol.fitness() / sum_fit){
            pop.push_back(sol);
        }
    }
}
*/

/*        
void Population::selecton_elite( Population& pop ){
    //trier les sol selon leur fitness
    for(int i=0; i<nb_enf; i++){
        pop.push_back((*this)[i]);
    }
}
*/

// void Population::selection( Population& pop){
//     switch(select)
//     {
//     case ROULETTE:
//         selection_roulette(pop);
//         break;
//     case ELITE:
//         selection_elite(pop);
//         break;
//     default:
//         cerr << "Population::select = " << select << "; invalid Type_seletion attribute " << endl;
//         exit(-1);
//         break;    
//     }
// }


/**********************************/
/******* fonctions externes *******/
/**********************************/


// ostream& operator <<(ostream& stream, Population& pop){
//     stream << "Population : (" << pop.size() << "individus) [ " ;
//     for (Solution sol : pop){
//         sol.short_print(stream);
//     }
//     stream << " ]" << endl;
//     return stream;
// }
