#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <numeric>
#include <math.h>
#include <sstream>

typedef unsigned int uint;
using namespace std;


class Instance : public vector< vector<float> >
//Matrice des distances entre chaque cible
//matrice symétrique, on pourrait stocker que la moitié
{
protected:
    int grid_size; // nb cibles = grid_size * grid_size
    int const R_capt; // radius captation
    int const R_com; // radius communication
    int const K; // k couverture
    int const width_bit_mask;

    ostream& print(ostream&);
    friend ostream& operator<<(ostream& stream, const Instance& inst);

public:

    Instance(const int capt=1, const int com=1, const int k=1)
            :grid_size(0), R_capt(capt), R_com(com), K(k), width_bit_mask(0.1*grid_size){};
    Instance(const string instance_name, int const capt=1, int const com=1, int const k=1);

    template <typename number>
    void init_dist(const vector< pair<number,number> >& targets );

    //getter
    int k(){ return K; };
    virtual int size(){ return grid_size*grid_size; };
    int Grid_size(){ return grid_size; };

    //on pourrait supposer i<j et stocker que la moitié de la matrice
    //Doit être dans Solution
    // bool capt_linked(int i, int j){ return (*this)[i][j] <= R_capt; };
    // bool com_linked(int i, int j){ return (*this)[i][j] <= R_com; };

    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Renvoie l'ensemble des cibles contenues dans le carré de taille width avec
    //coin supérieur droit = (x,y)
    virtual vector<int> bit_mask(float x, float y);
    /**************************************************************************/

    //Affichage
    ostream& print(ostream& stream) const;
};
/********* fonctions externes ***************************/ 

template <typename number>
float dist(pair<number,number> i, pair<number,number> j);



/********* IMPLEMENTATION ***************************/ 

//Calcul de la matrice des distances
//matrice symétrique, on pourrait stocker que la moitié
template <typename number>
void Instance::init_dist(const vector< pair<number,number> >& cibles )
{
    (*this).reserve(cibles.size());
    for(uint i=0; i<cibles.size(); i++){
        (*this)[i] = vector<float>(cibles.size(),0);
        for(uint j=0; j<cibles.size(); j++){
            if(i==j) continue;
            (*this)[i].push_back(dist(cibles[i], cibles[j]));
        }
    }
}

template <typename number>
float dist(pair<number,number> i, pair<number,number> j){
    return sqrt( pow(i.first-j.first,2) + pow(i.second-j.second,2) );
}
#endif