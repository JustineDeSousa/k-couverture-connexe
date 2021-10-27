#ifndef INSTANCE_ALEA_HPP
#define INSTANCE_ALEA_HPP

#include "Instance.hpp"

class Instance_alea : public Instance
{
private:
    vector< pair<float,float> > cibles; //position des cibles

    friend ostream& operator<<(ostream& stream, const Instance_alea& inst);
public:
    //Constructeur grâce à la lecture d'un fichier
    Instance_alea( const string instance_name, int capt=1, int com=1, int k=1);

    //getters
    int size() const{ return cibles.size(); };

    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Renvoie l'ensemble des cibles contenues dans le carré de taille width avec
    //coin supérieur droit = (x,y)
    vector<int> bit_mask(float x, float y);
    /**************************************************************************/
};
#endif
