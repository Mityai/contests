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
	
	if (argc != 9) {
		cerr << "Usage: n, minHero, maxHero, m1, weakMonster, m2, strongMonster, seed" << endl;

		return 1;
	}
	
	int n = atoi(argv[1]);
	int minH = atoi(argv[2]);
	int maxH = atoi(argv[3]);
	int m1 = atoi(argv[4]);
	int wM = atoi(argv[5]);
	int m2 = atoi(argv[6]);
	int sM = atoi(argv[7]);

	cout << n << ' ' << m1 + m2 << endl;
	for (int i = 0; i < n; i++)
		cout << rnd.next(minH, maxH) << ' ' << rnd.next(minH, maxH) << endl;
	for (int i = 0; i < m1; i++)
		cout << rnd.next(1, wM) << ' ' << rnd.next(1, wM) << endl;
	for (int i = 0; i < m2; i++)
		cout << rnd.next(1, sM) << ' ' << rnd.next(1, sM) << endl;
	
    return 0;
}