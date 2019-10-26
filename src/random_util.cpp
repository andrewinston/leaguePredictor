#include <assert.h>
#include <stdlib.h>
// FLOAT random number in (a, b)
double rand_rangef(int a, int b){
	assert(b >= a);
	double r = rand()/(double)RAND_MAX;
	// cout << "random generated: " << r*(b-a)+a << endl;
	return r*(b-a)+a;
}

// INTEGER random number in [a, b)
int rand_range(int a, int b){
	assert(b >= a);
	int r = rand()%(b-a);
	// cout << "random generated: " << r+a << endl;
	return r+a;
}