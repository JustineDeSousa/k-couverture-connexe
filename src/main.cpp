
#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/Population.hpp"
#include "../include/algo_genetic.hpp"
#include <algorithm> 
#include <cstdlib>
#include <ctime>

using namespace std;

const Instance* Solution::instance;


int main(){
    srand (static_cast <unsigned> (time(0)));

    
    //cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);
    Solution::instance = &inst_tronc;


    cout << "\n\n***************************************** TEST GENETIC *****************************************" << endl;
    int N = 100; //TODO : 100
    Population pop;
    for(int i=0; i<N; i++){
    set<vector<bool>> vec;
    while (vec.size() < N)
    {
        Solution sol_heuristic;
        heuristic(sol_heuristic);
        vec.insert( vec.end(), sol_heuristic);
    }
    set<vector<bool>>::const_iterator it = vec.begin();

    for(; it != vec.end(); it++){

        pop.push_back(Solution(*it));
    }
    Solution best_sol = pop.best_individual();

    genetic_algo(pop, best_sol, 3, Selection::ROULETTE, 0.5); //TODO : 3 min / ELITE, ROULETTE

    // cout << "TEST HEURICTIC" << endl;
    
    // sol_heuristic.update_graphs();
    // cout << "AVANT sol_heuristic=" << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    
    // cout <<"APRES sol_heuristic = " << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    // cout << "is_realisable = " <<sol_heuristic.is_realisable() << endl;

}