#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/Population.hpp"

using namespace std;




int main(){

    
    //cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);
    //cout << "inst_tronc.size() = " << inst_tronc.size() << endl;
    //cout << "inst_tronc : " << inst_tronc << endl;
    //cout << "OK" << endl;

    //cout << endl << "TEST INSTANCE ALEA" << endl;
    instance_name = "captANOR150_7_4";
    Instance_alea inst_alea(instance_name);
    //cout << "inst_alea.size() = " << inst_alea.size() << endl;
    //cout << "inst_alea : " << inst_alea << endl;
    //cout << "OK" << endl;


    cout << endl << "TEST SOLUTION(Instance_tronc*)" << endl;
    Solution solution(&inst_tronc);
    cout << solution << endl;
    cout << "OK" << endl;

    cout << endl << "TEST SOLUTION(Instance_alea*)" << endl;
    Solution solution_1(&inst_alea);
    cout << solution_1 << endl;
    cout << "OK" << endl;


    cout << endl << "TEST GRAPHS(Instance_tronc*)" << endl;
    solution.update_graphs();
    cout << solution.get_graph_capt() << endl;
    cout << solution.get_graph_com() << endl;


    cout<<"solution.reverse(5, true) "<< endl;
    solution.reverse(5, true);
    cout << solution.get_graph_capt() << endl;
    cout << solution.get_graph_com() << endl;

  
}