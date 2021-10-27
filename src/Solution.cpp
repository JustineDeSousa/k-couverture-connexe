#include "../include/Solution.hpp"

void Solution::update_graphs(int t){
    if((*this)[t]){ // we add a captor
        Graph_com.add_captor(instance, (*this), t);
        Graph_capt.add_captor(instance, (*this), t);
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
    //TODO

    return make_pair(E1,E2);
}
/**************************************************************************/


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
/**************************************************************************/





void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2){
    
}