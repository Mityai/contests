#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e5;
const int K = 17;

struct Ev {
    int d, c, t;
};

vector< pair<int, int> > g[N];
int sz[N], parent[N], used[N], depth[N], up[N][K], en[N], ex[N];
vector<Ev> ev[N];
int T = 0;

void buildlca(int v, int p, int d) {
    en[v] = T++;
    depth[v] = d;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto to : g[v]) {
        int u = to.fi;
        int w = to.se;
        if (u != p) {
            buildlca(u, v, d + w);
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
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && !used[u]) {
            calcsz(u, v);
            sz[v] += sz[u];
        }
    }
}

int dfs(int v, int p, int n) {
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && !used[u] && sz[u] > n / 2) {
            return dfs(u, v, n);
        }
    }
    return v;
}

void build(int v, int p = -1) {
    calcsz(v, v);
    int center = dfs(v, v, sz[v]);
    if (p == -1) parent[center] = center;
    else parent[center] = p;
    used[center] = true;
    for (auto to : g[center]) {
        int u = to.fi;
        if (!used[u]) {
            build(u, center);
        }
    }
}

inline void add(int v, int d, int c, int t) {
    Ev cur = {d, c, t};
    while (!ev[v].empty() && ev[v].back().d <= cur.d) {
        ev[v].pop_back();
    }
    ev[v].push_back(cur);
}

inline void paint(int v, int d, int c, int t) {
    int pv = v;
    while (true) {
        int ds = d - dist(v, pv);
        if (ds >= 0) {
            add(pv, ds, c, t);
        }
        if (parent[pv] == pv) break;
        pv = parent[pv];
    }
}

inline int bins(int v, int d) {
    int lb = -1, rb = (int)ev[v].size();
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        if (ev[v][mb].d >= d) lb = mb;
        else rb = mb;
    }
    return lb;
}

inline int get(int v) {
    int col = 0, t = -1;
    int pv = v;
    while (true) {
        int ds = dist(v, pv);
        int j = bins(pv, ds);
        if (j != -1) {
            if (ev[pv][j].t > t) {
                col = ev[pv][j].c;
                t = ev[pv][j].t;
            }
        }
        if (parent[pv] == pv) break;
        pv = parent[pv];
    }
    return col;
}

int main() {
    freopen("lwdb.in", "r", stdin);
    freopen("lwdb.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    buildlca(0, 0, 0);
    build(0);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int v, d, c;
            scanf("%d%d%d", &v, &d, &c);
            --v;
            paint(v, d, c, i);
        } else {
            int v;
            scanf("%d", &v);
            --v;
            printf("%d\n", get(v));
        }
    }
}
