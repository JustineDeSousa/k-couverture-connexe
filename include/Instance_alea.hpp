#ifndef INSTANCE_ALEA_HPP
#define INSTANCE_ALEA_HPP

#include "Instance.hpp"

class Instance_alea : public virtual Instance
{
private:
    vector< pair<float,float> > cibles; //position des cibles

    friend ostream& operator<<(ostream& stream, const Instance_alea& inst);
public:
    //Constructeur grâce à la lecture d'un fichier
    Instance_alea( const string instance_name, int capt=1, int com=1, int k=1);
};
#endif
