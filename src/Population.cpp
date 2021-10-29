#include "../include/Population.hpp"


Population::Population( vector<Solution>& solutions) {
    this->resize(solutions.size());
    for (int i = 0; i < int(solutions.size()); i++){
        (*this)[i] = solutions[i];
    }   
}

/***************************** UPDATES *****************************/
// TODO pop.update_best_solution()
void Population::update(){
    sort();
    Solution best((*this)[0]);
}
/*******************************************************************/
/******************** FONCTIONS SELECTION *********************************/
void Population::sort(){
    std::sort( begin(), end() ); 
}
void Population::selection_roulette( Population& pop, int nb_indiv){
    sort();
    vector<int> fit;
    for( Solution sol : *this){
        fit.push_back( sol.fitness() );
    }
    int sum_fit = accumulate(fit.begin(), fit.end(), 0);
    
    //TODO partial sum
    vector<int> partial_sum_fit;
    partial_sum(fit.begin(), fit.end(), partial_sum_fit.begin());

    for(uint i=0; i<partial_sum_fit.size(); i++){
        cout << partial_sum_fit[i] << " ";
    }
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
void Population::selection( Population& pop, int nb_indiv, Selection select){
    switch(select)
    {
    case Selection::ROULETTE:
        cout << "*****Selection ROULETTE\n";
        selection_roulette(pop, nb_indiv);
        break;
    case Selection::ELITE:
        cout << "*****Selection ELITE\n";
        selection_elite(pop, nb_indiv);
        break;
    default:
        cerr << "Population::select = invalid Selection attribute : " << to_str(select) << endl;
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
/*******************************************************************/