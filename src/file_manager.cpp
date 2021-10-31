#include "../include/file_manager.hpp"

void write_solution(Solution& solution, const string nom_instance, float average){
    string filename = "./solutions/" + nom_instance + ".sol";
    ofstream stream(filename.c_str());
    stream << "R_capt = " << Solution::instance->capt() << endl;
    stream << "R_com = " << Solution::instance->com() << endl;
    stream << "K = " << Solution::instance->k() << endl;
    if(stream){
        for(int i=0; i<solution.size(); i++){
            stream << solution[i] << endl;
        }
    }
    stream << "best solution = " << solution.fitness() << endl;
    stream << "average solution = " << average << endl;

}
