 #include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
 
const int INF = 1234567890;

vector<char> mark;
vector<vector<pair<int, int> > > gnew;

void dfs(int v, int w, vector<vector<int> > &d, const int &st) {
	mark[v] = true;
	d[st][v] = w;
	for (int i = 0; i < gnew[v].size(); i++) {
		int u = gnew[v][i].fi;
		int curw = gnew[v][i].se;
     	if (mark[u] == false) {
         	dfs(u, min(w, curw), d, st);
		}
	}
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else
    //freopen("maniac.in", "r", stdin);
	//freopen("maniac.out", "w", stdout);
#endif

	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<int, int> > > g(n);
	for (int i = 0; i < m; i++) {
     	int u, v, w;
		cin >> u >> v >> w;

		--u, --v;

		g[u].push_back(mp(v, w));
		g[v].push_back(mp(u, w));
	}

	gnew.resize(n);

	vector<int> d(n, 0);
	d[0] = INF;

	vector<int> p(n, -1);

	priority_queue<pair<int, int> > q;
	q.push(mp(d[0], 0));

	mark.assign(n, false);
	for (int i = 0; i < n; i++) {
		int v;
		do {
			v = q.top().se;
			q.pop();
		} while (mark[v] == true);

		mark[v] = true;

		if (p[v] != -1) {
			gnew[p[v]].push_back(mp(v, d[v]));
			gnew[v].push_back(mp(p[v], d[v]));
		}

		for (int j = 0; j < (int)g[v].size(); j++) {
			int u = g[v][j].fi;
			int w = g[v][j].se;
			if (d[u] < w) {
				d[u] = w;
				p[u] = v;
             	q.push(mp(d[u], u));
			}
		}
	}

	vector<vector<int> > dist(n, vector<int> (n));
	for (int i = 0; i < n; i++) {
		mark.assign(n, false);
		dfs(i, INF, dist, i);
	}

	for (int i = 0; i < k; i++) {
     	int u, v;
		cin >> u >> v;

		--u, --v;

		cout << dist[u][v] << endl;
	}
}
