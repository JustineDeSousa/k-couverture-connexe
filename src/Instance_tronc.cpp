#include "../include/Instance_tronc.hpp"

/***************************** CONSTRUCTEUR *****************************/
Instance_tronc::Instance_tronc(const int capt, const int com) : Instance(capt,com)
{
    cibles = vector< pair<int,int> >();
    init_dist(cibles);
}
Instance_tronc::Instance_tronc( const string instance_name, const int capt, const int com) : Instance(capt,com)
{
    string filename = "./instances/" + instance_name + ".dat";
    //cout << "Instance_tronc:: Lecture du fichier " << filename << endl;
    ifstream file(filename, ios::in);
    
    vector<int> x,y;
    if(file.is_open()){
        string token;
        
        file >> token >> token >> token >> token >> token >> token;
        grid_size = sqrt( stoi(token.substr(2,token.size()-3)) );
        width_bit_mask = (0.5*grid_size);


        file >> token >> token >> token >> token >> token;
        int nb_lines = stoi( token.substr(2,token.size()-3) );

        getline(file, token);
        getline(file, token);

        //On récupère les points à supprimer
        for(int i=0; i<nb_lines; i++ ){
            file >> token >> token >> token;
            x.push_back( stoi( token.substr(1,token.size()-2) ) );

            file >> token;
            y.push_back( stoi( token.substr(0,token.size()-1) ) );
        }
        file.close();
    }else{
        cerr <<("Couldn't open file : " + filename).c_str() << endl;
        exit(-1);
    }
    // Initialisation de la grille
    bool to_del = false;
    for( int i=0; i<grid_size; i++ ){
        for(int j=0; j<grid_size; j++){
            to_del = false;
            //is (i,j) to be deleted ?
            for( unsigned int l=0; l<x.size(); l++ ){
                if( x[l]==i && y[l]==j ){
                    to_del = true; 
                }
            }
            if(!to_del){
                cibles.push_back( make_pair(i,j) );
            }
        }
    }
    //Calcul de la matrice des distances
    init_dist(cibles);
}
/**************************************************************************/

/******************* OPERATIONS POUR CROSSOVER MUTATION *******************/
void Instance_tronc::bit_mask(float x, float y, vector<int>& result) const {
    bool x_in = false;
    bool y_in = false;
    for(uint i=0; i<cibles.size(); i++){
        x_in = cibles[i].first >= x && cibles[i].first <= x+this->width_bit_mask;
        y_in = cibles[i].second >= y && cibles[i].second <= y+this->width_bit_mask;
        if(x_in && y_in){
            result.push_back(i);
        }
    }
}
/**************************************************************************/
/******************************* AFFICHAGE ********************************/
ostream& Instance_tronc::print(ostream& stream) const{
    stream << "list of targets : [" << endl;
    for(int i=0; i<int(cibles.size()); i++){
        stream << "#" << i << "=("  << cibles[i].first;
        stream << ","               << cibles[i].second << ")\t";
        
        if(i%grid_size == grid_size-1) stream << endl;
    }
    stream << "]" << endl;

    return stream;
}
ostream& operator<<(ostream& stream, const Instance_tronc& inst){
    inst.Instance::print(stream);
    inst.print(stream);
    return stream;
}
/**************************************************************************/