#ifndef INSTANCE_TRONC_HPP
#define INSTANCE_TRONC_HPP

#include "Instance.hpp"

class Instance_tronc : public virtual Instance
{
private:
    const int K=1;
    vector< pair<int,int> > cibles; //position des cibles
    friend ostream& operator<<(ostream& stream, const Instance_tronc& inst);
public:
    //Constructeur grâce à la lecture d'un fichier
    Instance_tronc(const string instance_name, const int capt=1, const int com=1);
};
#endif
