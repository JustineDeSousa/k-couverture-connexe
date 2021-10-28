#include "../include/algo_genetic.hpp"

void new_generation(Population& pop, float rep_rate){
    int N = pop.size();
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

void genetic_algo(Population& pop, float maximum_duration, float rep_rate){
    int N = pop.size();
    clock_t time_begin = clock();
    while( double(clock() - time_begin)/CLOCKS_PER_SEC < 60*maximum_duration ){ // while( durée < min_max min)
        new_generation(pop, rep_rate);
    }
    cout << double(clock()-time_begin)/CLOCKS_PER_SEC << "s -- BEST INDIVIDUAL : " << pop.best_individual() << endl;
}