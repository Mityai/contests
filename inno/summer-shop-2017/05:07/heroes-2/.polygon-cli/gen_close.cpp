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
	
	if (argc != 10) {
		cerr << "Usage: n, m, A, B, maxH, C, D, maxM, seed" << endl;

		return 1;
	}
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int A = atoi(argv[3]);
	int B = atoi(argv[4]);
	int maxH = atoi(argv[5]);
	int C = atoi(argv[6]);
	int D = atoi(argv[7]);
	int maxM = atoi(argv[8]);

	int step1 = 1;
	while (step1 * step1 <= n)
		step1++;
	int step2 = 1;
	while (step2 * step2 <= m)
		step2++;

	vector <pair <int, int> > heroes;
	vector <pair <int, int> > monsters;
	for (int i = max(1, A - step1); i <= min(maxH, A + step1); i++) {
		for (int j = max(1, B - step1); j <= min(maxH, B + step1); j++) {
			heroes.pb(mp(i, j));
		}
	}
	
	for (int i = max(1, C - step2); i <= min(maxM, C + step2); i++) {
		for (int j = max(1, D - step2); j <= min(maxM, D + step2); j++) {
			monsters.pb(mp(i, j));
		}
	}

	shuffle(heroes.begin(), heroes.end());
	shuffle(monsters.begin(), monsters.end());

	assert((int) heroes.size() >= n);
	heroes.resize(n);
	assert((int) monsters.size() >= m);
	monsters.resize(m);

	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++)
		printf("%d %d\n", heroes[i].fs, heroes[i].sc);
	for (int i = 0; i < m; i++)
		printf("%d %d\n", monsters[i].fs, monsters[i].sc);

    return 0;
}