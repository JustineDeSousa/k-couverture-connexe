#include "Instance.hpp"

using namespace std;



int main(){

    pair<float,float> paire;
    paire = make_pair(1, 1);
    

    string instanceName = "captANOR150_7_4";
    cout << "instanceName = captANOR150_7_4" << endl;
    Instance instance_1 = Instance();
    cout << instance_1.grid_size() << endl;
    instance_1.lecture_instance( instanceName, alea);
    cout << "grid size = " << instance_1.grid_size() << endl;
    string line = "0 1 2";
    //cout << "line[0] = " << line[0] << " line[1] = " << line[1] << " line[2] = " << line[2] << endl;
}