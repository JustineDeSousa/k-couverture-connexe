#include "Instance.hpp"
#include "Solution.hpp"
#include "Graph.hpp"
#include "FileManager.hpp"
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
    cout << "target 1 and target 2 can be capted ? " << inst.do_capt(1, 2) << endl;


    /** test Solution **/
    Solution<int> sol(targets_number);
    cout << "Initialize solution : " << sol;
    cout << "Shorter way :" << endl;

    sol.short_print(cout);
    cout << "Number of captors = " << sol.nb_captors() << endl;
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

    /* test Graph */
    sol.update_graph_capt(inst);
    sol.update_graph_com(inst);

    cout<< sol.get_graph_capt()<< endl;

}