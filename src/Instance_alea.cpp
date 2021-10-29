#include "../include/Instance_alea.hpp"

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
/**************************************** CONSTRUCTORS ****************************************/
Instance_alea::Instance_alea(const int capt, const int com, const int k) : Instance(capt,com,k)
{
    cibles = vector< pair<float,float> >();
    init_dist(cibles);
}
/**
 * @brief Construct a new Instance_alea::Instance_alea object
 * 
 * @param instance_name 
 * @param capt 
 * @param com 
 * @param k 
 */
Instance_alea::Instance_alea( const string instance_name, const int capt, const int com, const int k)
                                :Instance(capt,com,k){
    //Lecture grid_size
    vector<string> tab;
    tokenize(instance_name, '_', tab);
    grid_size = stoi(tab[1]);
    width_bit_mask = (0.5*grid_size);

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
/**********************************************************************************************/

/**
 * @brief return a set of identity whose captor are under the mask region
 * 
 * @param x 
 * @param y 
 * @return vector<int> 
 */
void Instance_alea::bit_mask(float x, float y, vector<int>& result)const {
    bool x_in, y_in = false;

    for(uint i=0; i<cibles.size(); i++){

        x_in = cibles[i].first >= x && cibles[i].first <= x+this->width_bit_mask;
        y_in = cibles[i].second >= y && cibles[i].second <= y+this->width_bit_mask;
        if(x_in && y_in){
            result.push_back(i);
        }
    }
}
/**************************************************************************/

/********* fonctions externes ***************************/ 
ostream& Instance_alea::print(ostream& stream) const{
    stream << "list of targets : [" << endl;
    for(int i=0; i<int(cibles.size()); i++){
        stream << "#" << i << "=("  << cibles[i].first;
        stream << ","               << cibles[i].second << ")\t";
        
        if(i%grid_size == grid_size-1) stream << endl;
    }
    stream << "]" << endl;

    return stream;
}
ostream& operator<<(ostream& stream, const Instance_alea& inst){
    inst.Instance::print(stream);
    inst.print(stream);
    return stream;
}