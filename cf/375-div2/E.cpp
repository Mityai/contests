#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 200;

vector<pair<int, int>> g[N];
vector<pair<int, int>> edges;
vector<char> used;
vector<int> col;

void clear() {
    for (int i = 0; i != N; ++i) g[i].clear();
}

void orient(int v) {
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (!used[id]) {
            used[id] = true;
            if (edges[id].fi == u) {
                swap(edges[id].fi, edges[id].se);
            }
            orient(u);
        }
    }
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<int> deg(n);
    edges.resize(m);
    for (int i = 0; i != m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        ++deg[a];
        ++deg[b];
        edges[i] = {a, b};
    }

    int ed = m;
    for (int v = 0; v < n; ++v) {
        if (deg[v] % 2 == 0) continue;
        for (int u = v + 1; u < n; ++u) {
            if (deg[v] % 2 == 1 && deg[u] % 2 == 1) {
                g[v].push_back({u, ed});
                g[u].push_back({v, ed++});
                ++deg[v];
                ++deg[u];
                edges.push_back({u, v});
                break;
            }
        }
    }

    used.assign(ed, false);
    for (int v = 0; v != n; ++v) {
        orient(v);
    }

    vector<int> indeg(n), outdeg(n);
    for (int i = 0; i != m; ++i) {
        ++indeg[edges[i].se];
        ++outdeg[edges[i].fi];
    }

    int anscnt = 0;
    for (int v = 0; v != n; ++v) {
        if (indeg[v] == outdeg[v]) {
            ++anscnt;
        }
    }

    printf("%d\n", anscnt);
    for (int i = 0; i != m; ++i) {
        printf("%d %d\n", edges[i].fi + 1, edges[i].se + 1);
    }
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    while (t--) {
        clear();
        solve();
    }
}
