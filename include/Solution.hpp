#ifndef SOLUTION_HPP
#define SOLUTION_HPP


#include "Instance.hpp"
#include "Graph.hpp"

class Solution : public vector<bool>
{
private:
    Graph graph_capt;
    Graph graph_com;

    friend ostream& operator<<(ostream& stream, const Solution &solution);

public:
    static const Instance* instance; 

    /**************************************** CONSTRUCTORS ****************************************/
    Solution(): vector<bool>(Solution::instance->size(),1){ (*this)[0] = 0; };
    Solution(const vector<bool>& vec): vector<bool>(vec) {};
    Solution(const Solution& solution, bool G=false);
    Solution& operator=(const Solution& solution); //TODO tester
    /**********************************************************************************************/
    /**************************************** GETTERS *********************************************/
    void bit_mask(vector<int>& result) const;
    Graph get_graph_capt() const {return graph_capt; };
    Graph get_graph_com() const {return graph_com; };

    /**********************************************************************************************/
    /******************************** OPERATIONS DE GRAPHE ****************************************/
    // update the neighbourhood of target t
    void update_graphs(int t);
    void update_graphs();
    /**********************************************************************************************/
    /*********************** EVALUATION DE LA SOLUTION ***********************/
    bool operator<(const Solution& solution) const;
    bool operator<=(const Solution& solution) const;
    bool operator==(const Solution& solution) const;
    //renvoie le nombre de capteurs
    int nb_capteurs() const{ return accumulate((*this).begin(),(*this).end(),0); };
    // return the number of connected component in the communication network 
    int nb_connected_component() const;
    bool is_graph_com_connected() const {vector<bool> v=(*this); return graph_com.nb_connected_components(v)==1;}
    int captation(int i) const;
    int nb_captation_missed() const;
    bool is_k_covered() const;
    int fitness() const;
    bool is_realisable() const {return is_k_covered() && is_graph_com_connected();}
    /**************************************************************************/
    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Inverse le bit i et mets à jour le graphe
    void reverse(int i, bool G);
    //Fais muter la solution avec proba mut_rate 
    // Pour l'instant on inverse un seul bit
    void mutation(float mut_rate);
    /**************************************************************************/
};
/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2);
/**************************************************************************/
#endif
