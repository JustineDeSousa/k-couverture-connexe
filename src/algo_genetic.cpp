#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, Solution& best_sol, Selection selection, float rep_rate){
    //Population initiale de taille N
    int N = pop.size();
    int nb_indiv_parents= rep_rate*N;
    cout << "new_generation nb_indiv_parents: " <<nb_indiv_parents<<endl;
    
    //Population de reproducteurs de taille rep_rate*N
    Population parents;
    pop.selection(parents, nb_indiv_parents, selection);
    cout << "parents.size() : " << parents.size() << endl;

    //Population enfant de taille (rep_rate*N)!
    cout << "*****CROSS_OVER\n";
    Population enfants;

    for(Solution P1 : parents){
        for(Solution P2 : parents){
            if( P1 == P2) continue; 
            Solution E1(P1); Solution E2(P2);
            cross_over(P1, P2, E1, E2);
            cout << endl << "E1 : " << E1.fitness() << " " << "E2 : " << E2.fitness() << endl;
            enfants.push_back(E1);
            enfants.push_back(E2);

        }
    }
    pop = parents;
    int nb_indiv_enfants = N - pop.size(); // (1-rep_rate)*N;
    cout << "nb_indiv_enfants="<<nb_indiv_enfants<<endl;
    enfants.selection(pop,nb_indiv_enfants, selection); //Les meilleurs enfants vont dans pop (après les parents)

    Solution pop_best = pop.best_individual();
    cout << "pop.best_individual() fit= " <<  pop_best.fitness() << endl;
    if( pop_best < best_sol ){
        best_sol = pop_best;
        cout << "best_sol_fitness() = " << best_sol.fitness() << endl;
        // pop.push_back(best_sol); //TODO: ajouter vest sol dans nouvelle pop
    }
    //Nouvelle génération de taille N = rep_rate*N parents + (1-rep_rate)*N enfants
    cout <<"new population size=" << pop.size()<<endl;
    cout << "********************\n";
}


void genetic_algo(Population& pop, Solution& best_sol, float maximum_duration, Selection selection, float rep_rate){
    cout << "\n******************** Genetic algorithm ********************\n";
    //best_sol = pop.best_individual();
    cout<<"pop best_individual fit = "<<pop.best_individual().fitness() << endl;
    cout << "best_sol fit= " << best_sol.fitness() << endl;
    clock_t time_begin = clock();
    int nb_iter = 0;
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*maximum_duration ){ // while( durée < min_max min)
        cout << "*********************** Iteration " << nb_iter << endl;
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