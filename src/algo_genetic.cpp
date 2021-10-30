#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, Solution& best_sol, Selection selection, float rep_rate){
    pop.generation_older();

    int N = pop.size();     //Population initiale de taille N
    int nb_indiv_parents= rep_rate*N;
    //cout << "new_generation nb_indiv_parents: " <<nb_indiv_parents<<endl;

    Population parents;
    pop.selection(parents, nb_indiv_parents, selection);
    //cout << "APRES SELECT parents.size() = " << parents.size() << endl;

    for(int i=0; i<parents.size(); i++){
        //cout << "parents[" << i << "] fit = " << parents[i].fitness() << " ";
    }
    //cout << endl;

    //Population enfant de taille (rep_rate*N)!
    //cout << "*****CROSS_OVER\n";
    Population enfants;

    for(Solution P1 : parents){
        for(Solution P2 : parents){ 
            if( vector<bool>(P1) == vector<bool>(P2)) continue; 
            Solution E1(P1); Solution E2(P2);
            cross_over(P1, P2, E1, E2);
            E1.reset_vie(); E2.reset_vie(); // new babies born and reset vie=0
            enfants.push_back(E1);
            enfants.push_back(E2);

            if(enfants.size() >= N) {break;}
        }
    }

    // When parents are homo, enfants is empty
    // we search neighbour solutions
    if(enfants.size() == 0){ 
        //cout << "PARENT IDENTIQUES" << endl; 

        set<vector<bool>> neighbours_sol; 
        neighbour_solution(parents[0], ( N - parents.size())*2, neighbours_sol); //TODO : potential PB if N is too big
        
        set<vector<bool>>::const_iterator it = neighbours_sol.begin();
        for(; it != neighbours_sol.end(); it++) {
            enfants.push_back(Solution( (*it) ) ); // constructor by vector<bool>, vie=0
        }
    }

    //cout << "*****MUTATION\n";
    for (int i = 0; i < enfants.size(); i++)
    {
        enfants[i].mutation(0.05); //TODO : mute proba à voir
    }


    pop = parents;

    if( enfants.best_individual() < best_sol ){ // Soit enfants évoluent 
        best_sol = enfants.best_individual();
        pop.push_back(best_sol); 

    }

    //cout << "\n*****SELECTION DES ENFANTS\n";
    int nb_indiv_enfants = N - pop.size(); 
    //cout << "nb_indiv_enfants="<<nb_indiv_enfants<<endl;

    enfants.selection(pop, nb_indiv_enfants, selection);
    //cout <<"new population size=" << pop.size()<<endl;


    // delete solutions too old
    pop.delete_old_sols();
    //cout << "APRES  pop delete_old_sols size = " << pop.size() << endl;

    if(pop.size() < N){
        int nb_new = N - pop.size();
        set<vector<bool>> neighbours_sol;
        neighbour_solution(best_sol, nb_new , neighbours_sol);

        for (set<vector<bool>>::const_iterator it = neighbours_sol.begin(); it!=neighbours_sol.end(); it++)
        {
            pop.push_back(Solution( (*it)));
        }

        if(pop.best_individual() < best_sol) {best_sol = pop.best_individual();}
        
    }
    best_sol.reset_vie();
    //cout << "Fin itération pop size = " << pop.size() << endl;
    //cout << "*******************************************\n";
}


void genetic_algo(Population& pop, Solution& best_sol, float maximum_duration, Selection selection, float rep_rate){
    //cout << "\n******************** Genetic algorithm ********************\n";
    //cout<<"pop best_individual fit = "<<pop.best_individual().fitness() << endl;
    //cout << "best_sol fit= " << best_sol.fitness() << endl;

    clock_t time_begin = clock();
    int nb_iter = 0;
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*maximum_duration ){ // while( durée < min_max min)
        //cout << "*************************** Iteration " << nb_iter << endl;
        new_generation(pop, best_sol, selection, rep_rate);
        nb_iter++;
    }
    double total_time = double(clock()-time_begin)/CLOCKS_PER_SEC;
    //cout <<  total_time << " (s) -- BEST INDIVIDUAL : " << best_sol << endl;
    //cout << "best_sol.is_realisable : " << best_sol.is_realisable() << endl;
    //cout << "with fit = " << best_sol.fitness() << endl;

}



/**
 * @brief Generate an heuristic solution by deleting captors randomly
 * 
 * @param sol 
 */
void heuristic(Solution& sol){// should be a default solution placing captors at every targets except the sink

    set<int> available_bits;
    for (int i = 0; i < Solution::instance->size(); i++) available_bits.insert(available_bits.end(), i);

    // find(visited.begin(), visited.end(), false) != visited.end()
    while ( available_bits.size() >0)// exists at least one target not visited
    {   
        int r = rand()%(available_bits.size()); // a position between 0 and size()-1

        int bit = *next(available_bits.begin(), r); 

        available_bits.erase(available_bits.find(bit));

        if(!sol[bit]) continue; // target bit is not captor => sol[bit]=0

        sol.reverse(bit, true); // update the graph also

        if(!sol.is_graph_com_connected() || !sol.is_k_covered()){// if removing target bit violates constraint NOT realisable

            sol.reverse(bit, true); // undo
        }
    }
}


/**
 * @brief Given a solution, we return n different solutions but having the same number of captors as given
 * Also called "Structure Voisinage"
 * 
 * @param sol 
 * @param n 
 * @param neighbours_sol 
 */
void neighbour_solution(const Solution& sol, int n, set<vector<bool>>& neighbours_sol){
    vector<bool> sol_ = sol;
    neighbours_sol = set<vector<bool>>(); // an empty set
    int nb_capt = sol.nb_capteurs();

    do
    {
        vector<bool> v(sol.size(), 0);

        // select captors 
        for (int i = 0; i < nb_capt; i++)
        {
            int r = rand()%(sol.size()); // a position between 0 and size()-1
            if(v[r]) {i--; continue;} // if r already is captor

            v[r] = 1;
        }

        if (accumulate(v.begin(),v.end(),0) != nb_capt) {
            cerr << "neighbour_solution is wrongly generated ! "<< endl;
            exit(-1);
         }

        if(v != sol_) { neighbours_sol.insert(neighbours_sol.end(), v); }
        
    } while (neighbours_sol.size() != n);
    
}