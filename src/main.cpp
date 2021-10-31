
#include "../include/Instance.hpp"
#include "../include/Instance_tronc.hpp"
#include "../include/Instance_alea.hpp"
#include "../include/Solution.hpp"
#include "../include/algo_genetic.hpp"
#include "../include/file_manager.hpp"
using namespace std;

const Instance* Solution::instance;
int MAX_VIE = 50 ;


bool run(string full_name, float& best, float& average, float& average_ite){

    // we run 5 times and we compare the best sol ever, and the average sol
    Population recorder_sol;
    int sum_v = 0;
    int total_nb_ite = 0;

    for (int i = 1; i <= 5; i++) //TODO : à changer
    {
        cout << endl << "run i : " << i;
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

        cout << ", sol heuristic = " << best_sol.nb_capteurs() << endl;

        // run the genetic algo
        int ite = 0;
        ite = genetic_algo(pop, best_sol, minitues, Selection::ELITE, percentage_parents); //TODO : 3 min / ELITE, ROULETTE

        cout << "; sol algo genetic = " << best_sol.nb_capteurs() << " is feasible : " << best_sol.is_realisable() << endl;
        if(best_sol.is_realisable()) {
            recorder_sol.push_back(best_sol);
            total_nb_ite += ite;
        }
    }

    if(recorder_sol.size() == 0){
        cout << "No feasible solution found :(" << endl;
        return false;
    }

    Solution best_sol_ever = recorder_sol.best_individual();
    for(int i = 0; i< recorder_sol.size(); i++) { sum_v += recorder_sol[i].nb_capteurs(); }
    average = sum_v / recorder_sol.size();
    average_ite = total_nb_ite/recorder_sol.size();
    best = best_sol_ever.nb_capteurs();

    write_solution(best_sol_ever, full_name, average, average_ite);
    cout << endl;
    return true;
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
    cout << endl << "Input file name : " <<instance_name;


    if(instance_name[0] == 'c'){ // instances aléatoires
        for (int K = 1; K <= 3; K++)
        {
            for (int Rcapt = 1; Rcapt <= 2; Rcapt++)
            {
                for (int Rcom = Rcapt; Rcom <= Rcapt+1; Rcom++)
                {   
                    Instance_alea inst_alea(instance_name, Rcapt, Rcom, K);
                    Solution::instance = &inst_alea;
                    stringstream full_name;
                    full_name << instance_name << "_K" << K << "_" << Rcapt << "_" << Rcom;

                    cout << "  test with " << "K=" << K << ", Rcapt=" << Rcapt << ", Rcom=" << Rcom << endl;

                    ofstream out;
                    out.open("./instances_alea.tex", ios::app);

                    stringstream ss_(instance_name);
                    string s_;

                    while(getline(ss_, s_, '_'))
                    {
                        out << s_ << "\\_" ;
                    }

                    float best; float average; float average_ite;
                    bool success = run(full_name.str(), best, average, average_ite);

                    out << " & " << K << " & " << Rcapt << " & " << Rcom;

                    if(success){
                        out << " & " << best << " & " << average << " & " << average_ite << " \\\\ " << endl;
                    }else{
                        out << " & - & - & - \\\\ " << endl;
                    }
                }  
            }
        }

    }else if(instance_name[0] == 'g'){ // grilles tronquées
        return 0;
        for (int Rcapt = 1; Rcapt <= 2; Rcapt++)
        {
            for (int Rcom = Rcapt; Rcom <= Rcapt+1; Rcom++)
            {
                Instance_tronc inst_tronc(instance_name, Rcapt, Rcom);
                Solution::instance = &inst_tronc;
                stringstream full_name;
                full_name << instance_name << "_K1"<< "_" << Rcapt << "_" << Rcom;
                cout << "  test with " << "K=1"<< ", Rcapt=" << Rcapt << ", Rcom=" << Rcom << endl;

                ofstream out;
                out.open("./instances_grilles.tex", ios::app);

                stringstream ss_(instance_name);
                string s_;

                while(getline(ss_, s_, '_'))
                {
                    out << s_ << "\\_" ;
                }

                float best; float average; float average_ite;
                bool success = run(full_name.str(), best, average, average_ite);

                out << " & " << Rcapt << " & " << Rcom;

                if(success){
                    out << " & " << best << " & " << average << " & " << average_ite << " \\\\ " << endl;
                }else{
                    out << " & - & - & - \\\\ " << endl;
                }
            }  
        }
    }

}



void repare(Solution & sol){
    // reparation pour k-couvertur
    vector<int> cibles_notfully_capted; // identifiant

    map<int, vector<int>> candidates; //cible => l'ensemble de cible peut être ajouter


    vector<int> candidates_required; // each cible => nombre demandé par candidates

    // ajouter les captors de l'ordre décroissant du candidates_required
    // jusqu'a k couverture safisfied

    // si n'est pas connexe  


}