#include "../include/Population.hpp"

//genetic algo
/*
void Population::selection_roulette( Population& pop ){
    int sum_fit = 0;
    for( Solution sol : pop.solutions()){
        sum_fit += sol.fitness();
    }
    for( Solution sol : pop.solutions()){
        double p = (double)rand() / (double)RAND_MAX ;;
        
    }
}
*/
        
// void Population::selecton_elite( Population& pop ){

// }

// void Population::selection( Population& pop, Selection s ){
    
//     if( s == Selection::Roulette){
//         selection_roulette(pop);    
//     }else{
//         selection_elite(pop);
//     }
// }


/**********************************/
/******* fonctions externes *******/
/**********************************/

/*
ostream& operator <<(ostream& stream, Population& pop){
    stream << "Population : (" << pop.size() << "individus) [ " ;

    for (Solution sol : pop.get_solutions()){
        sol.short_print(stream);
    }

    stream << " ]" << endl;
    return stream;
}
*/