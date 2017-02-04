#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5;
const int K = 20;

vector<int> g[N];

int en[N], ex[N], depth[N], up[N][K], sz[N];
ll sumd[N], sums[N];
int T = 0;

void dfs(int v, int p, int d) {
    en[v] = T++;

    depth[v] = d;

    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v, d + 1);
            sz[v] += sz[u];
            sumd[v] += sumd[u] + sz[u];
        }
    }

    ex[v] = T++;
}

void go(int v, int p) {
    if (v != p) {
        sums[v] = (sums[p] + sz[0] - sz[p]) + (sumd[p] - (sumd[v] + sz[v]) + sz[p] - sz[v]);
    }
    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
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

int dist(int v, int u) {
    int lca = getLca(v, u);
    return depth[v] + depth[u] - 2 * depth[lca];
}

int getP(int v, int u) {
    for (int i = K - 1; i >= 0; i--) {
        if (!isAnc(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return u;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0, 0);
    go(0, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;

        if (isAnc(b, a)) swap(a, b);

        if (isAnc(a, b)) {
            int pb = getP(a, b);
            double suma = sums[a] + sumd[a] - (sumd[pb] + sz[pb]);
            double sza = sz[0] - sz[pb];
            double ans = 1 + dist(a, b) + (double)sumd[b] / (double)sz[b] + suma / sza;
            printf("%.10lf\n", ans);
        } else {
            double ans = 1 + dist(a, b) + (double)sumd[a] / (double)sz[a] + (double)sumd[b] / (double)sz[b];
            printf("%.10lf\n", ans);
        }
    }
}
