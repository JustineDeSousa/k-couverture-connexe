#ifndef ALGO_GENETIQUE_HPP
#define ALGO_GENETIQUE_HPP

#include "Population.hpp"

// N = taille de la population
// rep_rate = taux de reproducteurs
void new_generation(const Instance* const inst, Population& pop, int N=100, float rep_rate=0.1);

void genetic_algo(const Instance* const inst, Population& pop, int N=100, float rep_rate=0.1);



void heuristic(Solution& sol);

#endif