#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
#include <climits>
#include <bitset>
#include <assert.h>
 
#define fi first
#define se second
#define mp make_pair
 
#define sz(a) (int)a.size()
//#define len(s) (int)s.length()
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const int INF = 1234567890;
const ll INF_LL = LLONG_MAX - INF;
const int MAXN = 3e5;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("vacation.in", "r", stdin);
        freopen("vacation.out", "w", stdout);
    #endif
	
	int n, m, k, q;
	scanf("%d%d%d%d", &n, &m, &k, &q);

	vector<vector<pair<int, int> > > g(n);
	for (int i = 0; i < m; i++) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		
		--a;
		--b;

		g[a].push_back(mp(b, w));
	}

	for (int i = 0; i < k; i++) {
		int trash;
		scanf("%d", &trash);
	}

	vector<pair<int, int> > qu(q);
	vector<int> to_check(n);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &qu[i].fi, &qu[i].se);
		
		--qu[i].fi;
		--qu[i].se;  	

		to_check[qu[i].fi] = 1;
	}

	sort(qu.begin(), qu.end());

	int ans = 0;
	ll answ = 0;
	int j = 0;
	for (int a = 0; a < n; a++) {
		if (to_check[a] == 1) {
			vector<int> d(n, INF), len(n);
			d[a] = 0;
			priority_queue<pair<int, int> > q;
			q.push(mp(0, a));
			while (!q.empty()) {
				pair<int, int> f = q.top();
				int v = f.se;
				int curd = -f.fi;
				q.pop();

				if (curd > d[v]) {
					continue;
				}

				int curlen = len[v];

				for (int j = 0; j < g[v].size(); j++) {
					int u = g[v][j].fi;
					int w = g[v][j].se;
					if (d[v] + w < d[u]) {
						len[u] = len[v] + 1;
						if (len[u] <= 2 * k) {
							d[u] = d[v] + w;
							q.push(mp(-d[u], u));
						}
					}
				}
			}

			while (j < sz(qu) && qu[j].fi < a) {
             	j++;
			}
			while (j < sz(qu) && qu[j].fi == a) {
				if (d[qu[j].se] != INF) {
                 	++ans;
					answ += d[qu[j].se];
				}
             	j++;
			}
		}
	}

	cout << ans << endl;
	cout << answ << endl;
}
