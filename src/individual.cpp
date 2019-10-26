#include <math.h>
#include <utility>
#include <vector>
#include <algorithm>

#include "random_util.h"
#include "individual.h"

using std::make_pair;
using std::max;
using std::pair;
using std::vector;

double sigmoid(double val){
	return 1.0/(1+exp(-val));
}

double relu(double val){
	return max(0.0, val);
}

double individual::activation_function_input(double val){
	return relu(val);
}

double individual::activation_function_output(double val){
	return sigmoid(val);
}

double individual::get_weight_input(int i, int j){
	return chromosome[j*(INPUT_SIZE+OUTPUT_SIZE)+i].first;
}

double individual::get_bias_input(int i, int j){
	return chromosome[j*(INPUT_SIZE+OUTPUT_SIZE)+i].second;
}

double individual::get_weight_output(int i){
	return chromosome[i*(INPUT_SIZE+OUTPUT_SIZE)+INPUT_SIZE].first;
}

double individual::get_bias_output(int i){
	return chromosome[i*(INPUT_SIZE+OUTPUT_SIZE)+INPUT_SIZE].second;
}

int individual::calculate_outcome(vector<double> in){
	vector<double> hidden(HIDDEN_LAYER_SIZE, 0.0);
	for(int i = 0; i < INPUT_SIZE; i++){
		for(int j = 0; j < HIDDEN_LAYER_SIZE; j++){
			hidden[j] += get_weight_input(i, j)*in[i]+get_bias_input(i, j);
		}
	}
	double output = 0;
	for(int i = 0; i < HIDDEN_LAYER_SIZE; i++) {
		output += activation_function_input(hidden[i])*get_weight_output(i) + get_bias_output(i);
	}
	return activation_function_output(output) >= 0.5;
}

void individual::calculate_fitness(const vector<sample>& samples){
	int total = (int)samples.size();
	int correct = 0;
	for(sample s : samples){
		int outcome = calculate_outcome(s.input);
		correct += outcome+1 == s.output;
	}
	this->fitness = correct/(double)total;
}

void individual::mutate(){
	for(int i = 0; i < (int)chromosome.size(); i++){
		if(rand_rangef(0, 1) <= MUTATION_PROBABILITY){
			chromosome[i] = {rand_rangef(MINIMAL_WEIGHT, MAXIMAL_WEIGHT), rand_rangef(MINIMAL_BIAS, MAXIMAL_BIAS)};
		}
	}
}

individual::individual(){
	fitness = -1;
	for(auto& c : chromosome){
		c = {rand_rangef(MINIMAL_WEIGHT, MAXIMAL_WEIGHT), rand_rangef(MINIMAL_WEIGHT, MAXIMAL_WEIGHT)};
	}
}

individual::individual(const vector<pair<double, double>>& c) : chromosome(c), fitness(-1) {}

individual::individual(const individual& i) : chromosome(i.chromosome), fitness(i.fitness) {}