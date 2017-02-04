#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 5e4;
const int K = 22;
const int INF = 1234567890;

vector< pair<int, int> > g[N];
int sz[N], parent[N], level[N], used[N], minpath[N][K];

void calcsz(int v, int p) {
    sz[v] = 1;
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && used[u] == false) {
            calcsz(u, v);
            sz[v] += sz[u];
        }
    }
}

int dfs(int v, int p, int n) {
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && used[u] == false && sz[u] > n / 2) {
            return dfs(u, v, n);
        }
    }
    return v;
}

void calc(int v, int p, int mn, int d) {
    minpath[v][d] = mn;
    for (auto to : g[v]) {
        int u = to.fi;
        int w = to.se;
        if (u != p && used[u] == false) {
            calc(u, v, min(mn, w), d);
        }
    }
}

void build(int v, int d, int p = -1) {
    calcsz(v, v);
    int center = dfs(v, v, sz[v]);
    if (p == -1) parent[center] = center;
    else parent[center] = p;
    level[center] = d;
    calc(center, center, INF, level[center]);
    used[center] = true;
    for (auto to : g[center]) {
        int u = to.fi;
        if (!used[u]) {
            build(u, d + 1, center);
        }
    }
}

int getmin(int v, int u) {
    int pv = v, pu = u;
    while (level[pv] > level[pu]) {
        pv = parent[pv];
    }
    while (level[pu] > level[pv]) {
        pu = parent[pu];
    }
    while (pv != pu) {
        pv = parent[pv];
        pu = parent[pu];
    }
    return min(minpath[v][level[pv]], minpath[u][level[pu]]);
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        g[x].push_back({i + 1, y});
        g[i + 1].push_back({x, y});
    }

    build(0, 0);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        printf("%d\n", getmin(a, b));
    }
}
