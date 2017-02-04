#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int INF = 1234567890;
const int N = 1e5;
const int K = 17;

vector<int> g[N];
int sz[N], parent[N], used[N], col[N], depth[N], up[N][K], en[N], ex[N];
int T = 0;
unordered_map<int, int> near[N];

void buildlca(int v, int p) {
    en[v] = T++;
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : g[v]) {
        if (u != p) {
            buildlca(u, v);
        }
    }
    ex[v] = T++;
}

inline bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}

inline int getlca(int v, int u) {
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return isAnc(v, u) ? v : up[v][0];
}

inline int dist(int v, int u) {
    int lca = getlca(v, u);
    return depth[v] + depth[u] - 2 * depth[lca];
}

void calcsz(int v, int p) {
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            calcsz(u, v);
            sz[v] += sz[u];
        }
    }
}

int dfs(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) {
            return dfs(u, v, n);
        }
    }
    return v;
}

void calc(int v, int p, int center, int d) {
    if (near[center].find(col[v]) == near[center].end()) {
        near[center][col[v]] = d;
    } else {
        near[center][col[v]] = min(near[center][col[v]], d);
    }
    for (int u : g[v]) {
        if (u != p && !used[u]) {
            calc(u, v, center, d + 1);
        }
    }
}

void build(int v, int p = -1) {
    calcsz(v, v);
    int center = dfs(v, v, sz[v]);
    if (p == -1) parent[center] = center;
    else parent[center] = p;
    calc(center, center, center, 0);
    used[center] = true;
    for (int u : g[center]) {
        if (!used[u]) {
            build(u, center);
        }
    }
}

inline int get(int v, int c) {
    int ret = INF;
    int u = v;
    while (true) {
        int d = INF;
        if (near[u].find(c) != near[u].end()) {
            d = near[u][c];
        }
        ret = min(ret, d + dist(v, u));
        if (parent[u] == u) break;
        u = parent[u];
    }
    return ret == INF ? -1 : ret;
}

int main() {
    freopen("centroid.in", "r", stdin);
    freopen("centroid.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int a = 1; a <= n - 1; a++) {
        int b;
        scanf("%d", &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &col[i]);
    }

    buildlca(0, 0);
    build(0);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int v, c;
        scanf("%d%d", &v, &c);
        printf("%d ", get(v, c));
    }
    puts("");
}
