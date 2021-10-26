#include "Instance.hpp"
#include "Instance_tronc.hpp"
#include "Instance_alea.hpp"
#include "Solution.hpp"
#include "Population.hpp"

using namespace std;




int main(){
    cout << "TEST INSTANCE" << endl;
    Instance inst(10);
    cout << "OK" << endl;
    
    cout << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "grille1010_1";
    Instance_tronc inst_tronc(instance_name);
    cout << "inst_tronc : " << endl;
    inst_tronc.print(cout);
    cout << "OK" << endl;

    cout << "TEST INSTANCE ALEA" << endl;
    instance_name = "captANOR150_7_4";
    Instance_alea inst_alea(instance_name);
    cout << "inst_alea : " << endl;
    inst_alea.print(cout);
    cout << "OK" << endl;


    cout << "TEST SOLUTION(i)" << endl;
    Solution solution(2);
    for(bool elmt : solution)
        cout << elmt << endl;
    cout << "OK" << endl;

    cout << "TEST SOLUTION(captors)" << endl;
    vector<bool> captors(4,1);
    cout << "captors = " << endl;
    Solution sol(captors);
    cout << "Solution(captors) = " << endl;
    for(bool elmt : sol)
        cout << elmt << endl;
    cout << "OK" << endl;

    cout << "TEST POPULATION(solutions)" << endl;
    vector<Solution> solutions = {solution, sol};
    Population pop(solutions);
    cout << "pop.size() = " << pop.size() << endl;
    cout << "OK" << endl;
}