all:
	g++ ./src/genetic_algorithm.cpp ./src/individual.cpp ./src/main.cpp ./src/random_util.cpp ./src/sample.cpp ./src/winrate_lookup_table.cpp -I./include/ -o geneticAlgorithm -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wno-unused-result -Wno-unused-function -O2
