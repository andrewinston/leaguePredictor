#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>

using std::vector;

struct sample{
	vector<double> input;
	int output; // win/lose

	sample();

	sample(vector<int> participants_team_1, vector<int> participants_team_2, int winner);
};
#endif