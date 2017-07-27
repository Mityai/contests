#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> g[1000];
bool visited[1000];

void dfs(int v) {
	if (visited[v])
		return;
	visited[v] = true;
	for (int i = 0; i < g[v].size(); i++)
		dfs(g[v][i]);
}

int main () {
	int n, m;
	cin >> n >> m;
	bool good = true;
	if (m == n - 1) {
		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			a--;
			b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		memset(visited, 0, sizeof(visited));
		dfs(0);
		for (int i = 0; i < n; i++)
			good &= visited[i];
	}
	else
		good = false;
	
	if (good)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	return 0;
}                                                          
