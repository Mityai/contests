#include "testlib.h"
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);


int main(int argc, char ** argv) {
	registerGen(argc, argv, 1);
	
	if (argc != 8) {
		cerr << "Usage: n, m, maxA, maxB, maxC, maxD, seed" << endl;

		return 1;
	}
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int maxA = atoi(argv[3]);
	int maxB = atoi(argv[4]);
	int maxC = atoi(argv[5]);
	int maxD = atoi(argv[6]);

	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++)
		printf("%d %d\n", rnd.next(1, maxA), rnd.next(1, maxB));
	for (int i = 0; i < m; i++)
		printf("%d %d\n", rnd.next(1, maxC), rnd.next(1, maxD));
	
    return 0;
}