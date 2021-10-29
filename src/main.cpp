
#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/Population.hpp"
#include "../include/algo_genetic.hpp"

using namespace std;

const Instance* Solution::instance;

void test(){
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

    Solution E1(P1, false);
    Solution E2(P2, false);
    cout << P1 << endl;
    cout << P2 << endl;

    cross_over(P1, P2, E1, E2);
    cout << endl << "E1 : " << E1 << endl;
    cout << endl << "E2 : " << E2 << endl;

    cout << "\n\n***************************************** TEST POPULATION *****************************************" << endl;
    vector<Solution> solutions = {P1, P2, E1, E2};
    Population pop(solutions);
    cout << "Population de taille " << pop.size() << endl;

    cout << "pop.sort()" << endl;
    pop.sort();
    cout << "pop = " << pop << endl;

    genetic_algo(pop, 1,Selection::ROULETTE,0.5);
     
    // cout << "TEST HEURICTIC" << endl;
    // Solution sol_heuristic;
    // sol_heuristic.update_graphs();
    // cout << "AVANT sol_heuristic=" << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    // heuristic(sol_heuristic);
    // cout <<"APRES sol_heuristic = " << sol_heuristic << endl <<"fit = " << sol_heuristic.fitness()<< endl;
    // cout << "is_realisable = " <<sol_heuristic.is_realisable() << endl;

}



int main(int argc, char** argv){
    srand (static_cast <unsigned> (time(0)));

    // Check the number of parameters
    if (argc < 2) {
        cerr<< "No input file" << endl;
        exit(-1);
    }
    string fname = argv[1];
    vector<string> seglist;
    stringstream ss(fname);
    string s;
    
    while(getline(ss, s, '/'))
    {
        seglist.push_back(s);
    }

    string instance_name = seglist[2].substr(0, seglist[2].size()-4);
    cout << "Input file name : " <<instance_name << endl;


    if(instance_name[0] == 'c'){
        Instance_alea inst_alea(instance_name);
        Solution::instance = &inst_alea;
        test();

 }else if(instance_name[0] == 'g'){
        Instance_tronc inst_tronc(instance_name);
        Solution::instance = &inst_tronc;
        test();
}



}