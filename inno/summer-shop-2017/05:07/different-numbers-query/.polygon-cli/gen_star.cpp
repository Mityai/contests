#include "testlib.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]), m = atoi(argv[2]), k = atoi(argv[3]), c = atoi(argv[4]);
	int count = (n - 1) / k;
	n = count * k + 1;
	int cur = 1;
	vector<tuple<int, int, int>> edges;
	vector<int> good;
	for (int i = 0; i < count; i++) {
		vector<int> ray(k);
		for (int j = 0; j < k; j++) {
			ray[j] = cur++;
		}
		edges.emplace_back(0, ray[0], rnd.next(0, c));
		for (int j = 0; j < k - 1; j++) {
			edges.emplace_back(ray[j], ray[j + 1], rnd.next(0, c));
		}
		good.pb(ray.back());
	}
	assert(cur == n);
	cout << n << " " << m << endl;
	for (int i = 0; i < len(edges); i++) {
		int u, v, c; tie(u, v, c) = edges[i];
		printf("%d %d %d\n", u + 1, v + 1, c);
	}
	for (int i = 0; i < m; i++) {
		printf("%d %d\n", good[rnd.next(0, len(good) - 1)] + 1, good[rnd.next(0, len(good) - 1)] + 1);
	}
    return 0;
}
