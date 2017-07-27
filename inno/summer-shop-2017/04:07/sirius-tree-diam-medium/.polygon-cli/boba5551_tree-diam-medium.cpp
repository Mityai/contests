#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> g[100000];
bool visited[100000];

int bestv, bestd;

void dfs(int v, int dist) {
	if (visited[v])
		return;
	visited[v] = true;
	if (dist > bestd) {
		bestv = v;
		bestd = dist;
	}
	for (int i = 0; i < g[v].size(); i++)
		dfs(g[v][i], dist + 1);
}

int getFurthest(int v) {
	bestd = -1;
	memset(visited, 0, sizeof(visited));
	dfs(v, 0);
	return bestv;
}

int main () {
	int n, m;
	cin >> n >> m;
	bool good = true;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	getFurthest(getFurthest(0));
	cout << bestd << endl;
	return 0;
}                                                          
