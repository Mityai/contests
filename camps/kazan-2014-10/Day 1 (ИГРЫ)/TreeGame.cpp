#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <queue>
#include <iomanip>

using namespace std;
         
#define mp make_pair
#define fi first
#define se second
#define sz(a) (int)a.size()
#define len(s) (int)s.length()

typedef long long ll;

const double eps = 1e-7;
const double PI = 3.14159265358979323846;
const int INF = 1234567890;
const ll MOD = (ll)1e6+3;
const int MAXN = (int)1e5;
const int MAXM = (int)1e5;

vector<vector<int> > g;
vector<int> z;
vector<int> N, P;

int main() {
	#if __APPLE__
		freopen("input.txt", "r", stdin);
	#else
	freopen("game2.in", "r", stdin);
	freopen("game2.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	g.resize(n);
	z.resize(n);
	N.resize(n, -1);
	P.resize(n, -1);

	for (int i = 0; i < m; i++) {
     	int u, v;
		cin >> u >> v;

		--u;
		--v;

		g[v].push_back(u);
		++z[u];
	}
	
	queue<int> q;
	for (int i = 0; i < n; i++) {
     	if (z[i] == 0) {
         	P[i] = 0;
			q.push(i);
		}
	}

	while (!q.empty()) {
     	int u = q.front();
		q.pop();

		if (N[u] != -1) {
            for (int i = 0; i < g[u].size(); i++) {
             	int v = g[u][i];
				--z[v];

				if (z[v] == 0) {
					P[v] = N[u] + 1;
                 	q.push(v);
				}
			}
		} else {
			for (int i = 0; i < g[u].size(); i++) {
			 	int v = g[u][i];
				if (N[v] == -1) {
				 	N[v] = P[u] + 1;   
					q.push(v);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
     	if (N[i] != -1) {
         	putchar('W');
		} else if (P[i] != -1) {
         	putchar('L');
		} else {
         	putchar('D');
		}
	}
	cout << endl;
}
