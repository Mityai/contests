#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;
const int K = 19;

int depth[N], up[K][N];

void init(int v) {
    depth[v] = depth[up[0][v]] + 1;
    for (int i = 1; i < K; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
}

int getlca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < K; ++i) {
        if ((diff >> i) & 1) {
            u = up[i][u];
        }
    }
    assert(depth[u] == depth[v]);
    if (v == u) return v;
    for (int i = K - 1; i >= 0; --i) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int dist(int v, int u) {
    int lca = getlca(v, u);
    return depth[v] + depth[u] - 2 * depth[lca];
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n - 1; ++i) {
        scanf("%d", &up[0][i]);
        --up[0][i];
    }

    for (int i = 0; i < n; ++i) {
        init(i);
    }

    int u = 0, v = 0, d = 0;
    for (int i = 1; i <= n - 1; ++i) {
        int tu = u, tv = v;
        if (dist(i, u) > d) {
            tu = u;
            tv = i;
            d = dist(i, u);
        }
        if (dist(i, v) > d) {
            tu = i;
            tv = v;
            d = dist(i, v);
        }
        u = tu;
        v = tv;
        printf("%d ", d);
    }
    puts("");
}
