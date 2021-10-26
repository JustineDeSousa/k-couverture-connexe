#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"

using namespace std;


class Solution : public vector<bool>
{
private:
    Instance instance;

public:
    Solution(int size = 0): vector<bool>(size,1){ (*this)[0] = 0;};
    Solution(vector<bool> captors): vector<bool>(captors){(*this)[0] = 0; };

    //Renvoie le nombre de composantes connexes
    int nb_connexite();
    //renvoie le nombre de couverture de la cible i
    int nb_couverture(int i);
    //somme des k-nb_couverture(i)
    int pena_couverture();
    //renvoie le nombre de capteurs
    int nb_capteurs(){ return accumulate((*this).begin(),(*this).end(),0); };

    int fitness(){ return nb_capteurs() + nb_connexite() + pena_couverture(); };

    void reverse(int i){ (*this)[i] = 1-(*this)[i]; };
};

#endif