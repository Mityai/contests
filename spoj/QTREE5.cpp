#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1234567890;
const int N = 1e5;
const int K = 20;

vector<int> g[N];
int en[N], ex[N], dist[N], up[N][K], sz[N], used[N], father[N], white[N];
multiset<int> q[N];
int T = 0;

void dfs(int v, int p) {
    en[v] = T++;

    dist[v] = dist[p] + 1;

    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }

    ex[v] = T++;
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

int getdist(int v, int u) {
    int lca = getlca(v, u);
    return dist[v] + dist[u] - 2 * dist[lca];
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

int go(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && sz[u] > n / 2) {
            return go(u, v, n);
        }
    }
    return v;
}

void getcenter(int v, int p) {
    calcsz(v, v);
    int center = go(v, v, sz[v]);
    if (p == -1) father[center] = center;
    else father[center] = p;
    used[center] = true;
    for (int u : g[center]) {
        if (!used[u]) {
            getcenter(u, center);
        }
    }
}

void add(int v) {
    int u = v;
    while (true) {
        q[v].insert(getdist(v, u));
        if (father[v] == v) break;
        v = father[v];
    }
}

void del(int v) {
    int u = v;
    while (true) {
        q[v].erase(q[v].find(getdist(v, u)));
        if (father[v] == v) break;
        v = father[v];
    }
}

int get(int v) {
    int ret = INF;
    int u = v;
    while (true) {
        if (!q[v].empty()) {
            ret = min(ret, getdist(v, u) + *q[v].begin());
        }
        if (father[v] == v) break;
        v = father[v];
    }
    return ret == INF ? -1 : ret;
}

int main() {
#if __APPLE__
    freopen("QTREE5.in", "r", stdin);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);
    getcenter(0, -1);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int t, v;
        scanf("%d%d", &t, &v);
        --v;

        if (t == 0) {
            if (white[v]) del(v), white[v] = false;
            else add(v), white[v] = true;
        } else {
            printf("%d\n", get(v));
        }
    }
}
