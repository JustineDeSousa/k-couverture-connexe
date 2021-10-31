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

/*
void write_sol_inst_alea(Solution& solution, const string nom_instance, float average){
    string filename = "./instances_alea.txt";


    std::ofstream out_file(filename);
    if (!out_file) {
        std::cerr << "Could not create output file\n";
        exit(-1);
    }

    std::string str;
    while (std::getline(in_file, str)) {
        out_file << str <<  " & " << solution.nb_capteurs() << " & " << average<< " & PL" << "\n";
    }


}
*/


