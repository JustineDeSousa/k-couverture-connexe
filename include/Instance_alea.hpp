#ifndef INSTANCE_ALEA_HPP
#define INSTANCE_ALEA_HPP

#include "Instance.hpp"

class Instance_alea : public virtual Instance

{
private:
    vector< pair<float,float> > cibles; //position des cibles

    ostream& print(ostream& stream) const;
    friend ostream& operator<<(ostream& stream, const Instance_alea& inst);
public:
    /**************************************** CONSTRUCTORS ****************************************/
    Instance_alea(const int capt=1, const int com=1, const int k=1);
    //Constructeur grâce à la lecture d'un fichier
    Instance_alea( const string instance_name, int capt=1, int com=1, int k=1);
    /**********************************************************************************************/
    

    //getters
    int size() const{ return cibles.size(); };
    virtual pair<float, float> getPosition(uint i) const { return cibles[i]; };

    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Renvoie l'ensemble des cibles contenues dans le carré de taille width avec
    //coin supérieur droit = (x,y)
    void bit_mask(float x, float y, vector<int>& result) const ;
    /**************************************************************************/
};
#endif
