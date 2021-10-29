#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, Solution& best_sol, Selection selection, float rep_rate){
    //Population initiale de taille N
    int N = pop.size();
    
    //Population de reproducteurs de taille rep_rate*N
    Population parents;
    pop.selection(parents,rep_rate*N,selection);

    //Population enfant de taille (rep_rate*N)!
    cout << "*****CROSS_OVER\n";
    Population enfants;
    
    for(Solution P1 : parents){
        for(Solution P2 : parents){
            if( P1 == P2){continue;} 
            Solution E1;
            Solution E2;
            cross_over(P1, P2, E1, E2);
            cout << "E1 : " << E1.fitness() << " " << "E2 : " << E2.fitness() << endl;
            enfants.push_back(E1);
            enfants.push_back(E2);
        }
    }
    cout <<  enfants.best_individual() << endl;
    if( enfants.best_individual() < best_sol ){
        best_sol = enfants.best_individual();
        cout << "best_sol_fitness() = " << best_sol.fitness() << endl;
    }

    //Nouvelle génération de taille N = rep_rate*N parents + (1-rep_rate)*N enfants
    pop = parents;
    enfants.selection(pop,(1-rep_rate)*N, selection); //Les meilleurs enfants vont dans pop (après les parents)
    cout << "********************\n";
}

void genetic_algo(Population& pop, Solution& best_sol, float maximum_duration, Selection selection, float rep_rate){
    best_sol = pop.best_individual();
    cout << "\n******************** Genetic algorithm ********************\n";
    clock_t time_begin = clock();
    int nb_iter = 0;
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*maximum_duration ){ // while( durée < min_max min)
        cout << "********** Iteration " << nb_iter << endl;
        new_generation(pop, best_sol, selection, rep_rate);
        nb_iter++;
    }
    cout << double(clock()-time_begin)/CLOCKS_PER_SEC << "s -- BEST INDIVIDUAL : " << best_sol << endl;
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