#include "../include/Instance.hpp"
#include "../include/FileManager.hpp"

using namespace std;



int main(){   

    string instanceName = "captANOR150_7_4";
    instanceName = "grille1010_1";
    Instance instance_1 = Instance();
    vector< pair<float,float> > grille;
    int grid_size;
    //lecture_instance_alea( instanceName, grille, grid_size);
    lecture_instance_tronc( instanceName, grille, grid_size);
    cout << "grid size = " << grid_size << endl;
    
}