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
/*********************** EVALUATION DE LA SOLUTION ***********************/
bool Solution::operator<(const Solution& solution){
    return fitness() < solution.fitness();
}
int Solution::nb_connexite() const{
    //A ECRIRE
    return 0;
}
int Solution::nb_couverture(int i) const{
    //A ECRIRE
    return 0;
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
    return nb_capteurs() + nb_connexite() + instance->k()*size() 
    - accumulate(nb_couverture().begin(),nb_couverture().end(),0); 
}
/**************************************************************************/

/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/

void Solution::reverse(int i){
    (*this)[i] = 1-(*this)[i]; 
    cout << "Solution::reverse(int) : IL FAUT METTRE A JOUR LE GRAPHE" << endl;
};
/*
vector<bool> Solution::val_bit_mask(){
    vector<bool> result;
    float x = rand()%instance->Grid_size();
    float y = rand()%instance->Grid_size();
    for(int cible : instance->bit_mask(x,y) ){
        //Valeur de la solution sur la cible
        result.push_back( (*this)[cible] );
    }
}
*/
void Solution::mutation(float mut_rate){
    float p = rand()/RAND_MAX;
    if( p <= mut_rate ){
        int bit_to_reverse = rand() % size();
        reverse(bit_to_reverse);
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