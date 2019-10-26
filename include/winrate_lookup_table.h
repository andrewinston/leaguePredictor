#ifndef WINRATE_LOOKUP_TABLE
#define WINRATE_LOOKUP_TABLE

#include <map>
#include <utility>

using std::map;
using std::pair;

extern map<pair<int, int>, double> winrate_lookup_table;
void populate_winrate_lookup_table();
#endif
