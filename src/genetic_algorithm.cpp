#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <map>
#include <fstream>

#include "genetic_algorithm.h"
#include "individual.h"
#include "random_util.h"
#include "winrate_lookup_table.h"

using std::ifstream;
using std::endl;
using std::cout;
using std::make_pair;
using std::max;
using std::pair;
using std::vector;
using std::swap;
using std::map;

vector<sample> training_samples{};
vector<sample> validating_samples{};

vector<individual> genetic_algorithm::population;

bool fitness_descending_sort(individual& a, individual& b){
	return a.fitness > b.fitness;
}

void genetic_algorithm::create_population(){
	for(int i = 0; i < POPULATION_SIZE; i++){
		population.push_back(individual());
	}
}

void genetic_algorithm::evaluate_population(){
	for(auto& ind : population){
		//cout << "calculating fitness of " << x++ << endl;
		ind.calculate_fitness(training_samples);
	}
	////cout << "all fitnesses calculated." << endl;
	sort(population.begin(), population.end(), fitness_descending_sort);
	//cout << "everything sorted" << endl;
}

void genetic_algorithm::cross(){
	for(int i = ELITE_SIZE; i < POPULATION_SIZE; i+=2){
		int i1 = rand_range(0, ELITE_SIZE), i2 = rand_range(0, ELITE_SIZE);
		pair<individual, individual> crossed = crossover(population[i1], population[i2]);
		population[i] = crossed.first;
		population[i+1] = crossed.first;
	}
}

void genetic_algorithm::mutate(){
	for(auto& ind : population){
		if(rand_rangef(0, 1) < MUTATION_PROBABILITY){
			ind.mutate();
		}
	}
}

pair<individual, individual> genetic_algorithm::crossover(individual a, individual b){
	int i = rand_range(0, (int)a.chromosome.size());
	int j = rand_range(0, (int)a.chromosome.size());
	if(i > j) swap(i, j);
	pair<individual, individual> ret = {a, b};
	for(; i <= j; i++) {
		swap(ret.first.chromosome[i], ret.second.chromosome[i]);
	}
	return ret;
}

void genetic_algorithm::run(){
	int generation = 0;
	create_population();
	cout << "population created." << endl;
	evaluate_population();
	cout << "population evaluated." << endl;
	while(generation < 1000){
		print_elite(generation+1);
		run_validation(population[0]);
		cross();
		cout << "population crossed." << endl;
		mutate();
		cout << "population mutated." << endl;
		evaluate_population();
		cout << "population evaluated." << endl;
		generation++;
	}
	cout << "best individual: \n";
	cout << "individual({";
	for(int i = 0; i < (int)population[0].chromosome.size(); i++){
		cout << "{" << population[0].chromosome[i].first << ", " << population[0].chromosome[i].second << "}, ";
	}
	cout << "});\n";
}

void genetic_algorithm::run_validation(individual& ind){
	cout << "running validating samples for best individual:" << endl;
	ind.calculate_fitness(validating_samples);
	cout << "fitness of best individual: " << ind.fitness*100 << "%" << endl;
}

void genetic_algorithm::print_elite(int gen){
	cout << "Generation " << gen << endl;
	for(int i = 0; i < ELITE_SIZE; i++){
		cout << "\t" << i+1 << "º: " << population[i].fitness*100 << "%" << endl;
	}
}

void read_sample_file(std::string file_path, vector<sample>& samples){
	std::ifstream in(file_path);
	
	using std::cin;
	
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	int winner;
	int match_id;
	while(cin >> winner){
		cin >> match_id;
		vector<int> t1;
		vector<int> t2;
		int a = 0;
		for (int i = 0; i < 5; i++){
			cin >> a;
			t1.push_back(a);
		}
		for(int i = 0; i < 5; i++){
			cin >> a;
			t2.push_back(a);
		}
		samples.emplace_back(t1, t2, winner);
	}

	cin.rdbuf(cinbuf);
}