#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);

	int maxn = atoi(argv[1]);
	int maxh = atoi(argv[2]);

	cout << rnd.next(1, maxn) << " ";
	cout << rnd.next(1, maxh) << "\n";

	return 0;
}
