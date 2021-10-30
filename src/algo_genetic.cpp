#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, Solution& best_sol, Selection selection, float rep_rate){
    //Population initiale de taille N
    int N = pop.size();
    int nb_indiv_parents= rep_rate*N;
    
    //Population de reproducteurs de taille rep_rate*N
    Population parents;
    pop.selection(parents, nb_indiv_parents, selection);
    cout << "POPULATION PARENTS: " << parents.size() << " INDIVIDUS : " << endl;

    //Population enfant de taille (rep_rate*N)!
    cout << "*****CROSS_OVER\n";
    Population enfants;

    for(Solution P1 : parents){
        for(Solution P2 : parents){
            if( P1 == P2) continue; 
            Solution E1(P1); Solution E2(P2);
            cross_over(P1, P2, E1, E2);
            // cout << endl << "E1 : " << E1.fitness() << " " << "E2 : " << E2.fitness() << endl;
            enfants.push_back(E1);
            enfants.push_back(E2);

        }
    }
    
    // When parents are homogene, enfants is empty
    // we search neighbour solutions
    if(enfants.size() == 0){ 
        cout << "PARENT IDENTIQUES" << endl;
        set<vector<bool>> neighbours_sol; 
        neighbour_solution(parents[0], ( N - parents.size()), neighbours_sol); //TODO : potential PB if N is too big
        
        set<vector<bool>>::const_iterator it = neighbours_sol.begin();
        for(; it != neighbours_sol.end(); it++) {
            enfants.push_back(Solution( (*it) ) );
        }
    }
    cout << "********************\n"; //fin du cross_over
    cout << "*****MUTATION\n";
    for (int i = 0; i < enfants.size(); i++)
    {
        enfants[i].mutation(0.05); //TODO : mute proba à voir
    }
    cout << "********************\n"; //fin MUTATION
    cout << "POPULATION ENFANTS: " << enfants.size() << " individus : " << endl;

    pop = parents;
    Solution best_child = enfants.best_individual();
    if( best_child < best_sol ){ // Soit enfants évoluent 
        best_sol = enfants.best_individual();
        cout << "EVOLUÉ !!! best_sol_fitness() = " << best_sol.fitness() << endl;
        pop.push_back(best_sol); 

    }else if( best_sol < pop.best_individual()){ // soit ils s'améliore pas
        pop.push_back(best_sol);
        cout << "NON EVOLUE best_fit= "<< best_sol.fitness() << endl;
    }
    int nb_indiv_enfants = N - pop.size(); // (1-rep_rate)*N;
    enfants.selection(pop,nb_indiv_enfants, selection); //Les meilleurs enfants vont dans pop (après les parents)
    //Nouvelle génération de taille N = rep_rate*N parents + (1-rep_rate)*N enfants
}


void genetic_algo(Population& pop, Solution& best_sol, float maximum_duration, Selection selection, float rep_rate){
    cout << "\n******************** Genetic algorithm ********************\n";
    
    cout << "BEST SOL : FITNESS = " << best_sol.fitness() << endl;
    cout << "        NB_CAPTORS = " << best_sol.nb_capteurs() << endl;
    cout << best_sol << endl;

    clock_t time_begin = clock();
    int nb_iter = 0;
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*maximum_duration ){ // while( durée < min_max min)
        cout << "*********************** Iteration " << nb_iter << " ***********************\n";
        cout << "POP : " << pop.size() << " INDIVIDUS -- BEST FIT = " << best_sol.fitness() << endl;
        cout << "\t\t   NB_CAPTORS = " << best_sol.nb_capteurs() << endl;
        new_generation(pop, best_sol, selection, rep_rate);
        
        cout << "***********************************************************\n";
        nb_iter++;
    }
    cout << double(clock()-time_begin)/CLOCKS_PER_SEC << "s";
    cout << " -- BEST INDIVIDUAL : FITNESS = " << best_sol.fitness() << endl;
    cout << "                   NB_CAPTORS = " << best_sol.nb_capteurs() << endl;
    cout << best_sol;
    cout << "SOLUTION REALISABLE  : " << boolalpha << best_sol.is_realisable() << endl;
    //TODO : heuristique de réparation
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