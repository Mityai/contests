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
int depth[N];
int par[N];
std::vector < std::vector <int> > child;
char s[100];

void setParent(int v, int parent)
{
	par[v] = parent;
	child[parent].push_back(v);
}

void addVertex(int parent)
{
	dbg("+ %d\n", parent);

	int v = n++;

	child.push_back(std::vector<int>());

	setParent(v, parent);
	depth[v] = depth[parent] + 1;
}

void init()
{
	addVertex(0);
}

void clearVector(std::vector <int> & v)
{
	std::vector <int> v2;
	v.swap(v2);
}

void deleteVertex(int v)
{
	dbg("- %d\n", v);
	for (int i = 0; i < int(child[v].size()); ++i)
		setParent(child[v][i], par[v]);

	clearVector(child[v]);
}

int lca(int u, int v)
{
	dbg("? %d %d\n", u, v);

	while (u != v)
	{
		if (depth[u] < depth[v])
			v = par[v];
		else
			u = par[u];
	}
	return u;
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
