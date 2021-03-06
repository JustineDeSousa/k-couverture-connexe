#include "../include/file_manager.hpp"

void write_solution(Solution& solution, const string nom_instance, float average, float average_ite){
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
    stream << "average iterations = " << average_ite << endl;
    stream << "best solution = " << solution.nb_capteurs() << endl;
    stream << "average solution = " << average << endl;

}


