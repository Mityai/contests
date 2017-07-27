#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <iomanip>
#define nextLine() { for (int c = getchar(); c != '\n' && c != EOF; c = getchar()); }
#define sqr(a) ((a)*(a))
#define has(mask,i) (((mask) & (1<<(i))) == 0 ? false : true)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define TASK "genealogy"
using namespace std;

#define log2 my_log2
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef long long LL;
typedef long double ldb;

const int INF = (1 << 30) - 1;
const ldb EPS = 1e-9;
const ldb PI = fabs(atan2(0.0, -1.0));

const int MAXV = 100005;

int edges = 0;
int fst[MAXV];
int nxt[MAXV];
int eend[MAXV];

inline void addEdge(int u, int v)
{
	nxt[edges] = fst[u];
	eend[edges] = v;
	fst[u] = edges++;	
}

int n;
int root;

void load()
{
	memset(fst, -1, sizeof(fst));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int p;
		scanf("%d", &p);
		if (p == -1) root = i;
		else addEdge(p - 1, i);
	}
}

int dpth[MAXV];
int fptr[MAXV];
vector <int> order;

void dfs(int v, int d)
{
	order.pb(v);
	fptr[v] = (int)order.size() - 1;
	dpth[v] = d;
	for (int i = fst[v]; i != -1; i = nxt[i])
	{
		dfs(eend[i], d + 1);
		order.pb(v);
	}
}

int sparse[20][3 * MAXV];
int log2[3 * MAXV];

inline void precalcLca()
{
 	dfs(root, 0);
 	int sz = order.size();
 	for (int j = 0; (1 << j) < sz; j++)
 	{
 		for (int i = 0; i < sz; i++)
 		{
 			if (j == 0) sparse[j][i] = order[i];
 			else
 			{
 				if (i + (1 << j) <= sz)
 				{
 					int a = sparse[j - 1][i];
 					int b = sparse[j - 1][i + (1 << (j - 1))];
 					sparse[j][i] = (dpth[a] < dpth[b] ? a : b);
 				}
 			}	
 		}
 	}

 	log2[1] = 0;
 	for (int i = 2; i <= sz; i++)
 		log2[i] = log2[i >> 1] + 1;
}

inline int lca(int u, int v)
{
	int pu = fptr[u];
	int pv = fptr[v];

	if (pu > pv)
	{
		swap(u, v);
		swap(pu, pv);
	}

	int pow2 = log2[pv - pu + 1];

	int i = sparse[pow2][pu];
	int j = sparse[pow2][pv - (1 << pow2) + 1];
	return dpth[i] < dpth[j] ? i : j;
}

inline bool cmp(int i, int j)
{
	return fptr[i] < fptr[j];
}

inline int query(vector <int> &vt)
{
	sort(vt.begin(), vt.end(), cmp);
	
	int res = dpth[vt[0]] + 1;
	for (int i = 1; i < (int)vt.size(); i++)
	{
		int s = lca(vt[i - 1], vt[i]);
		res += dpth[vt[i]] - dpth[s];
	}

	return res;	
}

void solve()
{
	precalcLca();
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int k;
		scanf("%d", &k);

		vector <int> vt(k);
		for (int j = 0; j < k; j++)
		{
			scanf("%d", &vt[j]);
			vt[j]--;
		}
			
		printf("%d\n", query(vt));
	}
}

int main()
{
	freopen(TASK".in","r",stdin);
	freopen(TASK".out","w",stdout);
	load();
	solve();
	return 0;
}
