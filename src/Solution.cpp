#include "../include/Solution.hpp"

/**************************************** CONSTRUCTORS *****************************/
Solution::Solution(const Solution& solution, bool G) : vector<bool>(solution.size())
{   
    this->resize(solution.size());
    for (int i = 0; i < int(solution.size()); i++)
    {
        (*this)[i] = solution[i];
    }
    if(G){
    graph_capt = Graph(solution.graph_capt);
    graph_com = Graph(solution.graph_com);
    }
}
Solution& Solution::operator=(const Solution& solution){
    if(this == &solution) return *this;
    if(this->size() != solution.size() ) this->resize(solution.size());//  *this=vector<bool>(solution.size())
    for (int i = 0; i < int(solution.size()); i++)
    {
        (*this)[i] = solution[i];
    }
    this->graph_capt = Graph(solution.get_graph_capt());
    this->graph_com = Graph(solution.get_graph_com());
    return *this;
}
/********************************************************************************/
/******************************** OPERATIONS DE GRAPHE *******************/
void Solution::update_graphs(int t){
    if((*this)[t]){ // we add a captor
        graph_com.add_captor(Solution::instance, *this, t);
        graph_capt.add_captor(Solution::instance, *this, t);
    }else{
        graph_capt.supprime_captor(t);
        graph_com.supprime_captor(t);
    }
}
void Solution::update_graphs(){
    graph_capt = Graph(Solution::instance, *this, Network::captation);
    graph_com = Graph(Solution::instance, *this, Network::communication);
}
/*************************************************************************/
/*********************** EVALUATION DE LA SOLUTION ***********************/
bool Solution::operator<(const Solution& solution) const{
    return this->fitness() < solution.fitness();
}
bool Solution::operator<=(const Solution& solution) const{
    return fitness() <= solution.fitness();
}
int Solution::nb_capteurs() const{ 
    int acc = accumulate((*this).begin(),(*this).end(),0);
    // cout << "Solution::nb_capteurs() = " << acc << endl;
    return acc;
}
int Solution::nb_connected_component() const {
    //cout << "Solution::nb_connected_component() = ";
    vector<bool> v = (*this);
    int nb_cc=0;
    if( v == vector<bool>(size(), false) ){ // Si sol=(0,0,0,0,0), on pénalise la fct fitness
        nb_cc = size();
    }else{
        nb_cc = graph_com.nb_connected_components(v);
    }
    // cout << nb_cc << endl;
    return nb_cc;
}
/**
 * @brief Return the total number of missed captors for each targets
 * 
 * @return int 
 */
int Solution::nb_captation_missed() const{
    int missed = 0;
    // cout << "Solution::nb_captation_missed() = ";
    for (int i=1; i<int(size()); i++)// we don't consider the k-coverage for the sink
    {
        if(graph_capt.degree(i) < Solution::instance->k()){
            missed += Solution::instance->k() - graph_capt.degree(i);
        }
    }
    // cout << missed << endl;
    return missed;
}
/**
 * @brief Return true if every target is covered by at least K captors
 * 
 * @return true 
 * @return false 
 */
bool Solution::is_k_covered() const{
    for (uint i = 1; i < size(); i++){

        if(graph_capt.degree(i) < Solution::instance->k()) return false;
    }

    return true;
}
/**
 * @brief Return the fitness value
 * 
 * @return int 
 */
int Solution::fitness() const{
    return nb_capteurs() + nb_connected_component()-1 + nb_captation_missed();
}
/**************************************************************************/
/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
void swap(Solution& sol1, Solution& sol2){
    Solution sol3(sol1, false);
    for(int i = 0; i < int(sol3.size()); i++){
        sol1[i] = sol2[i];
        sol2[i] = sol3[i];
    }
    sol1.update_graphs();
    sol2.update_graphs();
}
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
        reverse(bit_to_reverse, true);
    }
}
void Solution::bit_mask(vector<int>& result) const{
    // a random float between 0.0 and grid_size
    float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ Solution::instance->Grid_size()));
    float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ Solution::instance->Grid_size()));
    Solution::instance->bit_mask(x, y, result);
}
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2){
    cout << "  do cross-over  ";
    vector<int> bits_to_cross;
    int nb_cross = P1.size() * 0.05; //TODO : A VOIR

    do
    {   bits_to_cross = vector<int>();
        P1.bit_mask(bits_to_cross);
        //cout << "bits size  : " << bits_to_cross.size() << ", nb_cross=" << nb_cross << endl;
    } while (bits_to_cross.size() < nb_cross);
    
    
    //cout << "bits : ";
    for (int bit : bits_to_cross){
        //cout <<bit<<", ";
        E1[bit] = P2[bit];
        E2[bit] = P1[bit];
    }
    E1.update_graphs();
    E2.update_graphs();
    //cout<< endl;
}
/**************************************************************************/
/******************************** AFFICHAGE *******************************/
ostream& operator<<(ostream& stream, const Solution& solution){
    stream << "Solution (taille " << solution.size() << ")" << endl;
    stream << "{" << endl;
    for(int i=0; i<int(solution.size()); i++){
        stream << solution[i] << "\t";
        if( i%Solution::instance->Grid_size() == Solution::instance->Grid_size()-1) stream << endl;
    }
    return stream << "}" << endl;
}
/**************************************************************************/
