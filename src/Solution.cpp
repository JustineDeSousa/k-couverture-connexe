#include "Solution.hpp"

/**********************************/
/******* fonctions membres *******/
/**********************************/
int Solution::pena_couverture(){
    int sum_couverture = 0;
    for(uint i=0; i<size(); i++){
        sum_couverture += instance.k() - nb_couverture(i);
    }
    return sum_couverture;
}
int Solution::nb_couverture(int i){
    //A ECRIRE
    return 0;
}
/**********************************/
/******* fonctions externes *******/
/**********************************/
