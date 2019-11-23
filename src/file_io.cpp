#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "file_io.h"
#include "sample.h"
#include "table.h"

using std::vector;
using std::cin;

void read_samples_file(std::string file_path, vector<sample>& samples){
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

void populate_tables(){
	populate_winrate_lookup_table();
	populate_champion_stats_lookup_table();
}

void populate_champion_stats_lookup_table(){
	std::ifstream in("data/champion_stats.txt");
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	int id;
	while(cin >> id){
		vector<double> aux(20, 0.0);
		for(int i = 0; i < 20; i++){
			cin >> aux[i];
		}
		champion_stats_lookup_table[id] = aux;
	}

	cin.rdbuf(cinbuf);
}

void populate_winrate_lookup_table(){
	std::ifstream in("data/samples/attempt2/winrate_samples.txt");
	std::streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());
	int winner, match_id;
	while(cin >> winner >> match_id){
		vector<int> t1, t2;
		for(int i = 0; i < 5; i++){
			int c;
			cin >> c;
			t1.push_back(c);
		}
		for(int i = 0; i < 5; i++){
			int c;
			cin >> c;
			t2.push_back(c);
		}
		for(auto c1 : t1){
			for(auto c2 : t2){
				if(!winrate_lookup_table.count({c1, c2})){
					winrate_lookup_table[{c1, c2}] = {0, 0};
					winrate_lookup_table[{c2, c1}] = {0, 0};
				}
				if(winner == 1){
					pair<int, int> res = winrate_lookup_table[{c1, c2}];
					pair<int, int> res2 = winrate_lookup_table[{c2, c1}];
					winrate_lookup_table[{c1, c2}] = {res.first+1, res.second+1};
					winrate_lookup_table[{c2, c1}] = {res2.first, res2.second+1};
				}
				else{
					pair<int, int> res = winrate_lookup_table[{c1, c2}];
					pair<int, int> res2 = winrate_lookup_table[{c2, c1}];
					winrate_lookup_table[{c1, c2}] = {res.first, res.second+1};
					winrate_lookup_table[{c2, c1}] = {res2.first+1, res2.second+1};
				}
			}
		}
	}

	cin.rdbuf(cinbuf);
}