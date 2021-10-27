#include "algo_genetic.hpp"

void new_generation(const Instance* const inst, Population& pop, int N, float rep_rate){
    //Population initiale de taille N

    //Population de reproducteurs de taille rep_rate*N
    Population parents(inst);
    pop.selection(parents,rep_rate*N);

    //Population enfant de taille (rep_rate*N)!
    Population enfants(inst);
    Solution E1(inst), E2(inst);
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