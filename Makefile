all:
	g++ ./src/geneticAlgorithm.cpp ./src/winrate_lookup_table.cpp -I./include/ -o geneticAlgorithm -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wno-unused-result -Wno-unused-function -O2
