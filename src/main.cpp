
#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/algo_genetic.hpp"
#include "../include/file_manager.hpp"
#include <algorithm> 
#include <cstdlib>
#include <ctime>
using namespace std;

const Instance* Solution::instance;
int MAX_VIE = 5;//TODO : A changer


void run(string instance_name){

    // we run 5 times and we compare the best sol ever, and the average sol
    Population recorder_sol;
    int sum_v = 0;

    for (int i = 1; i <= 5; i++) //TODO : à changer
    {
        int N = 100; // size of one generation
        int minitues = 3;
        float percentage_parents = 0.5;

        // generate N different heuristic solution in the initial Population
        Population pop;
        set<vector<bool>> vec;
        while (vec.size() < N)
        {
            Solution sol_heuristic;
            heuristic(sol_heuristic);
            vec.insert( vec.end(), sol_heuristic);
        }
        set<vector<bool>>::const_iterator it = vec.begin();

        for(; it != vec.end(); it++){

            pop.push_back(Solution(*it));
        }

        Solution best_sol = pop.best_individual();
        int fit_init = best_sol.fitness();

        // run the genetic algo
        genetic_algo(pop, best_sol, minitues, Selection::ROULETTE, percentage_parents); //TODO : 3 min / ELITE, ROULETTE

        recorder_sol.push_back(best_sol);
    }

    Solution best_sol_ever = recorder_sol.best_individual();
    for(int i = 0; i< recorder_sol.size(); i++) { sum_v += recorder_sol[i].fitness(); }
    float average = sum_v / recorder_sol.size();

    write_solution(best_sol_ever, instance_name, average);
}



int main(int argc, char** argv){
    srand (static_cast <unsigned> (time(0)));


    // Check the number of parameters
    if (argc < 2) {
        cerr<< "No input file" << endl;
        exit(-1);
    }
    string fname = argv[1];
    vector<string> seglist;
    stringstream ss(fname);
    string s;

    while(getline(ss, s, '/'))
    {
        seglist.push_back(s);
    }

    string instance_name = seglist[2].substr(0, seglist[2].size()-4);
    cout << "Input file name : " <<instance_name << endl;


    if(instance_name[0] == 'c'){ // instances aléatoires
        for (int K = 1; K <= 3; K++)
        {
            for (int Rcapt = 1; Rcapt <= 2; Rcapt++)
            {
                for (int Rcom = Rcapt; Rcom <= 3; Rcom++)
                {
                    Instance_alea inst_alea(instance_name, Rcapt, Rcom, K);
                    Solution::instance = &inst_alea;
                    run(instance_name);
                }  
            }
        }

    }else if(instance_name[0] == 'g'){ // grilles tronquées
        for (int Rcapt = 1; Rcapt <= 2; Rcapt++)
        {
            for (int Rcom = Rcapt; Rcom <= 3; Rcom++)
            {
                Instance_tronc inst_tronc(instance_name, Rcapt, Rcom);
                Solution::instance = &inst_tronc;
                run(instance_name);
            }  
        }
    }

/*
    
    //cout << endl << "TEST INSTANCE TRONQUEE" << endl;
    string instance_name = "captANOR150_7_4"; // grille1010_1
    Instance_alea inst_alea(instance_name);
    Solution::instance = &inst_alea;

    //Instance_tronc inst_tronc(instance_name);
    //Solution::instance = &inst_tronc;


    cout << "\n\n***************************************** TEST GENETIC *****************************************" << endl;
    int N = 100; //TODO : 100
    Population pop;
    set<vector<bool>> vec;
    while (vec.size() < N)
    {
        Solution sol_heuristic;
        heuristic(sol_heuristic);
        vec.insert( vec.end(), sol_heuristic);
    }
    set<vector<bool>>::const_iterator it = vec.begin();

    for(; it != vec.end(); it++){

        pop.push_back(Solution(*it));
    }
    Solution best_sol = pop.best_individual();
    int fit_init = best_sol.fitness();


    genetic_algo(pop, best_sol, 3, Selection::ELITE, 0.5); //TODO : 3 min / ELITE, ROULETTE
    cout << "fit au départ = " << fit_init << endl;

*/
}