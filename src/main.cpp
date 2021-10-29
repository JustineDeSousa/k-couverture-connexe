
#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/Population.hpp"
#include "../include/algo_genetic.hpp"

using namespace std;

const Instance* Solution::instance;


int main(){
    srand (static_cast <unsigned> (time(0)));

    
    //cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);

    Solution::instance = &inst_tronc;
    Solution solution;
    cout << "Solution::instance = " << static_cast<const Instance_tronc&>(*solution.instance) << endl;
    cout << "solution.is_graph_com_connected() : "<< solution.is_graph_com_connected() << endl;
    cout << " solution.nb_connected_component : " << solution.nb_connected_component() << endl;
    cout << "solution.nb_capteurs() : " << solution.nb_capteurs() << endl;
    cout << "solution.is_k_covered : " <<solution.is_k_covered() << endl;
    cout << "solution.nb_captation_missed() : " << solution.nb_captation_missed() << endl;


    cout << "TEST CROSS OVER"<< endl;
    vector<bool> v1(solution.size(), 0);
    vector<bool> v2(solution.size(), 1);
    Solution P1(v1);
    Solution P2(v2);

    Solution E1(P1);
    Solution E2(P2);
    cout << "P1 : fitness = " << P1.fitness() << " " << P1 << endl;
    cout << "P2 : fitness = " << P2.fitness() << " " << P2 << endl;

    cross_over(P1, P2, E1, E2);
    E1.update_graphs();
    cout << "E1 : fitness = " << E1.fitness() << " " << E1 << endl;
    cout << "E2 : fitness = " << E2.fitness() << " " << E2 << endl;

    cout << "\n\n***************************************** TEST POPULATION *****************************************" << endl;
    int N = 10;
    Population pop;
    Solution sol_heuristic;
    for(int i=0; i<N; i++){
        heuristic(sol_heuristic);
        pop.push_back(sol_heuristic);
    }
    
    for(Solution sol : pop){
        cout << sol.fitness() << " ";
    }
    
    cout << "\nPopulation de taille " << pop.size() << endl;

    genetic_algo(pop, 1,Selection::ROULETTE,0.5);
     
    // cout << "TEST HEURICTIC" << endl;
    
    // sol_heuristic.update_graphs();
    // cout << "AVANT sol_heuristic=" << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    
    // cout <<"APRES sol_heuristic = " << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    // cout << "is_realisable = " <<sol_heuristic.is_realisable() << endl;

}