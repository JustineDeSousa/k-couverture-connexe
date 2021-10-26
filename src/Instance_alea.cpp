#include "Instance_alea.hpp"

void tokenize(std::string const &str, const char delim, vector<std::string> &out) 
{ 
    // construct a stream from the string 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        if(s != " " && s != "")
            out.push_back(s); 
    } 
}

Instance_alea::Instance_alea( const string instance_name, const int capt, const int com, const int k)
                                :Instance(capt,com,k){
    //Lecture grid_size
    vector<string> tab;
    tokenize(instance_name, '_', tab);
    grid_size = stoi(tab[1]);

    string filename = "./instances/" + instance_name + ".dat";
    cout << "Instance_alea:: Lecture du fichier " << filename << endl;
    ifstream file(filename, ios::in);

    if(file.is_open()){
        float x,y;
        while( file >> x){
            file >> x >> y;
            cibles.push_back( make_pair(x,y) );
        }
    file.close();
    }else{
        cerr << "Couldn't open file : " << filename << endl;
        exit(-1);
    }
    //Calcul de la matrice des distances
    init_dist(cibles);
}


/********* fonctions externes ***************************/ 
ostream& operator<<(ostream& stream, const Instance_alea& inst){
    inst.print(stream);
        stream << "list of targets : [" << endl;
    for(uint i=0; i<inst.cibles.size(); i++){
        stream << "#" << i << "=(" << inst.cibles[i].first << "," << inst.cibles[i].second << ")\t";

        if(i%inst.grid_size == 0) stream << endl;
    }
    stream << "]" << endl;
    return stream << "}";
}