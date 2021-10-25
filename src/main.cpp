#include "../include/Instance.hpp"
#include "../include/Solution.hpp"
#include "../include/Graph.hpp"
#include "../include/FileManager.hpp"
#include "Population.hpp"

using namespace std;



int main(){   

    /** test lecture **/
    /*
    string instanceName = "captANOR150_7_4"; //alea
    vector< pair<float,float> > targets;
    int N;
    N = lecture_instance_alea( instanceName, targets);
    int targets_number = targets.size();
    cout << "targets_number = " << targets_number << endl;
    cout << "grid size = " << N << " * " << N<< endl;
    */


    string instanceName = "grille1010_1"; // grille1010_1, grille2525_2
    vector< pair<int,int> > targets;
    int N;
    N = lecture_instance_tronc( instanceName, targets);

    int targets_number = targets.size();
    cout << "targets_number = " << targets_number << endl;
    cout << "grid size = " << N << " * " << N<< endl;


    /** test Instance **/ 
    //Instance<float> inst(targets, N);
    Instance<int> inst(targets, N);
    cout << inst;
    cout << "target 1 and target 2 can be capted ? " << inst.is_capted(1, 2) << endl;


    /** test Solution **/
    Solution sol(targets_number);
    cout << "Initialize solution : " << sol;
    cout << "Shorter way :" << endl;
    sol.short_print(cout);

    /* test Graph */
    Graph<int> graph_capt(inst, sol, captation);
    cout << graph_capt<<endl;

    Graph<int> graph_com(inst, sol, communication);
    cout << graph_com<<endl;
}