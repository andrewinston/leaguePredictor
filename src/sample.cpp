#include <vector>

#include "sample.h"
#include "table.h"

using std::vector;

sample::sample() : input(vector<double>{200, 0.0}), output(-1) {}

sample::sample(vector<int> participants_team_1, vector<int> participants_team_2, int winner) {
	for(auto p1 : participants_team_1){
		for(auto stat : champion_stats_lookup_table[p1]){
			input.push_back(stat);
		}
	}

	for(auto p2 : participants_team_2){
		for(auto stat : champion_stats_lookup_table[p2]){
			input.push_back(stat);
		}
	}
	this->output = winner;
}