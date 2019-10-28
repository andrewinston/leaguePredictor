#include <vector>

#include "sample.h"
#include "winrate_lookup_table.h"

using std::vector;

sample::sample() : input(vector<double>{25, 0.0}), output(-1) {}

sample::sample(vector<int> participants_team_1, vector<int> participants_team_2, int winner) {
	for(auto p1 : participants_team_1){
		for(auto p2 : participants_team_2){
			if(!winrate_lookup_table.count({p1, p2})) this->input.push_back(-1);
			else this->input.push_back(winrate_lookup_table.at({p1, p2}));
		}
	}
	this->output = winner;
}

void sample::set_input(int i, double val){
	input[i] = val;
}

void sample::set_output(int out){
	output = out;
}