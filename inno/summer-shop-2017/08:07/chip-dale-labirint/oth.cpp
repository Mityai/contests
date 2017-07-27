#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10, L = 19;

int n, m, u, v, timer, go[N][L], go1[N][L], go2[N][L], tin[N], out[N];
vector <int> g[N], g1[N], g2[N];

void dfs(int v, int pr) {
    tin[v] = timer++;
    go[v][0] = pr;
    for (int u: g1[v])
        if (u != pr) go2[u][0] = 1;
    for (int u: g2[v])
        if (u != pr) go1[u][0] = 1;
    for (int u: g[v])
        if (u != pr) dfs(u, v);
    out[v] = timer++;
}

bool isp(int u, int v) { return tin[u] <= tin[v] && out[v] <= out[u]; }

int lca(int u, int v) {
    if (isp(u, v)) return u;
    if (isp(v, u)) return v;
    for (int j = L - 1; j >= 0; --j)
        if (!isp(go[u][j], v)) u = go[u][j];
    return go[u][0];
}

bool can(int u, int v) {
    int u1 = u, v1 = v;
    int w = lca(u, v);
    for (int j = L - 1; j >= 0; --j)
        if (!isp(go[u][j], v1)) {
            if (!go1[u][j]) return 0;
            u = go[u][j];
        }
    if (u != w) if (!go1[u][0]) return 0;
    for (int j = L - 1; j >= 0; --j)
        if (!isp(go[v][j], u1)) {
            if (!go2[v][j]) return 0;
            v = go[v][j];
        }
    if (v != w) if (!go2[v][0]) return 0;
    return 1;
}

main() {
    cin >> n;
    for (int i = 1; i < n; ++i){
        scanf("%d%d", &u, &v);
        g1[u].push_back(v);
        g2[v].push_back(u);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 1);
    go[1][0] = go1[1][0] = go2[1][0] = 1;
    for (int j = 1; j < L; ++j)
        for (int i = 1; i <= n; ++i) {
            go[i][j] = go[go[i][j - 1]][j - 1];
            go1[i][j] = int(go1[i][j - 1] && go1[go[i][j - 1]][j - 1]);
            go2[i][j] = int(go2[i][j - 1] && go2[go[i][j - 1]][j - 1]);
        }
    cin >> m;
    while (m--) {
        scanf("%d%d", &u, &v);
        puts(can(u, v) ? "Yes" : "No");
    }
    return 0;
}
