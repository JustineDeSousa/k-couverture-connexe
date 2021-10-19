#include "Instance.hpp"

void tokenize(std::string const &str, const char delim, 
            std::vector<std::string> &out) 
{ 
    // construct a stream from the string 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        if(s != " " && s != "")
            out.push_back(s); 
    } 
}


void Instance::lecture_instance( const string instanceName, const mode mod, int gridSize ){
    string filename = "instances/" + instanceName + ".dat";
    ifstream file(filename, ios::in);
    if(file){
        if(mod == alea){
            string line;
            
            while( getline(file, line) ) //Tant qu'on n'est pas à la fin, on lit
            {
                vector<string> tab;
                tokenize(line, ' ', tab);
                int nb = stoi(tab[0]);
                targets.push_back( make_pair(stof(tab[1]), stof(tab[2])) );
            }
        }
    }
}
