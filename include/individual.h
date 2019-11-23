#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <utility>
#include <vector>

#include "sample.h"

using std::make_pair;
using std::pair;
using std::vector;

double sigmoid(double val);

double relu(double val);

struct individual{
	static const int HIDDEN_LAYER_SIZE = 100;
	static const int INPUT_SIZE = 200;
	static const int OUTPUT_SIZE = 1;
	static constexpr double MUTATION_PROBABILITY = 0.3;
	static const int MINIMAL_WEIGHT = -15;
	static const int MAXIMAL_WEIGHT = 15;
	static const int MINIMAL_BIAS = -15;
	static const int MAXIMAL_BIAS = 15;
	//			weight, bias
	vector<pair<double, double>> chromosome{HIDDEN_LAYER_SIZE*(INPUT_SIZE+OUTPUT_SIZE), make_pair(0.0, 0.0)};

	double fitness;

	double activation_function_input(double val);

	double activation_function_output(double val);

	double get_weight_input(int i, int j);

	double get_bias_input(int i, int j);

	double get_weight_output(int i);

	double get_bias_output(int i);

	double calculate_outcome(vector<double> in);

	void calculate_fitness(const vector<sample>& samples);

	void mutate();

	individual();

	individual(const vector<pair<double, double>>& c);

	individual(const individual& i);
};
#endif