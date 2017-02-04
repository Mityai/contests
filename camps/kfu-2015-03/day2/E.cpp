#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    freopen("dwarf.in", "r", stdin);
    freopen("dwarf.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    set< pair<int, int> > q;
    int cost[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", cost + i);
        q.insert({cost[i], i});
    }

    vector< vector< pair<int, int> > > g(n);
    for (int i = 0; i < m; i++) {
        int a, x, y;
        scanf("%d%d%d", &a, &x, &y);
        --a, --x, --y;
        g[x].push_back({y, a});
        g[y].push_back({x, a});
    }

    while (!q.empty()) {
        int v = q.begin()->se;
        q.erase(q.begin());

        for (auto to : g[v]) {
            int u = to.fi, w = to.se;
            if (cost[w] > cost[u] + cost[v]) {
                q.erase({cost[w], w});
                cost[w] = cost[u] + cost[v];
                q.insert({cost[w], w});
            }
        }
    }

    printf("%d\n", cost[0]);
}
