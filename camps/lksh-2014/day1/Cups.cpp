#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>

#define fi first
#define se second

#define INF 1000000000

typedef long long ll;

using namespace std;

struct Edge {
    int t, w;
};

vector<vector<pair<int, Edge> > > g;

int main() {
    freopen("cups.in", "r", stdin);
    freopen("cups.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    g.resize(n);
    vector<int> weight(m);

    for (int i = 0; i < m; i++) {
        Edge e;
        int a, b;
        scanf("%d%d%d%d", &a, &b, &e.t, &e.w);

        weight[i] = e.w;

        --a;
        --b;

        g[a].push_back(make_pair(b, e));
        g[b].push_back(make_pair(a, e));
    }

    sort(weight.begin(), weight.end());

    int l = 0, r = (int)weight.size();
    int ans = 0;
    while (l < r) {
        int m = (l + r) / 2;

        int w = weight[m];

        vector<int> d(n, INF);
        d[0] = 0;

        set<pair<int, int> > s;
        s.insert(make_pair(0, 0));

        while (!s.empty()) {
            int v = s.begin()->se;
            s.erase(s.begin());

            for (size_t j = 0; j < g[v].size(); j++) {
                int u = g[v][j].fi, cur_t = g[v][j].se.t, cur_w = g[v][j].se.w;
                
                if (cur_w >= w && d[v] + cur_t < d[u]) {
                    s.erase(make_pair(d[u], u));
                    d[u] = d[v] + cur_t;
                    s.insert(make_pair(d[u], u));
                }
            }
        }

        if (d[n - 1] <= 1440) {
            ans = max(ans, (w - 3000000) / 100);
            l = m + 1;
        } else {
            r = m;
        }
    }

    printf("%d\n", ans);
}