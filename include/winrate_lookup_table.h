#ifndef WINRATE_LOOKUP_TABLE_H
#define WINRATE_LOOKUP_TABLE_H

#include <map>
#include <utility>

using std::map;
using std::pair;

extern map<pair<int, int>, pair<int, int>> winrate_lookup_table;

#endif
