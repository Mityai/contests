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
	int n = atoi(argv[1]), m = atoi(argv[2]);
	vector<int> res(n - 1);
	int len1 = 0, len2 = 1;
	for (int i = (n - 1) / 2 - 1; i >= 0; i--) {
		res[i] = len1;
		len1 += 2;
	}
	for (int i = (n - 1) / 2; i < n - 1; i++) {
		res[i] = len2;
		len2 += 2;
	}
	cout << n << " " << m << endl;
	for (int i = 0; i < n - 1; i++) {
		printf("%d %d %d\n", i + 1, i + 2, res[i]);
	}
	for (int i = 0; i < m; i++) {
		printf("%d %d\n", rnd.next(1, n / 2 - 1), rnd.next(n / 2 + 1, n));
	}
    return 0;
}