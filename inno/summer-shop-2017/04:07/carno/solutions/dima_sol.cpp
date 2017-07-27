#include <bits/stdc++.h>
#define rank asdaslkdj
using namespace std;

const int N = 2e5;

int par[N], depth[N];

int get(int v) {
    return v == par[v] ? v : par[v] = get(par[v]);
}

void unite(int v, int u) {
    v = get(v);
    u = get(u);

    if (v == u) return;
    if (depth[v] < depth[u]) swap(v, u);
    par[v] = u;
}

const int K = 18;

int up[K][N];

int get_lca(int v, int u) {
    if (depth[v] < depth[u]) swap(v, u);
    int diff = depth[v] - depth[u];
    for (int i = 0; i < K; ++i) {
        if ((diff >> i) & 1) {
            v = up[i][v];
        }
    }
    if (v == u) return v;
    for (int i = K - 1; i >= 0; --i) {
        if (up[i][v] != up[i][u]) {
            v = up[i][v];
            u = up[i][u];
        }
    }
    return up[0][v];
}

int main() {
#if !__APPLE__
    freopen("carno.in", "r", stdin);
    freopen("carno.out", "w", stdout);
#endif

    int m;
    scanf("%d", &m);

    int num = 0;
    par[num++] = 0;
    for (int i = 0; i < m; ++i) {
        char c;
        scanf(" %c", &c);

        if (c == '+') {
            int v;
            scanf("%d", &v);
            --v;
            int cur = num++;
            par[cur] = cur;
            depth[cur] = depth[v] + 1;
            up[0][cur] = v;
            for (int j = 1; j < K; ++j) {
                up[j][cur] = up[j - 1][up[j - 1][cur]];
            }
        } else if (c == '-') {
            int v;
            scanf("%d", &v);
            --v;
            unite(v, up[0][v]);
        } else {
            int u, v;
            scanf("%d%d", &u, &v);
            --u, --v;

            int lca = get_lca(u, v);
            lca = get(lca);
            printf("%d\n", lca + 1);
        }
    }
}
