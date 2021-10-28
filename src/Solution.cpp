#include "../include/Solution.hpp"

/**************************************** CONSTRUCTORS ****************************************/
Solution::Solution(const Solution& solution, bool G) : vector<bool>(solution)
{
    if(G){
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
    }
}
Solution& Solution::operator=(const Solution& solution){
    if(this == &solution) return *this;
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
    return *this;
}
/**********************************************************************************************/
/******************************** OPERATIONS DE GRAPHE ****************************************/
void Solution::update_graphs(int t){
    if((*this)[t]){ // we add a captor
        graph_com.add_captor(instance, *this, t);
        graph_capt.add_captor(instance, *this, t);
    }else{
        graph_capt.supprime_captor(t);
        graph_com.supprime_captor(t);
    }
}
void Solution::update_graphs(){
    graph_capt = Graph(instance, *this, Network::captation); 
    graph_com = Graph(instance, *this, communication);
}
/**********************************************************************************************/
/*********************** EVALUATION DE LA SOLUTION ***********************/
bool Solution::operator<(const Solution& solution) const{
    return fitness() < solution.fitness();
}
int Solution::captation(int i) const{
    return graph_capt[i].size();
}
vector<int> Solution::captation() const{
    vector<int> result;
    for(uint i=0; i<size(); i++){
        result.push_back(captation(i));
    }
    return result;
}
/**
 * @brief Return the total number of missed captors for each targets
 * 
 * @return int 
 */
int Solution::nb_captation_missed() const{
    int missed = 0;
    for (int i=1; i<size(); i++)// we don't consider the k-coverage for the sink
    {
        if(graph_capt.degree(i) < instance->k()){
            missed += instance->k() - graph_capt.degree(i);
        }
    }
    return missed;
}
bool Solution::is_k_covered() const{
    for (int i = 1; i < size(); i++){
        if(graph_capt.degree(i) < instance->k()) return false;
    }
    return true;
}
int Solution::fitness() const{ 
    return nb_capteurs() + nb_connected_component()-1 + nb_captation_missed(); 
}
/**************************************************************************/
/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
/**
 * @brief if G=true, we update also the vertex i in two graphs
 * 
 * @param i = cibles à changer
 * @param G = true si on va faire une selection
 */
void Solution::reverse(int i, bool G){
    (*this)[i] = !(*this)[i]; 
    if(G) update_graphs(i);
};
void Solution::mutation(float mut_rate){
    float p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // between 0.0 and 1.0
    if( p <= mut_rate ){
        int min_ = 0; int max_=size()-1;
        int bit_to_reverse =  rand()%(max_-min_ + 1) + min_; // a position between 0 and size()-1
        reverse(bit_to_reverse, false);
    }
}
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2){
    vector<int> bits_to_cross;
    P1.bit_mask(bits_to_cross);

    for (int bit : bits_to_cross)
    {
        E1[bit] = P2[bit];
        E2[bit] = P1[bit];
    }
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
