#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

const int N = 1e5;
const int K = 20;

vector< pair<int, int> > g[N];
int en[N], ex[N], up[N][K], dist[N], depth[N];
int T = 0;

void dfs(int v, int p, int d) {
    en[v] = T++;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    depth[v] = depth[p] + 1;
    dist[v] = d;

    for (int i = 0; i < (int)g[v].size(); i++) {
        int u = g[v][i].fi;
        int w = g[v][i].se;
        if (u != p) {
            dfs(u, v, d + w);
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

int jump(int v, int k) {
    for (int i = 0; i < K; i++) {
        if ((k >> i) & 1) {
            v = up[v][i];
        }
    }
    return v;
}

int getdist(int v, int u) {
    int lca = getlca(v, u);
    return dist[v] + dist[u] - 2 * dist[lca];
}

int getkth(int v, int u, int k) {
    int lca = getlca(v, u);
    int len = depth[v] + depth[u] - 2 * depth[lca] + 1;
    int ret;
    if (depth[v] - depth[lca] + 1 >= k) {
        ret = jump(v, k - 1);
    } else {
        ret = jump(u, len - k);
    }
    return ret;
}

void clear(int n) {
    for (int i = 0; i < n; i++) g[i].clear();
    memset(depth, 0, n * sizeof(depth[0]));
    T = 0;
}

void solve() {
    int n;
    scanf("%d", &n);

    clear(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        --a, --b;
        g[a].push_back(mp(b, w));
        g[b].push_back(mp(a, w));
    }

    dfs(0, 0, 0);

    char s[6];
    while (scanf(" %s", s)) {
        if (s[1] == 'I') {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            printf("%d\n", getdist(a, b));
        } else if (s[0] == 'K') {
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);
            --a, --b;
            printf("%d\n", getkth(a, b, k) + 1);
        } else {
            break;
        }
    }
}

int main() {
#if __APPLE__
    freopen("QTREE2.in", "r", stdin);
    freopen("QTREE2.out", "w", stdout);
#endif

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        solve();
    }
}

