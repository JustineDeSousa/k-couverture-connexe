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
#include <assert.h>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>

typedef unsigned int uint;
using namespace std;

enum Network { captation, communication };

class Instance : public vector< vector<float> >
//Matrice des distances entre chaque cible
{
protected:
    int grid_size; // nb cibles = grid_size * grid_size
    int const R_capt; // radius captation
    int const R_com; // radius communication
    int const K; // k couverture
    int width_bit_mask; //pour le crossover

    /*************************** AFFICHAGE ***************************/
    ostream& print(ostream&) const;
    // friend ostream& operator<<(ostream&,const Instance&);
    /*****************************************************************/
public:
    /**************************************** CONSTRUCTORS ****************************************/
    Instance(const int capt=1, const int com=1, const int k=1)
            :grid_size(0), R_capt(capt), R_com(com), K(k), width_bit_mask(0.5*grid_size){};
    Instance(const string instance_name, int const capt=1, int const com=1, int const k=1);
    template <typename number>
    void init_dist(const vector< pair<number,number> >& targets );
    /**********************************************************************************************/
    /**************************************** GETTERS *********************************************/
    int capt() const{ return R_capt; };
    int com() const { return R_com; };
    int k() const{ return K; };
    virtual int size() const = 0;
    int Grid_size() const{ return grid_size; };
    /**********************************************************************************************/
    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //on pourrait supposer i<j et stocker que la moitié de la matrice
    bool capt_linked(int i, int j) const { return (*this)[i][j] <= R_capt; };
    bool com_linked(int i, int j) const { return (*this)[i][j] <= R_com; };
    //Renvoie l'ensemble des cibles contenues dans le carré de taille width avec
    //coin supérieur gauche = (x,y)
    virtual void bit_mask(float x, float y, vector<int>& result) const = 0;
    /**************************************************************************/
};
/********* fonctions externes ***************************/
template <typename number>
float dist(pair<number,number> i, pair<number,number> j);



/************************* IMPLEMENTATION *********************************/ 
/**************************************************************************/
//Calcul de la matrice des distances
//matrice symétrique, on pourrait stocker que la moitié
template <typename number>
void Instance::init_dist(const vector< pair<number,number> >& cibles )
{
    vector<float> v(cibles.size(), 0.0);
    (*this).resize(cibles.size(), v);
    for(uint i = 0; i < cibles.size(); i++){
        for(uint j=0; j<cibles.size(); j++){
            if(i==j) continue;
            (*this)[i][j] = dist(cibles[i], cibles[j]);
        }
    }
}
/**
 * @brief Calcule la distance entre i et j
 * 
 * @param i,j = cibles 
 */
template <typename number>
float dist(pair<number,number> i, pair<number,number> j){
    return sqrt( pow(i.first-j.first,2) + pow(i.second-j.second,2) );
}
#endif