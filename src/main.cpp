#include "../include/Instance.hpp"
#include "../include/FileManager.hpp"

using namespace std;



int main(){   

    string instanceName = "captANOR150_7_4";
    instanceName = "grille2525_2"; // grille1010_1

    vector< pair<float,float> > targets;
    int N;

    //N = lecture_instance_alea( instanceName, targets);
    N = lecture_instance_tronc( instanceName, targets);

    int targets_number = targets.size();
    cout << "targets_number = " << targets_number << endl;
    cout << "grid size = " << N << " * " << N<< endl;
    
}