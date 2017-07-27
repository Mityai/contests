#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <cstdarg>

const int N = 200100;
const int logN = 18;

#define DBG2 0

void dbg(const char * fmt, ...)
{
#ifdef DBG1
#if DBG2
	va_list args;
	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);

	fflush(stdout);
#endif	
#endif
}

int n;
int up[logN][N];
int depth[N];
char s[100];
int par[N];
bool exists[N];

void calcUp(int v)
{
	up[0][v] = par[v];
	for (int i = 1; i < logN; ++i)
		up[i][v] = up[i - 1][up[i - 1][v]];
}

void addVertex(int parent)
{
	dbg("+ %d\n", parent);
	int v = n++;
	par[v] = parent;
	depth[v] = depth[parent] + 1;
	exists[v] = true;
	calcUp(v);
}

void init()
{
	addVertex(0);
}

void deleteVertex(int v)
{
	dbg("- %d\n", v);
	exists[v] = false;
}

int goUp(int u, int d)
{
	int power = 0;
	while (d)
	{
		if (d & 1)
			u = up[power][u];
		++power;
		d /= 2;
	}
	return u;
}

int findExistingAncestor(int v)
{
	if (exists[v])
		return v;
	for (int power = logN - 1; power >= 0; --power)
	{
		int newV = up[power][v];
		if (!exists[newV])
			v = newV;
	}
	if (exists[v])
		return v;
	return par[v];
}

int lca(int u, int v)
{
	dbg("? %d %d\n", u, v);
	if (depth[u] > depth[v])
		std::swap(u, v);
	v = goUp(v, depth[v] - depth[u]);

	if (u == v)
		return u;

	for (int power = logN - 1; power >= 0; --power)
	{
		if (up[power][u] != up[power][v])
		{
			u = up[power][u];
			v = up[power][v];
		}
	}
	assert(par[u] == par[v]);
	return findExistingAncestor(par[u]);
}

int main()
{
	freopen("carno.in", "r", stdin);
	freopen("carno.out", "w", stdout);
	int m;
	scanf("%d", &m);

	init();

	for (int i = 0; i < m; ++i)
	{
		scanf("%s", s);
		if (!strcmp(s, "+"))
		{
			int parent;
			scanf("%d", &parent);
			--parent;

			addVertex(parent);
		}
		else if (!strcmp(s, "-"))
		{
			int v;
			scanf("%d", &v);
			--v;

			deleteVertex(v);
		}
		else if (!strcmp(s, "?"))
		{
			int a, b;
			scanf("%d%d", &a, &b);
			--a, --b;

			printf("%d\n", lca(a, b) + 1);
		}
		else
			assert(false);
	}

	return 0;
}
