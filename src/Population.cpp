#include "../include/Population.hpp"



/***************************** UPDATES *****************************/
// TODO pop.update_best_solution()
void Population::update(){
    sort();
    Solution best((*this)[0]);
}
/*******************************************************************/
/******************** GENETIC ALGO *********************************/
void Population::selection_roulette( Population& pop, int nb_indiv){
    sort();
    vector<int> fit;
    for( Solution sol : pop){
        fit.push_back( sol.fitness() );
    }
    int sum_fit = accumulate(fit.begin(), fit.end(), 0);
    vector<int> partial_sum_fit;
    partial_sum(fit.begin(), fit.end(), partial_sum_fit.begin());
    int nb_ajout = 0;
    while( nb_ajout < nb_indiv ){
        int tirage = rand()%sum_fit; //int entre 0 et sum_fit
        for(uint i=0; i<size(); i++){
            if( tirage <= partial_sum_fit[i] ){
            pop.push_back((*this)[0]);
            nb_ajout ++;
            break;
            }
        }
    }
}
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
        cerr << "Population::select = " << to_str(select) << "; invalid Seletion attribute " << endl;
        exit(-1);
        break;    
    }
}
/*******************************************************************/
/******************** AFFICHAGE ************************************/

ostream& operator <<(ostream& stream, Population& pop){
    stream << "Population : (" << pop.size() << " individus) [ " << endl;
    for (Solution sol : pop){
        stream << sol;
    }
    stream << " ]" << endl;
    return stream;
}
