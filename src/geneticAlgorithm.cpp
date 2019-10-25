#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <map>
#include <fstream>
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

struct sample{
	vector<double> input;
	int output; // win/lose

	sample() : input(vector<double>{25, 0.0}), output(-1) {}

	sample(vector<int> participants_team_1, vector<int> participants_team_2, int winner) {
		for(auto p1 : participants_team_1){
			for(auto p2 : participants_team_2){
				this->input.push_back(winrate_lookup_table.at({p1, p2}));
			}
		}
		this->output = winner;
	}

	void set_input(int i, double val){
		input[i] = val;
	}

	void set_output(int out){
		output = out;
	}
};

vector<sample> training_samples;
vector<sample> validating_samples;

// FLOAT random number in (a, b)
double rand_rangef(int a, int b){
	assert(b >= a);
	double r = rand()/(double)RAND_MAX;
	return r*(b-a)+a;
}

// INTEGER random number in [a, b)
int rand_range(int a, int b){
	assert(b >= a);
	int r = rand()%(b-a);
	return r+a;
}

double sigmoid(double val){
	return 1.0/(1+exp(val));
}

double relu(double val){
	return max(0.0, val);
}

struct individual{
	static const int HIDDEN_LAYER_SIZE = 30;
	static const int INPUT_SIZE = 25;
	static const int OUTPUT_SIZE = 1;
	static constexpr double MUTATION_PROBABILITY = 0.05;
	//			weight, bias
	vector<pair<double, double>> chromosome{HIDDEN_LAYER_SIZE*(INPUT_SIZE+OUTPUT_SIZE), make_pair(0.0, 0.0)};
	double fitness;

	bool operator<(individual& a) {
		if(this->fitness < 0) this->calculate_fitness(training_samples);
		if(a.fitness < 0) a.calculate_fitness(training_samples);
		return this->fitness < a.fitness;
	}

	double activation_function_input(double val){
		return relu(val);
	}

	double activation_function_output(double val){
		return sigmoid(val);
	}

	double get_weight_input(int i, int j){
		return chromosome[j*(INPUT_SIZE+OUTPUT_SIZE)+i].first;
	}

	double get_bias_input(int i, int j){
		return chromosome[j*(INPUT_SIZE+OUTPUT_SIZE)+i].second;
	}

	double get_weight_output(int i){
		return chromosome[i*(INPUT_SIZE+OUTPUT_SIZE)+INPUT_SIZE].first;
	}

	double get_bias_output(int i){
		return chromosome[i*(INPUT_SIZE+OUTPUT_SIZE)+INPUT_SIZE].second;
	}

	int calculate_outcome(vector<double> in){
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

	void calculate_fitness(const vector<sample>& samples){
		int total = (int)samples.size();
		int correct = 0;
		for(sample s : samples){
			int outcome = calculate_outcome(s.input);
			correct += outcome == s.output;
		}
		this->fitness = correct/(double)total;
	}

	void mutate(){
		for(int i = 0; i < (int)chromosome.size(); i++){
			if(rand_rangef(0, 1) <= MUTATION_PROBABILITY){
				chromosome[i] = {rand_rangef(-10, 10), rand_rangef(-10, 10)};
			}
		}
	}

	individual(){
		fitness = -1;
		for(auto& c : chromosome){
			c = {rand_rangef(-10, 10), rand_rangef(-10, 10)};
		}
	}
	individual(const individual& i) : chromosome(i.chromosome), fitness(i.fitness) {}
};

bool fitness_descending_sort(individual& a, individual& b){
	return !(a < b);
}

struct genetic_algorithm{
	static const int ELITE_SIZE = 10;
	static const int POPULATION_SIZE = 100;
	static constexpr double MUTATION_PROBABILITY = 0.2;
	vector<individual> population;

	void create_population(){
		for(int i = 0; i < POPULATION_SIZE; i++){
			population.push_back(individual());
		}
	}

	void evaluate_population(){
		for(auto &ind : population){
			ind.calculate_fitness(training_samples);
		}
		sort(population.begin(), population.end(), fitness_descending_sort);
	}

	void cross(){
		for(int i = ELITE_SIZE; i < POPULATION_SIZE; i+=2){
			int i1 = rand_range(0, ELITE_SIZE), i2 = rand_range(0, ELITE_SIZE);
			pair<individual, individual> crossed = crossover(population[i1], population[i2]);
			population[i] = crossed.first;
			population[i+1] = crossed.first;
		}
	}

	void mutate(){
		for(auto& ind : population){
			if(rand_rangef(0, 1) < MUTATION_PROBABILITY){
				ind.mutate();
			}
		}
	}

	pair<individual, individual> crossover(individual a, individual b){
		int i = rand_range(0, (int)a.chromosome.size());
		int j = rand_range(0, (int)a.chromosome.size());
		if(i > j) swap(i, j);
		pair<individual, individual> ret = {a, b};
		for(; i <= j; i++) {
			swap(ret.first.chromosome[i], ret.second.chromosome[i]);
		}
		return ret;
	}

	void run(){
		int generation = 0;
		create_population();
		evaluate_population();
		while(generation < 100){
			print_elite(generation);
			cross();
			mutate();
			evaluate_population();
			generation++;
		}
	}
	
	void print_elite(int gen){
		cout << "Generation " << gen << endl;
		for(int i = 0; i < ELITE_SIZE; i++){
			cout << "\t" << i+1 << "º: " << population[i].fitness*100 << "%" << endl;
		}
	}
};

void read_sample_file(string file_path, vector<sample>& samples){
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
		training_samples.emplace_back(t1, t2, winner);
	}

	cin.rdbuf(cinbuf);
}

int main(){
	read_sample_file("data/samples/training_samples.txt");
	read_sample_file("data/samples/validating_samples.txt");
}
