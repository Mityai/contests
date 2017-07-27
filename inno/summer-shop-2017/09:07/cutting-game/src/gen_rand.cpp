#include <cstdio>
#include <cstdlib>
#include "random.h"

const int MINN = 0;
const int MAXN = 16;
const int MAXA = 100000;

int main(int argc, char ** argv) {
	int seed = atoi(argv[1]);
	initrand(seed);

	int minn = MINN;
	int maxn = MAXN;
	if (argc > 2) {
		minn = maxn = atoi(argv[2]);
	}

	int n = 1 << R(minn, maxn);
	printf("%d\n", n);
	for (int i = 0; i < n; ++i)
		printf("%d%c", R(-MAXA, MAXA), i == n - 1 ? '\n' : ' ');
	return 0;
}
