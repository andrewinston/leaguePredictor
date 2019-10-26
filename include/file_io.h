#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

#include "sample.h"

void read_sample_file(std::string file_path, std::vector<sample>& samples);

void populate_winrate_lookup_table();

#endif