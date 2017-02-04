#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int ans = 0;
vector<vector<int> > g;
bool us[11];

void dfs(int v, int st, int p = -1) {
	us[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int u = g[v][i];
		if (u == p || u < st) continue;
		if (u == st) {
			ans++;
		} else if (!us[u]) {
			dfs(u, st, v);
		}
	}
	us[v] = false;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("numcycle.in", "r", stdin);
	freopen("numcycle.out", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);

	g.resize(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);

		--u;
		--v;

		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 0; i < n; i++) {
		dfs(i, i);
	}

	printf("%d\n", ans / 2);
}
