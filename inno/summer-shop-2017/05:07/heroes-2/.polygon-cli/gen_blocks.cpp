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
	
	if (argc != 11) {
		cerr << "Usage: n, m, blocks, errors, maxA, maxAE, maxB, maxC, maxD, seed" << endl;

		return 1;
	}
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	int blocks = atoi(argv[3]);
	int errors = atoi(argv[4]);
	int maxA = atoi(argv[5]);
	int maxAE = atoi(argv[6]);
	int maxB = atoi(argv[7]);
	int maxC = atoi(argv[8]);
	int maxD = atoi(argv[9]);

	vector <pair <int, int> > heroes;
	vector <pair <int, int> > monsters;

	vector <int> events;
	for (int i = 0; i < blocks; i++)
		events.pb(rnd.next(1, m));
	events.pb(0);
	events.pb(m);
	sort(events.begin(), events.end());

	events.resize(unique(events.begin(), events.end()) - events.begin());
	for (int i = 0; i < (int) events.size() - 1; i++) {
		int attack = rnd.next(1, maxC);
		int hp = rnd.next(1, maxD);
		for (int j = events[i] + 1; j <= events[i + 1]; j++)
			monsters.pb(mp(attack, hp));
	}

	for (int i = 0; i < n - errors; i++)
		heroes.pb(mp(rnd.next(1, maxA), rnd.next(1, maxB)));
	for (int i = 0; i < errors; i++)
		heroes.pb(mp(rnd.next(1, maxAE), rnd.next(1, maxB)));

	shuffle(heroes.begin(), heroes.end());

	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++)
		printf("%d %d\n", heroes[i].fs, heroes[i].sc);
	for (int i = 0; i < m; i++)
		printf("%d %d\n", monsters[i].fs, monsters[i].sc);
	
    return 0;
}