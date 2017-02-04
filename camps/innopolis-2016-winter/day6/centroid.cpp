#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int INF = 1234567890;
const int N = 3e5;
const int K = 20;

vector< pair<int, int> > g[N];
int sz[N], father[N], used[N];
multiset<int> ans[N];
int up[N][K], en[N], ex[N], dist[N];
int T = 0;

void calcLca(int v, int p, int w = 0) {
    en[v] = T++;
    dist[v] = w;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p) {
            calcLca(u, v, w + to.se);
        }
    }
    ex[v] = T++;
}

bool isAnc(int a, int b) {
    return en[a] <= en[b] && ex[b] <= ex[a];
}

int getLca(int v, int u) {
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[v][i], u)) {
            v = up[v][i];
        }
    }
    return isAnc(v, u) ? v : up[v][0];
}

int getDist(int v, int u) {
    int lca = getLca(v, u);
    return dist[v] + dist[u] - 2 * dist[lca];
}

void calcSz(int v, int p = -1) {
    sz[v] = 1;
    for (auto to : g[v]) {
        int u = to.fi;
        if (!used[u] && u != p) {
            calcSz(u, v);
            sz[v] += sz[u];
        }
    }
}

int dfs(int v, int w, int p) {
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p && !used[u] && sz[u] > w / 2) {
            return dfs(u, w, v);
        }
    }
    return v;
}

void makeCentroid(int v, int p = -1) {
    calcSz(v);
    int current = dfs(v, sz[v], v);
    father[current] = (p == -1 ? current : p);
    used[current] = true;
    for (auto to : g[current]) {
        int u = to.fi;
        if (!used[u]) {
            makeCentroid(u, current);
        }
    }
}

void addVert(int v) {
    int u = v;
    while (true) {
        ans[v].insert(getDist(v, u));
        if (v == father[v]) break;
        v = father[v];
    }
}

void delVert(int v) {
    int u = v;
    while (true) {
        auto it = ans[v].find(getDist(v, u));
        assert(it != ans[v].end());
        ans[v].erase(it);
        if (v == father[v]) break;
        v = father[v];
    }
}

int getNearest(int v) {
    int u = v;
    int ret = INF;
    while (true) {
        if (!ans[v].empty()) {
            ret = min(ret, getDist(u, v) + *ans[v].begin());
        }
        if (v == father[v]) break;
        v = father[v];
    }
    assert(ret != INF);
    return ret;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("treeeg.in", "r", stdin);
    freopen("treeeg.out", "w", stdout);
#endif

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    calcLca(0, 0);
    makeCentroid(0);
    addVert(0);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char c;
        int v;
        scanf(" %c%d", &c, &v);
        --v;

        if (c == '+') {
            addVert(v);
        } else if (c == '-') {
            delVert(v);
        } else {
            printf("%d\n", getNearest(v));
        }
    }
}

