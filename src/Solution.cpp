#include "../include/Solution.hpp"

/**********************************/
/******* fonctions externes *******/
/**********************************/

ostream& operator <<(ostream& stream, const Solution & sol){
    stream << "Solution : [ " ;

    for (int i = 0; i < sol.size(); i++)
    {
        stream << i << "=" << sol.get_captors()[i] << ", ";
    }

    stream << " ]" << endl;
    return stream;
}