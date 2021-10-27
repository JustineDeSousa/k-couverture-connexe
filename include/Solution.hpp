#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"


class Solution : public vector<bool>
{
private:
    const Instance* const instance; //const pointer to const object, neither the ptr nor object modifiable
    vector< set<int> > graph_capt;
    vector< set<int> > graph_com;

    friend ostream& operator<<(ostream& stream, const Solution solution);

public:
    Solution(const Instance* const inst): vector<bool>(inst->size(),1), instance(inst){ (*this)[0] = 0; };
    // Solution(const Instance* const inst, const vector<bool>& captors): 
    //             vector<bool>(captors), instance(inst){(*this)[0] = 0; };

    /*********************** EVALUATION DE LA SOLUTION ***********************/
    //Renvoie le nombre de composantes connexes
    int nb_connexite();
    bool is_connexe(){ return nb_connexite() == 1; }
    //renvoie le nombre de couverture de la cible i
    int nb_couverture(int i);
    //nb de couverture de chacune des cibles
    vector<int> nb_couverture();
    bool is_k_covered();
    //renvoie le nombre de capteurs
    int nb_capteurs(){ return accumulate((*this).begin(),(*this).end(),0); };
    //Score de la solution
    int fitness();

    // bool sol_capt_linked(int i, int j){ 
    //     if( (*this)[i]){
    //         return instance->capt_linked(i,j);
    //     }else{
    //         return 0;
    //     }
         
    // };
    /**************************************************************************/

    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Inverse le bit i et mets à jour le graphe
    void reverse(int i);
    //Renvoie les val de la solution sur le bit_mask de instance
    vector<bool> val_bit_mask();
    
    //Fais muter la solution avec proba mut_rate 
    // Pour l'instant on inverse un seul bit
    void mutation(float mut_rate);
    /**************************************************************************/
};

#endif
/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
// Renvoie les deux enfants E1 et E2 issus du cross_over de P1 et P2
pair<Solution,Solution> cross_over(Solution P1, Solution P2);
/**************************************************************************/