#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::vector;

extern map<pair<int, int>, pair<int, int>> winrate_lookup_table;
extern map<int, vector<double>> champion_stats_lookup_table;

#endif
