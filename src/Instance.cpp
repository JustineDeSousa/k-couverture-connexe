#include "Instance.hpp"

/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
vector<int> Instance::bit_mask(float x, float y){
    vector<int> result;
    float width = 0.1*grid_size;
    cout << "Instance::bit_mask(float x, float y) : A ECRIRE CHEZ LES CLASSES FILLES" << endl;
    return result;
}
/**************************************************************************/

ostream& Instance::print(ostream& stream) const{
    stream << "Instance (grid size=" << grid_size << "*" << grid_size << ",";
    stream << "R_capt=" << R_capt << ",R_com=" << R_com << ",K=" << K << ")" << endl;
    stream << "{" << endl;
    return stream;
}
/********* fonctions externes ***************************/ 
ostream& operator<<(ostream& stream, const Instance& inst){
    inst.print(stream);
    return stream;
}