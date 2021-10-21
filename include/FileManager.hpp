#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void tokenize(std::string const &str, const char delim, vector<std::string> &out);
void lecture_instance_alea( const string instanceName, vector< pair<float,float> > &res, int&);
void lecture_instance_tronc( const string instanceName, vector< pair<float,float> > &res, int&);