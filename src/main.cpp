#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/Population.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;


const Instance* Solution::instance;

int main(){
    srand (static_cast <unsigned> (time(0)));

    //cout << endl << "TEST INSTANCE ALEA" << endl;
    //instance_name = "captANOR150_7_4";
    //Instance_alea inst_alea(instance_name);
    //cout << "inst_alea.size() = " << inst_alea.size() << endl;
    //cout << "inst_alea : " << inst_alea << endl;
    //cout << "OK" << endl;

    //cout << endl << "TEST SOLUTION(Instance_alea*)" << endl;
    //Solution solution_1();
    // cout << solution_1 << endl;
    //cout << "OK" << endl;


    
    //cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);
    //cout << "inst_tronc.size() = " << inst_tronc.size() << endl;
    //cout << "inst_tronc : " << inst_tronc << endl;
    //cout << "OK" << endl;

    Solution::instance = &inst_tronc;
    cout << endl << "TEST SOLUTION(Instance_tronc*)" << endl;
    Solution solution;
    Solution solution_t;
    cout << solution << endl;
    cout << "OK" << endl;




/*
    cout << "TEST POPULATION(solutions)" << endl;
    vector<Solution> solutions = {solution, solution_t};
    Population parents(solutions, Selection::ELITE);
    cout << parents << endl;
    Population enfants(&inst_tronc);
    parents.selection(enfants);
    cout << "OK" << endl;  
*/



    cout << endl << "TEST GRAPHS(Instance_tronc*)" << endl;
    solution.update_graphs();
    cout << solution.get_graph_capt() << endl;
    cout << solution.get_graph_com() << endl;


    cout<<endl <<" TEST solution.reverse(5, true) "<< endl;
    solution.reverse(5, true);
    cout << solution.get_graph_capt() << endl;
    cout << solution.get_graph_com() << endl;

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

    cout << "here" << endl;

    cross_over(P1, P2, E1, E2);
    cout << endl <<"E1 : " << E1<< endl;
    cout << endl << "E2 : "<< E2 << endl;


  
}