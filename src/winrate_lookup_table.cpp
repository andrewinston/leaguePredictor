//this file was generated automatically.
#include "winrate_lookup_table.h"
#include <iostream>
#include <fstream>

map<pair<int, int>, double> winrate_lookup_table;

void populate_winrate_lookup_table(){
	std::ifstream in("data/winrate_lookup_table.txt");
	
	using std::cin;
	
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());
	int a, b;
	double c;
	while(cin >> a >> b >> c){
		winrate_lookup_table[{a, b}] = c;
	}

	cin.rdbuf(cinbuf);
}