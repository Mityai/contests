#include "testlib.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]), m = atoi(argv[2]), c = atoi(argv[3]);
	double l = atof(argv[4]), r = atof(argv[5]);
	printf("%d %d\n", n, m);
	for (int i = 1; i < n; i++) {
		int left = l * (i - 1), right = r * (i - 1);
		printf("%d %d %d\n", rnd.next(left, right) + 1, i + 1, rnd.next(0, c));
	}
	for (int i = 0; i < m; i++) {
		printf("%d %d\n", rnd.next(1, n), rnd.next(1, n));
	}
	return 0;
}