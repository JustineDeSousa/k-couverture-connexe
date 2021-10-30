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
    //cout << "Population::sort()\n";
    std::sort( begin(), end() ); 
}


void Population::selection_roulette( Population& pop, int nb_indiv){
    vector<int> partial_fit_sum;
    int sum_fit = 0;
    for( Solution sol : *this){
        sum_fit += sol.fitness();
        partial_fit_sum.push_back( sum_fit );
    }

    set<vector<bool>> vec={(*this)[best_indic]};
    vector<bool> indic(size(), false);
    indic[best_indic] = true;
    int parcours = 0;
    int counter = 1;

    do
    {
        parcours++; 
        
        //int tirage = rand()%sum_fit; //int entre 0 et sum_fit
        // best fit <= tirage <= sum_fit
        int tirage = rand()%(sum_fit-(*this)[best_indic].fitness() + 1) + (*this)[best_indic].fitness();

        for(int i=0; i<int(size()); i++){
            if( tirage <= partial_fit_sum[i] ){
                int t = vec.size();
                vec.insert(vec.end(), (*this)[i]); // éviter doublons
                
                if( t != vec.size()) {
                    indic[i] = true; // sert à utiliset constructor par copie
                    pop.push_back((*this)[i]); 
                    counter++;
                }
                break;
            }

        }

        if(parcours == this->size()) {break;}  // éviter rester dans loop
    } while ( counter < nb_indiv);


    // push distinct sol
    for (int i = 1; i < size(); i++)
    {   
        if(counter == nb_indiv){ break;}

        if( !indic[i]){ // i not added

            int t = vec.size();
            vec.insert(vec.end(), (*this)[i]);
            if( t != vec.size()) { // find distinc
                indic[i] = true;
                pop.push_back((*this)[i]); 
                counter++;
            }
        }

    }
    
    // if pop still is not full, add randomly
    if(counter < nb_indiv) {
        int nb_missed = (nb_indiv - counter);

        for(int i=0; i <  nb_missed; i++){
            int r = rand()%(this->size()); // a position between 0 and size()-1
            pop.push_back((*this)[r]);
            counter++;
        }
    }
    cout << "out roulette" << endl;
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