#include "../include/Solution.hpp"

/**************************************** CONSTRUCTORS *****************************/
Solution::Solution(const Solution& solution, bool G) : vector<bool>(solution.size())
{   
    // this->resize(solution.size());

    for (uint i = 0; i < solution.size(); i++)
    {
        (*this)[i] = solution[i];
    }
    if(G){
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
    }
}


Solution& Solution::operator=(const Solution& solution){
    if(this == &solution) return *this;
    if(this->size() == 0 ) *this=vector<bool>(solution.size());//->resize(solution.size());
    for (int i = 0; i < int(solution.size()); i++)
    {
        (*this)[i] = solution[i];
    }
    graph_capt = solution.graph_capt;
    graph_com = solution.graph_com;
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
    cout << "\t\toperator<\n";
    cout << "\t\t\tsol1 = ";
    int a = fitness();
    cout << "\t\t\tsol2 = ";
    int b = solution.fitness();
    bool resul = a < b;
    cout << "\t\t< over\n";
    return resul;
}
bool Solution::operator<=(const Solution& solution) const{
    return fitness() <= solution.fitness();
}
bool Solution::operator==(const Solution& solution) const{
    return fitness() == solution.fitness();
}
int Solution::nb_connected_component() const {
    vector<bool> v=(*this); 
    return graph_com.nb_connected_components(v); 
}
/**
 * @brief Return the number of captors covering target i
 * 
 * @param i 
 * @return int 
 */
int Solution::captation(int i) const{
    return graph_capt[i].size();
}

/**
 * @brief Return the total number of missed captors for each targets
 * 
 * @return int 
 */
int Solution::nb_captation_missed() const{
    cout << "\t\t\t\tSolution::nb_captation_missed()\n";
    int missed = 0;
    for (int i=1; i<int(size()); i++)// we don't consider the k-coverage for the sink
    {
        if(graph_capt.size() == 0){
            cout << "\t\t\t\t" << i << " : graph_capt.size() = " << graph_capt.size() << endl;
            if(*this==vector<bool>(size(),0)){
                cout << "\t\t\t\tsol == vecteur nul" << endl;
            }else if(*this == vector<bool>(size(),1)){
                cout << "\t\t\t\tsol == vecteur de 1" << endl;
                return 0;
            }
        } 
        if(graph_capt.degree(i) < Solution::instance->k()){
            missed += Solution::instance->k() - graph_capt.degree(i);
        }
    }
    cout << "\t\t\t\tnb_captation_missed = " << missed <<endl;
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
    int fit = nb_capteurs() + nb_connected_component()-1 + nb_captation_missed();
    cout << "\t\t\tfitness = " << fit << endl;
    return fit;
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


void Solution::bit_mask(vector<int>& result) const{
    // a random float between 0.0 and grid_size
    float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ Solution::instance->Grid_size()));
    float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ Solution::instance->Grid_size()));
    Solution::instance->bit_mask(x, y, result);
}


// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2){
    vector<int> bits_to_cross;
    P1.bit_mask(bits_to_cross);

    for (int bit : bits_to_cross)
    {   cout << bit << ", " ;
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
        if( i%Solution::instance->Grid_size()-1 == 0) stream << endl;
    }
    return stream << "}" << endl;
}
/**************************************************************************/
