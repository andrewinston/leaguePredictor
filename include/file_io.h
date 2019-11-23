#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

#include "sample.h"

void populate_champion_stats_lookup_table();

void populate_winrate_lookup_table();

void read_samples_file(std::string file_path, std::vector<sample>& samples);

void populate_tables();

#endif