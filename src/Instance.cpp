#include "Instance.hpp"

//Affichage
ostream& Instance::print(ostream& stream) const
{
    stream  << "Instance (grid size=" << grid_size << "*" << grid_size
            << ",R_capt=" << R_capt << ",R_com=" << R_com << ",K=" << K << "){" << endl;
    return stream;
}
