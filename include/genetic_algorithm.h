#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <string>
#include <utility>
#include <vector>

#include "sample.h"
#include "individual.h"

using std::pair;
using std::string;
using std::vector;

bool fitness_descending_sort(individual& a, individual& b);

extern vector<sample> training_samples;
extern vector<sample> validating_samples;

struct genetic_algorithm{
	static const int ELITE_SIZE = 10;
	static const int POPULATION_SIZE = 100;
	static constexpr double MUTATION_PROBABILITY = 0.2;
	static vector<individual> population;

	static void create_population();

	static void evaluate_population();

	static void cross();

	static void mutate();

	static pair<individual, individual> crossover(individual a, individual b);

	static void run();

	static void run_validation(individual& ind);
	
	static void print_elite(int gen);
};

#endif