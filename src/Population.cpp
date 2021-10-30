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
    best_indic =0;
}
/*******************************************************************/
/******************** FONCTIONS SELECTION *********************************/
void Population::sort(){
    cout << "Population::sort()\n";
    std::sort( begin(), end() ); 
}
void Population::selection_roulette( Population& pop, int nb_indiv){
    vector<int> partial_fit_sum;
    int sum_fit = 0;
    for( Solution sol : *this){
        sum_fit += sol.fitness();
        partial_fit_sum.push_back( sum_fit );
    }
    set<vector<bool>> vec;
    vector<int> indic = {best_indic};

    while( indic.size() < nb_indiv ){
        int tirage = rand()%sum_fit; //int entre 0 et sum_fit

        for(int i=0; i<int(size()); i++){
            if( tirage <= partial_fit_sum[i] ){
                int t = vec.size();
                vec.insert(vec.end(), (*this)[i]); // éviter doublons
                
                if( t != vec.size()) indic.push_back(i); // sert à utiliset constructor par copie
                break;
            }
        }
    }


    for(int i = 1; i < indic.size(); i++){
        pop.push_back((*this)[i]); // constructor by copy, vie also copied !!!
    }

}
void Population::selection_elite( Population& pop, int nb_indiv ){
    for(int i=1; i<nb_indiv; i++){
        pop.push_back((*this)[i]);
    }
}


void Population::selection( Population& pop, int nb_indiv, Selection select){
    sort();
    pop.push_back((*this)[best_indic]);

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
    cout << "*************************\n";
}


void Population::delete_old_sols(){
    update();
    (*this)[best_indic].reset_vie(); // vie = 0

    vector<Solution>::iterator it = begin();
    int i=0;

    for (; it != end(); it++)
    {
        if ((*it).get_vie() >= MAX_VIE)
        {   
            this->erase(it);
            it--;
        }
        
    }
}


void Population::generation_older(){

    for (int i = 0; i < size(); i++)
    {
    (*this)[i].older();
    }

    (*this)[best_indic].reset_vie();
     
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