#include "Instance.hpp"
#include "Instance_tronc.hpp"
#include "Instance_alea.hpp"
#include "Solution.hpp"
#include "Population.hpp"

using namespace std;




int main(){
    // cout << "TEST INSTANCE" << endl;
    // Instance inst;
    // cout << "inst.size() = " << inst.size() << endl;
    // cout << "OK" << endl;
    
    cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);
    cout << "inst_tronc.size() = " << inst_tronc.size() << endl;
    // cout << "inst_tronc : " << inst_tronc << endl;
    cout << "OK" << endl;

    cout << endl << "TEST INSTANCE ALEA" << endl;
    instance_name = "captANOR150_7_4";
    Instance_alea inst_alea(instance_name);
    cout << "inst_alea.size() = " << inst_alea.size() << endl;
    // cout << "inst_alea : " << inst_alea << endl;
    cout << "OK" << endl;


    cout << endl << "TEST SOLUTION(Instance_tronc*)" << endl;
    Solution solution(&inst_tronc);
    // cout << solution << endl;
    cout << "OK" << endl;

    cout << endl << "TEST SOLUTION(Instance_alea*)" << endl;
    Solution solution_1(&inst_alea);
    // cout << solution_1 << endl;
    cout << "OK" << endl;

    cout << endl << "TEST SOLUTION(captors)" << endl;
    vector<bool> captors(4,1);
    Solution sol(captors);
    // cout << sol;
    cout << "OK" << endl;

    cout << endl << "TEST SOLUTION(Solution)" << endl;
    Solution solution_2(sol);
    // cout << solution_2 << endl;
    cout << "OK" << endl;

    cout << endl << "TEST nb_couverture()" << endl;
    // for(uint i=0; i<solution_1.size(); i++){
    //     cout << "solution_1.nb_couverture(i)= " 
    //             << solution_1.nb_couverture(i) << endl;
    // }
    // for(uint i=0; i<solution_1.size(); i++){
    //     cout << "solution_1.nb_couverture()[i]= " 
    //             << solution_1.nb_couverture()[i] << endl;
    // }
    cout << "OK" << endl;

    // cout << "TEST POPULATION(solutions)" << endl;
    // vector<Solution> solutions = {solution, sol};
    // Population pop(solutions);
    // cout << "pop.size() = " << pop.size() << endl;
    // cout << "OK" << endl;
}