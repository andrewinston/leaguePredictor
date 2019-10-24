all:
	g++ -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wno-unused-result -Wno-unused-function -O2 geneticAlgorithm.cpp -o geneticAlgorithm -lsqlite3;
