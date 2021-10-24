#include "../include/FileManager.hpp"

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

/**
 * @brief Read instance generated randomly
 * 
 * @param instanceName file name
 * @param res a vector of targets' positions
 * @return int the length of grid
 */
int lecture_instance_alea( const string instanceName, vector< pair<float,float> > &res){
    string filename = "./instances/" + instanceName + ".dat";
    ifstream file(filename, ios::in);

    if(file.is_open()){
        float x, y;
        while( file >> x){
            file >> x >> y;
            cout << "(" << x << ", " << y << ")" << endl;
            res.push_back( make_pair(x,y) );
        }
    file.close();
    }else{
        cerr << "Couldn't open file : " << filename << endl;
        exit(-1);
    }
    
    vector<string> tab;
    tokenize(instanceName, '_', tab);
    return stoi(tab[1]);
}


/**
 * @brief Read instance of grid tronc
 * 
 * @param instanceName file name
 * @param res a vector of targets' positions
 * @return int the length of grid
 */

int lecture_instance_tronc( const string instanceName, vector< pair<float,float> > &res){
    string filename = "./instances/" + instanceName + ".dat";
    ifstream file(filename, ios::in);
    int grid_size = 0;

    if(file.is_open()){
        string token;
        file >> token >> token >> token >> token >> token >> token;
        grid_size = sqrt( stoi(token.substr(2,token.size()-3)) );

        file >> token >> token >> token >> token >> token;
        int nb_lines = stoi( token.substr(2,token.size()-3) );

        getline(file, token);
        getline(file, token);

        res.push_back( make_pair(0,0) ); // the sink
        
        int x, y, id = 0;
        for(int i=0; i<nb_lines; i++ ){
            file >> id >> token >> token;
            x = stoi( token.substr(1,token.size()-2) );
            file >> token;
            y = stoi( token.substr(0,token.size()-1) );

            res.push_back( make_pair(x,y) );
        
        }
    file.close();
    }else{
        cerr <<("Couldn't open file : " + filename).c_str() << endl;
        exit(-1);
    }
    return grid_size;
}

