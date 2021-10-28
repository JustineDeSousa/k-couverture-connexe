#include "../include/Population.hpp"


Population::Population( vector<Solution>& solutions, Selection t) : vector<Solution>(solutions), select(t)
{
    sort();
    Solution best( (*this)[0] );
}
/***************************** UPDATES *****************************/
// TODO pop.update_best_solution()
void Population::update(){
    sort();
    Solution best((*this)[0]);
}
/*******************************************************************/
//genetic algo
void Population::selection_roulette( Population& pop, int nb_indiv ){
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
// void Population::selection_roulette( Population& pop, int nb_indiv){
//     vector<int> fit();
//     for( Solution sol : pop){
//         sum_fit += sol.fitness();
//     }
//     int nb_ajout = 0;
//     while( nb_ajout < nb_indiv ){
//         int tirage = rand()%sum_fit; //int entre 0 et sum_fit
//         if( tirage <= (*this)[0].fitness() ){
//             pop.push_back((*this)[0]);
//         }else if( tirage <= ){

//         }
//     }
//     for( Solution sol : pop){
//         double p = (double)rand() / (double)RAND_MAX ;;
//         if( p <= sol.fitness() / sum_fit){
//             pop.push_back(sol);
//         }
//     }
// }



void Population::selection_elite( Population& pop, int nb_indiv ){
    sort();
    for(int i=0; i<nb_indiv; i++){
        pop.push_back((*this)[i]);
    }
}


void Population::selection( Population& pop, int nb_indiv){
    switch(select)
    {
    case Selection::ROULETTE:
        selection_roulette(pop, nb_indiv);
        break;
    case Selection::ELITE:
        selection_elite(pop, nb_indiv);
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
