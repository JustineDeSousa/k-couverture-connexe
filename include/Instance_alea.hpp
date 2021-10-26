#ifndef INSTANCE_ALEA_HPP
#define INSTANCE_ALEA_HPP

#include "Instance.hpp"

class Instance_alea : virtual public Instance
{
private:
    vector< pair<float,float> > cibles; //position des cibles
public:
    //Constructeur grâce à la lecture d'un fichier
    Instance_alea( const string instance_name, int capt=1, int com=1, int k=1);

    //Affichage
    ostream& print_targets(ostream& stream) const;
};
#endif
