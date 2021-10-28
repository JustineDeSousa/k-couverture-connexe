#ifndef ALGO_GENETIQUE_HPP
#define ALGO_GENETIQUE_HPP

#include "Population.hpp"

// entrée: pop = population génération n 
// rep_rate = taux de reproducteurs
// sortie: pop = population generation n+1
void new_generation(Population& pop, float rep_rate=0.1);
// param entrée: pop = population génération 0
// maximum_duration = durée max d'execution en minutes
// rep_rate = taux de reproducteurs
// sortie: pop = population generation finale 
void genetic_algo(Population& pop, float maximum_duration, float rep_rate=0.1);

#endif