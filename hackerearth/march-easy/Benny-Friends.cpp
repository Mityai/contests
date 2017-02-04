#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1234567890;
const int N = 1e5;
const int K = 19;

vector< pair<int, int> > G[N], g[N];
multiset<int> q[N];

int cnt[N], en[N], ex[N], maxup[N][K], up[N][K], father[N], cost[N], sz[N];
bool used[N], was[N];
int T = 0;

void dfs(int v, int p) {
    was[v] = true;
    en[v] = T++;
    up[v][0] = p;
    maxup[v][0] = cost[v];
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        maxup[v][i] = max(maxup[v][i - 1], maxup[up[v][i - 1]][i - 1]);
    }
    for (auto to : g[v]) {
        int u = to.fi;
        int w = to.se;
        if (u != p) {
            cost[u] = w;
            dfs(u, v);
        }
    }
    ex[v] = T++;
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

int getcenter(int v, int p, int n) {
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && !used[u] && sz[u] > n / 2) {
            return getcenter(u, v, n);
        }
    }
    return v;
}

void build(int v, int p) {
    calcsz(v, v);
    int center = getcenter(v, v, sz[v]);
    if (p == -1) father[center] = center;
    else father[center] = p;
    used[center] = true;
    for (auto to : g[center]) {
        int u = to.fi;
        if (!used[u]) {
            build(u, center);
        }
    }
}

bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}

int getlca(int v, int u) {
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return isAnc(v, u) ? v : up[v][0];
}

int getmax(int v, int lca) {
    int mx = 0;
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], lca)) {
            mx = max(mx, maxup[v][i]);
            v = up[v][i];
        }
    }
    if (v != lca) mx = max(mx, maxup[v][0]);
    return mx;
}

int maxonpath(int v, int u) {
    int lca = getlca(v, u);
    return max(getmax(v, lca), getmax(u, lca));
}

void add(int v) {
    int u = v;
    while (true) {
        q[v].insert(maxonpath(v, u));
        if (v == father[v]) break;
        v = father[v];
    }
}

void del(int v) {
    int u = v;
    while (true) {
        q[v].erase(q[v].find(maxonpath(v, u)));
        if (v == father[v]) break;
        v = father[v];
    }
}

int get(int v) {
    int ret = INF;
    int u = v;
    while (true) {
        int mx = maxonpath(v, u);
        if (!q[v].empty()) {
            int mn = *q[v].begin();
            ret = min(ret, max(mx, mn));
        }
        if (v == father[v]) break;
        v = father[v];
    }
    return ret == INF ? -1 : ret;
}

int main() {
#if __APPLE__
    freopen("friends.in", "r", stdin);
    freopen("friends.out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        G[a].push_back({b, w});
        G[b].push_back({a, w});
    }

    for (int i = 0; i < n; i++) {
        if (!was[i]) {
            vector<int> dist(n, INF), p(n, -1);
            vector<char> mark(n, false);
            dist[i] = 0;
            set< pair<int, int> > r;
            r.insert({dist[i], i});
            while (!r.empty()) {
                int v = r.begin()->se;
                r.erase(r.begin());
                if (p[v] != -1) {
                    g[v].push_back({p[v], dist[v]});
                    g[p[v]].push_back({v, dist[v]});
                }
                mark[v] = true;

                for (auto to : G[v]) {
                    int u = to.fi;
                    int w = to.se;
                    if (mark[u] == false && dist[u] > w) {
                        r.erase({dist[u], u});
                        p[u] = v;
                        dist[u] = w;
                        r.insert({dist[u], u});
                    }
                }
            }

            dfs(i, i);
            build(i, -1);
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        char c;
        int v;
        scanf(" %c%d", &c, &v);
        --v;

        if (c == '+') {
            cnt[v]++;
            if (cnt[v] == 1) {
                add(v);
            }
        } else if (c == '-') {
            cnt[v]--;
            if (cnt[v] == 0) {
                del(v);
            }
        } else {
            printf("%d\n", get(v));
        }
    }
}
