#include "Solution.hpp"

/**********************************/
/******* fonctions membres *******/
/**********************************/
Solution::Solution(const Solution& solution) : vector<bool>(solution), instance(solution.instance)
{
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
}
Solution& Solution::operator=(const Solution& solution){
    if(this == &solution) return *this;
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
    return *this;
}
void Solution::update_graphs() {
    graph_capt = Graph(*this, Network::captation); 
    graph_com = Graph(*this, Network::communication);
}
/*********************** EVALUATION DE LA SOLUTION ***********************/
bool Solution::operator<(const Solution& solution) const{
    return fitness() < solution.fitness();
}
int Solution::captation(int i) const{
    return graph_capt[i].size();
}



int Solution::k_capted() const{
    int acc = 0;

    for (int i=1; i<instance->size(); i++)// we don't consider the k-coverage for the sink
    {   
        int degree = graph_capt[i].size();
        if ( degree < instance->k() ) {
            acc += instance->k() - degree;
        }
    }
    return acc;
}
vector<int> Solution::nb_couverture() const{
    vector<int> result;
    for(uint i=0; i<size(); i++){
        result.push_back(nb_couverture(i));
    }
    return result;
}

bool Solution::is_k_covered() const{
    for(int elmt : nb_couverture()){
        if( elmt < instance->k() ) return false;
    }
    return true;
}
int Solution::fitness() const{ 
    return nb_capteurs() + nb_connected_component() + instance->k()*size() 
    - accumulate(nb_couverture().begin(),nb_couverture().end(),0); 
}
void Solution::update_graphs(int t){
    if((*this)[t]){ // we add a captor
        graph_com.add_captor(instance, (*this), t);
        graph_capt.add_captor(instance, (*this), t);
    }else{
        Graph_capt.supprime_captor(t);
        Graph_com.supprime_captor(t);
    }
}


/**************************************************************************/

/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/


/**
 * @brief if G=true, we update also the vertex i in two graphs
 * 
 * @param i 
 * @param G 
 */
void Solution::reverse(int i, bool G){
    (*this)[i] = !(*this)[i]; 
    if(G) update_graphs(i);
};


void Solution::mutation(float mut_rate){
    float p = rand()/RAND_MAX;
    if( p <= mut_rate ){
        int bit_to_reverse = rand() % size();
        reverse(bit_to_reverse, false);
    }
}


/**************************************************************************/

/**********************************/
/******* fonctions externes *******/
/**********************************/

/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
pair<Solution,Solution> cross_over(Solution P1, Solution P2){
    Solution E1(P1);
    Solution E2(P2);
<<<<<<< HEAD
    
=======
    //TODO
>>>>>>> main

    return make_pair(E1,E2);
}
/**************************************************************************/

<<<<<<< HEAD
=======

>>>>>>> main
/******************************** AFFICHAGE *******************************/
ostream& operator<<(ostream& stream, const Solution& solution){
    stream << "Solution (taille " << solution.size() << ")" << endl;
    stream << "{" << endl;
    for(uint i=0; i<solution.size(); i++){
        stream << solution[i] << "\t";
        if( i%solution.instance->Grid_size()-1 == 0) stream << endl;
    }
    return stream << "}" << endl;
}
<<<<<<< HEAD
/**************************************************************************/
=======
/**************************************************************************/





void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2){
    
}
>>>>>>> main
