#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"
#include "Graph.hpp"


class Solution : public vector<bool>
{
private:
    const Instance* const instance; //const pointer to const object, neither the ptr nor object modifiable
    Graph Graph_capt;
    Graph Graph_com;

    friend ostream& operator<<(ostream& stream, const Solution &solution);

public:
    Solution(const Instance* const inst): vector<bool>(inst->size(),1), instance(inst){ (*this)[0] = 0; };
    // Solution(const Instance* const inst, const vector<bool>& captors): 
    //             vector<bool>(captors), instance(inst){(*this)[0] = 0; };


    //renvoie le nombre de capteurs
    int nb_capteurs(){ return accumulate((*this).begin(),(*this).end(),0); };
    Graph get_graph_capt() const {return Graph_capt;}
    Graph get_graph_com() const {return Graph_com;}
    void update_graphs(int t); // update the neighbourhood of target t
    void update_graphs() {Graph_capt = Graph(instance, *this, captation); 
    Graph_com = Graph(instance, *this, communication);};


    /*********************** EVALUATION DE LA SOLUTION ***********************/

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