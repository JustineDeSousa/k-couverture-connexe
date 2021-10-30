#include "../include/file_manager.hpp"

void write_solution(Solution& solution, const string nom_instance){
    string filename = "./solutions/" + nom_instance + ".sol";
    ofstream stream(filename.c_str());
    if(stream){
        for(int i=0; i<solution.size(); i++){
            stream << solution[i] << endl;
        }
    }
    
}