#include "../include/Instance.hpp"

/**************************************** CONSTRUCTORS ****************************************/
/**********************************************************************************************/

ostream& Instance::print(ostream& stream) const{
    stream << "Instance (grid size=" << grid_size << "*" << grid_size << ",";
    stream << "R_capt=" << R_capt << ",R_com=" << R_com << ",K=" << K << ")" << endl;
    stream << "{" << endl;
    return stream;
}
/********* fonctions externes ***************************/ 
// ostream& operator<<(ostream& stream, const Instance& inst){
//     inst.print(stream);
//     return stream;
// }