#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

//#define eof "EOF"

using namespace std;

void tokenize(std::string const &str, const char delim, vector<std::string> &out);
int lecture_instance_alea( const string instanceName, vector< pair<float,float> > &res);
int lecture_instance_tronc( const string instanceName, vector< pair<int,int> > &res);