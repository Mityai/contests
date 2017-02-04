#include <bits/stdc++.h>
#define se second
using namespace std;

const int N = 2e5;
const int K = 19;

vector<int> g[N];
int depth[N], en[N], ex[N], up[N][K], logK[N + 1];
pair<int, int> f[K][N];
int T = 0;

void dfs(int v, int p) {
    en[v] = T++;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    depth[v] = depth[p] + 1;
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

void build(int n) {
    --n;
    for (int i = 0; i < n; i++) {
        int lca = getlca(i, i + 1);
        f[0][i] = {depth[lca], lca};
    }
                                   
    for (int k = 1; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) {
            f[k][i] = min(f[k - 1][i], f[k - 1][i + (1 << (k - 1))]);
        }
    }

    for (int i = 2; i <= N; i++) {
        logK[i] = logK[i / 2] + 1;
    }
}

int get(int l, int r) {
    int k = logK[r - l + 1];
    return min(f[k][l], f[k][r - (1 << k) + 1]).se;
}

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
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
    build(n);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        --l, --r;

        if (l == r) {
            printf("%d\n", l + 1);
        } else {
            printf("%d\n", get(l, r - 1) + 1);
        }
    }
}
