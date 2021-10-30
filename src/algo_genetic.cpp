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
    cout << "********************\n"; //fin du cross_over
    mutation()
    cout << "POPULATION ENFANTS: " << enfants.size() << " individus : " << endl;

    pop = parents;
    int nb_indiv_enfants = N - pop.size(); // (1-rep_rate)*N;
    enfants.selection(pop,nb_indiv_enfants, selection); //Les meilleurs enfants vont dans pop (après les parents)

    Solution pop_best = pop.best_individual();
    if( pop_best < best_sol ){
        best_sol = pop_best;
        cout << "BEST_SOL : FITNESS = " << best_sol.fitness() << endl;
        cout << "        NB_CAPTORS = " << best_sol.nb_capteurs() << endl;
        // pop.push_back(best_sol); //TODO: ajouter vest sol dans nouvelle pop
    }
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