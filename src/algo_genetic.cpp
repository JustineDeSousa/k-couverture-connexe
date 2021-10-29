#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, Solution& best_sol, Selection selection, float rep_rate){
    int N = pop.size();     //Population initiale de taille N
    int nb_indiv_parents= rep_rate*N;
    cout << "new_generation nb_indiv_parents: " <<nb_indiv_parents<<endl;
    
    Population parents;
    pop.selection(parents, nb_indiv_parents, selection);
    cout << "parents.size() : " << parents.size() << endl;

    cout << "APRES SELECT parents.size() = " << parents.size() << endl;

    for(int i=0; i<parents.size(); i++){
        cout << "parents[" << i << "] fit = " << parents[i].fitness() << " ";
    }cout << endl;


    //Population enfant de taille (rep_rate*N)!
    cout << "*****CROSS_OVER\n";
    Population enfants;

/*
    do
    {
       
    } while (enfants.size() == 0);
*/
    

    for(Solution P1 : parents){
        for(Solution P2 : parents){
            if( P1 == P2) continue; 
            Solution E1(P1); Solution E2(P2);
            cross_over(P1, P2, E1, E2);
            //cout << endl << "E1 : " << E1.fitness() << " " << "E2 : " << E2.fitness() << endl;
            enfants.push_back(E1);
            enfants.push_back(E2);

        }
    }


    //TODO : mutation

    pop = parents;
    if(enfants.size() == 0){ 
        cout << "PARENT IDENTIQUES" << endl; 
        //cerr << "ERROR : cas homogène ! " << endl;
        //exit(-1);
    }
    
    cout << "enfants.best_individual() fit= " <<  enfants.best_individual().fitness() << endl;

    if( enfants.best_individual() < best_sol ){ // Soit enfants évoluent 
        best_sol = enfants.best_individual();
        cout << "EVOLUÉ !!! best_sol_fitness() = " << best_sol.fitness() << endl;
        pop.push_back(best_sol); 

    }else if( best_sol < pop.best_individual()){ // soit ils s'améliore pas
        pop.push_back(best_sol);
        cout << "NON EVOLUE best_fit= "<< best_sol.fitness() << endl;
    }

    //Nouvelle génération de taille N = rep_rate*N parents + (1-rep_rate)*N enfants
    //cout << "\n*****SELECTION DES PARENTS\n";

    // for(int i=0; i<pop.size(); i++){
    //     cout << "pop[" << i << "] = " << pop[i].fitness() << " ";
    // }
    cout << "\n*****SELECTION DES ENFANTS\n";
    // for(int i=0; i<enfants.size(); i++){
    //     cout << "enfants[" << i << "] = " << enfants[i].fitness() << " ";
    // }cout << endl;

    int nb_indiv_enfants = N - pop.size(); // (1-rep_rate)*N;
    cout << "nb_indiv_enfants="<<nb_indiv_enfants<<endl;

    enfants.selection(pop, nb_indiv_enfants, selection);
    cout <<"new population size=" << pop.size()<<endl;
    cout << "*******************************************\n";
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