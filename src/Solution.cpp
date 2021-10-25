#include "../include/Solution.hpp"

/**********************************/
/******* fonctions membres *******/
/**********************************/
//print
ostream& Solution::short_print(ostream& stream){
    stream << "Solution : [ " ;

    for (int i = 0; i < size(); i++){
        stream << get_captors()[i] << ", ";
    }

    stream << " ]" << endl;
    return stream;
}
/**********************************/
/******* fonctions externes *******/
/**********************************/

ostream& operator <<(ostream& stream, const Solution & sol){
    stream << "Solution : [ " ;

    for (int i = 0; i < sol.size(); i++)
    {
        stream << i << " : " << sol.get_captors()[i] << ";\t";
    }

    stream << " ]" << endl;
    return stream;
}