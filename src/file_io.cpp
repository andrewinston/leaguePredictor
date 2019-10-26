#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "sample.h"
#include "winrate_lookup_table.h"

using std::vector;
using std::cin;

void read_sample_file(std::string file_path, vector<sample>& samples){
	std::ifstream in(file_path);
	
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	int winner;
	int match_id;
	while(cin >> winner){
		cin >> match_id;
		vector<int> t1;
		vector<int> t2;
		int a = 0;
		for (int i = 0; i < 5; i++){
			cin >> a;
			t1.push_back(a);
		}
		for(int i = 0; i < 5; i++){
			cin >> a;
			t2.push_back(a);
		}
		samples.emplace_back(t1, t2, winner);
	}

	cin.rdbuf(cinbuf);
}

void populate_winrate_lookup_table(){
	std::ifstream in("data/winrate_lookup_table.txt");
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());
	
	int a, b;
	double c;
	while(cin >> a >> b >> c){
		winrate_lookup_table[{a, b}] = c;
	}

	cin.rdbuf(cinbuf);
}