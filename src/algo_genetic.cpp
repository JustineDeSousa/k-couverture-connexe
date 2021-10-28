#include "../include/algo_genetic.hpp"

void new_generation(const Instance* const inst, Population& pop, int N, float rep_rate){
    //TODO garder le meilleur individu
    //Population initiale de taille N

    //Population de reproducteurs de taille rep_rate*N
    Population parents;
    pop.selection(parents,rep_rate*N);

    //Population enfant de taille (rep_rate*N)!
    Population enfants;
    Solution E1, E2;
    for(Solution P1 : parents){
        for(Solution P2 : parents){
            if( P1 == P2) continue;
            cross_over(P1, P2, E1, E2);
            enfants.push_back(E1);
            enfants.push_back(E2);
        }
    }

    //Nouvelle génération de taille N = rep_rate*N parents + (1-rep_rate)*N enfants
    pop = parents;
    enfants.selection(pop,(1-rep_rate)*N);
}

void genetic_algo(const Instance* const inst, Population& pop, float min_max, int N=100, float rep_rate=0.1){
    clock_t time_begin = clock();
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*min_max ){ // while( durée < min_max min)
        new_generation(inst, pop, N, rep_rate);
    }
    cout << double(clock()-time_begin)/CLOCKS_PER_SEC << "s -- BEST INDIVIDUAL : " << pop.best_individual() << endl;
}




void heuristic(Solution& sol){// should be a default solution placing captors at every targets except the sink
    //vector<bool> visited(Solution::instance->size(), false);
    sol.update_graphs(); // init graphs

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