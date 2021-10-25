#include "Population.hpp"

//genetic algo

void Population::selection_roulette( Population& pop ){
    for( Solution sol : pop){
        
    }
}
        
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

ostream& operator <<(ostream& stream, Population& pop){
    stream << "Population : (" << pop.size() << "individus) [ " ;

    for (Solution sol : pop){
        sol.short_print(stream);
    }

    stream << " ]" << endl;
    return stream;
}