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

void lecture_instance_alea( const string instanceName, vector< pair<float,float> > &res, int &grid_size){
    string filename = "instances/" + instanceName + ".dat";
    ifstream file(filename, ios::in);
    if(file){
        string line;
        while( getline(file, line) ) //Tant qu'on n'est pas à la fin, on lit
        {
            vector<string> tab;
            tokenize(line, ' ', tab);
            res.push_back( make_pair(stof(tab[1]), stof(tab[2])) );
        }
        grid_size = res.size();
    }
}

void lecture_instance_tronc( const string instanceName, vector< pair<float,float> > &res, int &grid_size){
    string filename = "instances/" + instanceName + ".dat";
    ifstream file(filename, ios::in);
    if(file){
        string line;
        vector< pair<int,int> > to_be_deleted;
        file >> line >> line >> line >> line >> line >> line;
        line = string (1,line[2]) + string(1,line[3]) + string(1,line[4]);
        grid_size = stoi(line);
        getline(file, line);
        getline(file, line);
        getline(file, line);
        int i=1;
        while( getline(file, line) ){
            if( i < 10 ){
                int x = (int)line[6] - 48;
                int y = (int)line[9] - 48;
                to_be_deleted.push_back( make_pair(x,y) );
            }else{
                int x = (int)line[7] - 48;
                int y = (int)line[10] - 48;
                to_be_deleted.push_back( make_pair(x,y) );
            }
            i++;
            pair<int,int> jl;
            for( int j=0; j<10; j++ ){
                for(int l=0; l<10; l++){
                    jl = make_pair( j,l );
                    for( auto elmt : to_be_deleted ){
                        if( elmt != jl ){
                            res.push_back( jl );        
                        }
                    }
                }
            }
        }
    }
}