#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = int(1e5);
const int M = 2 * N;
const int K = 20;
const int s = 0;

int n, m;
int order[M];
int depth[M];
int firstIn[N];
pair<int, int> f[K][M];
int logK[M];

vector<int> g[N];

void calculate() {
    for (int i = 0; i < m; i++) {
        f[0][i] = {depth[i], order[i]};
    }

    for (int k = 0; (1 << (k + 1)) < m; k++) {
        for (int i = 0; i < m; i++) {
            if (f[k][i].fi < f[k][i + (1 << k)].fi) {
                f[k + 1][i] = f[k][i];
            } else {
                f[k + 1][i] = f[k][i + (1 << k)];
            }
        }
    }

    for (int i = 2; i < m; i++) {
        logK[i] = logK[i >> 1] + 1;
    }
}

inline int getMin(int L, int R) {
    int k = logK[R - L + 1];
    if (f[k][L].fi < f[k][R - (1 << k) + 1].fi) {
        return f[k][L].se;
    }
    return f[k][R - (1 << k) + 1].se;
}

void dfs(int v, int d = 0) {
    firstIn[v] = m;
    depth[m] = d;
    order[m++] = v;
    
    for (int u : g[v]) {
        dfs(u, d + 1);
        depth[m] = d;
        order[m++] = v;
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("lca2.in", "r", stdin);
    freopen("lca2.out", "w", stdout);
#endif

    int n, q;
    scanf("%d%d", &n, &q);

    for (int v = 1; v <= n - 1; v++) {
        int parent;
        scanf("%d", &parent);

        g[parent].push_back(v);
    }

    dfs(s);
    calculate();

    int a1, a2;
    scanf("%d%d", &a1, &a2);

    ll x, y, z;
    scanf("%lld%lld%lld", &x, &y, &z);

    ll ans = 0;
    for (int i = 1, anc = 0; i <= q; i++) {
        int fiV = firstIn[(a1 + anc) % n];
        int fiU = firstIn[a2];
        if (fiV > fiU) {
            swap(fiV, fiU);
        }
        anc = getMin(fiV, fiU);
        ans += anc;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    printf("%lld\n", ans);
}
