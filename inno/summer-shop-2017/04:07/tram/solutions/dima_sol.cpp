#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
const int K = 17;

int tin[N], tout[N], up[K][N];
int timer = 0;

void go(int v, int p) {
    up[0][v] = p;
    tin[v] = timer++;
    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
    tout[v] = timer++;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int getlca(int v, int u) {
    if (is_anc(v, u)) return v;
    if (is_anc(u, v)) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (!is_anc(up[i][v], u)) {
            v = up[i][v];
        }
    }
    return is_anc(v, u) ? v : up[0][v];
}

int val[N], lca_val[N];
int ans = 0;

int dfs(int v, int p) {
    int paths = val[v];
    for (int u : g[v]) {
        if (u != p) {
            int cur = dfs(u, v);
            if (cur == 0) {
                ++ans;
            }
            paths += cur;
        }
    }
    paths -= 2 * lca_val[v];
    return paths;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    go(0, 0);
    for (int i = 1; i < K; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        int lca = getlca(u, v);
        ++val[u];
        ++val[v];
        ++lca_val[lca];
    }

    dfs(0, 0);
    printf("%d\n", ans);
}
