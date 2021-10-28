#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"
#include "Graph.hpp"

class Solution : public vector<bool>
{
private:
    const Instance* const instance; //const pointer to const object, neither the ptr nor object modifiable
    Graph graph_capt;
    Graph graph_com;

    friend ostream& operator<<(ostream& stream, const Solution &solution);

public:
    /**************************************** CONSTRUCTORS ****************************************/
    Solution(const Instance* const inst): vector<bool>(inst->size(),1), instance(inst){ (*this)[0] = 0; };
    Solution& Solution::operator=(const Solution& solution);
    /**********************************************************************************************/
    /**************************************** GETTERS *********************************************/
    //const Instance* get_instance() const{ return instance; };
    Graph get_graph_capt() const {return graph_capt;}
    Graph get_graph_com() const {return graph_com;}
    /**********************************************************************************************/
    /******************************** OPERATIONS DE GRAPHE ****************************************/
    // update the neighbourhood of target t
    void update_graphs(int t);
    void update_graphs() {graph_capt = Graph(instance, *this, Network::captation); 
    graph_com = Graph(instance, *this, communication);};
    /**********************************************************************************************/
    /*********************** EVALUATION DE LA SOLUTION ***********************/
    //renvoie le nombre de capteurs
    int nb_capteurs() const{ return accumulate((*this).begin(),(*this).end(),0); };
    // return the number of connected component in the communication network 
    int nb_connected_component() const{ return graph_com.nb_connected_components(); };
    int captation(int i) const;
    vector<int> captation() const;
    int nb_captation() const;
    bool is_k_covered() const;
    int fitness() const;
    bool Solution::operator<(const Solution& solution) const;
    /**************************************************************************/
    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Inverse le bit i et mets à jour le graphe
    void reverse(int i, bool G);
    //Fais muter la solution avec proba mut_rate 
    // Pour l'instant on inverse un seul bit
    void mutation(float mut_rate);
    /**************************************************************************/
};

#endif
/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
void cross_over(const Solution& P1, const Solution& P2, Solution& E1, Solution& E2);
/**************************************************************************/