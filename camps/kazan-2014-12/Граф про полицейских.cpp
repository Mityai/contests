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
 
#define sz(a) a.size()
#define len(s) s.length()
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
const int INF = 1234567890;
const ll INF_LL = LLONG_MAX - INF;
const int MAXN = 1e5;
const int MAXM = 1e4;
const int MOD = 1e9 + 7;
const double eps = 1e-6;

int n, m;
vector<int> order, curcomp;
vector<char> mark;
vector<vector<int> > g, gt;

void dfs1(int v) {
 	mark[v] = true;
	for (int i = 0; i < g[v].size(); i++) {
		int u = g[v][i];
     	if (mark[u] == false) {
         	dfs1(u);
		}
	}

	order.push_back(v);
}

void dfs2(int v) {
 	mark[v] = true;
	for (int i = 0; i < gt[v].size(); i++) {
		int u = gt[v][i];
     	if (mark[u] == false) {
         	dfs2(u);
		}
	}

	curcomp.push_back(v);
}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
    #else
        freopen("police.in", "r", stdin);
        freopen("police.out", "w", stdout);
    #endif

	cin >> n >> m;

	g.resize(n);
	gt.resize(n);
	mark.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		--a;
		--b;

		g[a].push_back(b);
		gt[b].push_back(a);
	}

	mark.assign(n, false);
	for (int i = 0; i < n; i++) {
     	if (mark[i] == false) {
         	dfs1(i);
		}
	}

	int compcnt = 0;
	vector<int> comp_ref(n);
	mark.assign(n, false);
	for (int i = 0; i < n; i++) {
		int v = order[n - i - 1];
     	if (mark[v] == false) {
			curcomp.clear();
			dfs2(v);

			for (int j = 0; j < sz(curcomp); j++) {
             	comp_ref[curcomp[j]] = compcnt;
			}
			++compcnt;
		}
	}

	vector<char> in(compcnt, false), out(compcnt, false);
	vector<set<int> > comp_set(compcnt);
	for (int i = 0; i < n; i++) {
     	for (int j = 0; j < g[i].size(); j++) {
			int u = g[i][j];
			if (comp_ref[i] != comp_ref[u]) {
             	comp_set[comp_ref[i]].insert(comp_ref[u]);
				in[comp_ref[u]] = true;
				out[comp_ref[i]] = true;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < compcnt; i++) {
     	if (in[i] == false || out[i] == false) {
         	++ans;
		}
	}

	cout << max(1, ans) << endl;
}
