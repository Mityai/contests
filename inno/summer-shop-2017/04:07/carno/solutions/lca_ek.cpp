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

struct DSU {
	std::vector <int> up;
	DSU() {}

	void newVertex()
	{
		up.push_back(up.size());
	}

	int getRoot(int v)
	{
		int v1 = v;
		while (up[v1] != v1)
			v1 = up[v1];
		while (v != v1)
		{
			int temp = up[v];
			up[v] = v1;
			v = temp;
		}
		return v1;
	}

	void join(int src, int dest)
	{
		src = getRoot(src);
		dest = getRoot(dest);

		up[dest] = src;
	}
};

int n;
int up[logN][N];
int depth[N];
char s[100];
int par[N];
DSU dsu;

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
	calcUp(v);
	dsu.newVertex();
}

void init()
{
	addVertex(0);
}

void deleteVertex(int v)
{
	dbg("- %d\n", v);
	dsu.join(par[v], v);
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
	return dsu.getRoot(par[u]);
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
