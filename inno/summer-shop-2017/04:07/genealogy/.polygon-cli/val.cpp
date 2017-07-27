#include "testlib.h"
#include <vector>
#include <iostream>
using namespace std;

typedef vector <int> vi;
typedef vector <vi> vvi;

vi par;
vvi g;
vi was;

bool dfs(int v)
{
	was[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++)
	{
		int to = g[v][i];
		if (was[to] == 1) return false;
		if (was[to] == 2) continue;
		if (!dfs(to)) return false;
	}
	was[v] = 2;	
	return true;
}

int main() {
    registerValidation();
 	int n = inf.readInt(1, 100000);
 	inf.readEoln();

 	g = vvi(n);
 	for (int i = 0; i < n; i++)
 		g[i] = vi();

 	par = vi(n);
 	int root = -1;
 	for (int i = 0; i < n; i++)
 	{
 		if (i > 0) inf.readSpace();
		par[i] = inf.readInt(-1, n);
		ensuref((abs(par[i]) > 0), "zero at position %d", i);
		if (par[i] == -1)
		{
			ensuref(root == -1, "two roots - that's bad");
			root = i;
		}
		else
			g[par[i] - 1].push_back(i);
 	}
 	inf.readEoln();
 	ensuref(root != -1, "there is no root");

 	was = vi(n, 0);
 	bool f = dfs(root);
 	ensuref(f, "there are cycles");

 	for (int i = 0; i < n; i++)
 		ensuref(was[i], "vertex %d isn't conntected to the tree", i + 1);

 	int q = inf.readInt(1, 3000000);
 	int all = 0;
 	inf.readEoln();

 	vi mark(n, -1);
 	for (int i = 0; i < q; i++)
 	{
 		int k = inf.readInt(1, 100000);
 		all += k;
 		ensuref(all <= 3000000, "too much vertices");
 		for (int j = 0; j < k; j++)
 		{
 			inf.readSpace();
 			int v = inf.readInt(1, n) - 1;
 			ensuref(mark[v] != i, "vertex %d is already used in group %d\n", v, i);
 			mark[v] = i;
 		}
 		inf.readEoln();
 	}
 	inf.readEof();
    return 0;
}