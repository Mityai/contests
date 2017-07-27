#include "random.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

vector <int> generateTree(int n, int lin, int botv)
{
	vector <int> perm(n);
	for (int i = 0; i < n; i++)
		perm[i] = i;

	randomShuffle(perm.begin(), perm.end());
	vector <int> par(n, -1);

	vector <int> subTree(lin);
	for (int i = 1; i <= lin; i++)
	{
		par[perm[i]] = perm[0];
		subTree[i - 1] = perm[i];
	}

	for (int i = lin + 1; i < n - botv; i++)
	{
		int j = rndInt(lin);
		par[perm[i]] = subTree[j];
		subTree[j] = perm[i];
	}

	for (int i = n - botv; i < n; i++)
	{
		int j = rndInt(i);
		par[perm[i]] = perm[j];
	}

	return par;
}

inline int randomChoice(const vector <int> &a)
{
	return a[rndInt(a.size())];
}

int main(int argc, char *argv[])
{
	if (argc != 7)
	{
		fprintf(stderr, "usage %s: <randseed> <number of vertices> <lin> <botv> <vertices in query> <number of queries>\n", argv[0]);
		exit(42);
	}

	initrand(atoi(argv[1]));
	int n = atoi(argv[2]);
	int lin = atoi(argv[3]);
	int botv = atoi(argv[4]);
	
	vector <int> par = generateTree(n, lin, botv);

	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (i > 0) cout << " ";
		cout << (par[i] != -1 ? par[i] + 1 : -1);
	}
	cout << endl;

	vector <bool> isLeaf(n, true);
	for (int i = 0; i < n; i++)
	{
		if (par[i] == -1) isLeaf[i] = false;
		else isLeaf[par[i]] = false;
	}

	vector <int> leaves;
	for (int i = 0; i < n; i++)
		if (isLeaf[i]) leaves.push_back(i);

	int k = min(atoi(argv[5]), (int)leaves.size());
	vector <int> mark(n, -1);
	int q = atoi(argv[6]);
	cout << q << endl;

	for (int i = 0; i < q; i++)
	{
		cout << k;
		for (int j = 0; j < k; j++)
		{
			int v = randomChoice(leaves);
			while (mark[v] == i)
				v = randomChoice(leaves);
			mark[v] = i;
			cout << " " << v + 1;
		}
		cout << endl;	
	}
	return 0;
}
