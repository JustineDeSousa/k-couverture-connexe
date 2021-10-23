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
        string line;
        while( getline(file, line) ) //Tant qu'on n'est pas à la fin, on lit
        {
            vector<string> tab;
            tokenize(line, ' ', tab);
            cout<< "( " << tab[1] <<", " << tab[2] << ")"<<endl;
            res.push_back( make_pair(stof(tab[1]), stof(tab[2])) );
        }

    file.close();
    }else{
        cerr <<("Couldn't open file : " + filename).c_str() << endl;
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
    int N = 0;

    if(file.is_open()){
        string line;
        file >> line >> line >> line >> line >> line >> line;
        line = string (1,line[2]) + string(1,line[3]) + string(1,line[4]);
        N = sqrt(stoi(line));

        getline(file, line); getline(file, line); getline(file, line);

        res.push_back(make_pair(0, 0)); // the sink
        
        while( getline(file, line) ){
            int x, y;
            vector<string> tab;
            tokenize(line, ':', tab);

            vector<string> tab2;
            string position = tab[1].substr(2); // 9, 2)
            tokenize(position, ',', tab2);
            x = stoi(tab2[0]);

            string pos2 = tab2[1].substr(1);
            y = stoi(pos2.substr(0, pos2.size()-1));
            cout<< "( " << x <<", " << y<< ")"<<endl;

            res.push_back(make_pair(x, y));
        }
    file.close();
    
    }else{
        cerr <<("Couldn't open file : " + filename).c_str() << endl;
        exit(-1);
    }
    return N;

}