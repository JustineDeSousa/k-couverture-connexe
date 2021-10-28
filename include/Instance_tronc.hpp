#ifndef INSTANCE_TRONC_HPP
#define INSTANCE_TRONC_HPP

#include "Instance.hpp"

class Instance_tronc : public Instance
{
private:
    const int K=1;
    vector< pair<int,int> > cibles; //position des cibles
    
    friend ostream& operator<<(ostream& stream, const Instance_tronc& inst);

public:
    /**************************************** CONSTRUCTORS ****************************************/
    Instance_tronc(const int capt=1, const int com=1);
    //Constructeur grâce à la lecture d'un fichier
    Instance_tronc(const string instance_name, const int capt=1, const int com=1);
    /**********************************************************************************************/
    

    //getters
    int size() const{ return cibles.size(); };

    /******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
    //Renvoie l'ensemble des cibles contenues dans le carré de taille width avec
    //coin supérieur droit = (x,y)
    void bit_mask(float x, float y, vector<int>& result) const ;

    /**************************************************************************/
};
#endif
