#include "../include/Instance.hpp"
#include "../include/Solution.hpp"
#include "../include/Graph.hpp"
#include "../include/FileManager.hpp"
#include "../include/Population.hpp"

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
    cout << "target 1 and target 2 can be capted ? " << inst.do_capt(1, 2) << endl;


    /** test Solution **/
    Solution<int> sol(inst, targets_number);
    cout << "Initialize solution : " << sol;
    cout << "Shorter way :" << endl;

    sol.short_print(cout);
    cout << "Number of captors = " << sol.nb_captors() << endl;


    /* test Graph */
    sol.update_graph_capt();
    sol.update_graph_com();
    cout<< sol.get_graph_capt()<< endl;


    /* tets fonctions de Solution */
    vector<int> captors2 = sol.get_captors();
    captors2[3] = 0;
    sol.set_captors(captors2);
    sol.reverse_target(5);
    cout<< "new Sol : " << sol;

    sol.update_graph_com();
    cout << "new graph com : " << sol.get_graph_com();
    sol.update_graph_capt();
    cout << "new graph capt : " << sol.get_graph_capt();

    cout << "sol is_k_coverage ? " << sol.is_k_coverage() << endl;
    cout << "sol nb_captors = " << sol.nb_captors() << endl <<
    "sol constraint_k_capt violated = " << sol.constraint_k_capt() << endl <<
    "sol fonction fitness value = " << sol.fitness() << endl;

}