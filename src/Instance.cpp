#include "../include/Instance.hpp"

/**********************************/
/******* fonctions externes *******/
/**********************************/

ostream& operator <<(ostream& stream, const Instance& inst){
    stream << "Instance {"<<endl << "grid size : " << inst.get_N() << "*" << inst.get_N()<<
    "; R_capt=" << inst.get_R_capt() << "; R_com=" << inst.get_R_com() << "; k=" << inst.get_k()<<"; "<<endl;
    
    stream << "list of targets : ["<<endl;
    int i = 0;
    for(pair<float, float> t : inst.get_targets()){
        stream << i << " : " << "(" <<t.first<<", "<<t.second<<")"<<endl;
        i +=1;
    }

      
    return stream <<"]" <<endl;

}
