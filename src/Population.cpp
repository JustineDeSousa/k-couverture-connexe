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
    // cout << "Population::selection_roulette : \n";
    sort();
    vector<int> partial_fit_sum;
    int sum_fit = 0;
    for( Solution sol : *this){
        sum_fit += sol.fitness();
        partial_fit_sum.push_back( sum_fit );
    }
    cout << "sum_fit = " << sum_fit << endl;
    int nb_ajout = 0;
    while( nb_ajout < nb_indiv ){
        int tirage = rand()%sum_fit; //int entre 0 et sum_fit
        for(int i=0; i<int(size()); i++){
            if( tirage <= partial_fit_sum[i] ){
                pop.push_back((*this)[i]);
                nb_ajout ++;
                break;
            }
        }
    }
    cout << "*****roulette OK" << endl;
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