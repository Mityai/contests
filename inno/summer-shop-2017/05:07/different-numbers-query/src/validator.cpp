#include "testlib.h"
#include <cstdio>

using namespace std;

const int N = 1e6 + 100;

int parent[N];

int findSet(int v) {
	return parent[v] = (parent[v] != v ? findSet(parent[v]) : v);
}

void unite(int a, int b) {
	a = findSet(a); b = findSet(b);
	if (a == b) {
		return ;
	}
	parent[a] = b;
}

int main(int argc, char **argv) {
	registerValidation(argc, argv);
	int n = inf.readInt(2, 100000, "n");
	inf.readSpace();
	int m = inf.readInt(1, 100000, "m");
	inf.readEoln();
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	for (int i = 1; i < n; i++) {
		int u = inf.readInt(1, n, "u_i") - 1;
		inf.readSpace();
		int v = inf.readInt(1, n, "v_i") - 1;
		inf.readSpace();
		inf.readInt(-1000 * 1000 * 1000, 1000 * 1000 * 1000, "x_i");
		ensuref(findSet(u) != findSet(v), "cycles in a tree");
		unite(u, v);
		inf.readEoln();
	}
	for (int i = 0; i < m; i++) {
		inf.readInt(1, n, "a_j");
		inf.readSpace();
		inf.readInt(1, n, "b_j");
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}