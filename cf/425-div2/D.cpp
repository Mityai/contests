#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int N = 1e5;
const int K = 17;

vector<int> g[N];
int depth[N], up[K][N], en[N], ex[N];

void dfs(int v, int p) {
    static int T = 0;
    en[v] = T++;

    depth[v] = depth[p] + 1;

    up[0][v] = p;
    for (int i = 1; i < K; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }

    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }

    ex[v] = T++;
}

bool is_anc(int v, int u) {
    return en[v] <= en[u] && ex[u] <= ex[v];
}

int get_lca(int v, int u) {
    if (is_anc(v, u)) return v;
    if (is_anc(u, v)) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (!is_anc(up[i][v], u)) v = up[i][v];
    }
    return up[0][v];
}

int get(int s, int f, int t) {
    if (is_anc(s, f)) {
        int tf = get_lca(t, f);
        return min(depth[f] - depth[s], depth[f] - depth[tf]) + 1;
    } else if (is_anc(f, s)) {
        int st = get_lca(s, t);
        return max(0, depth[st] - depth[f]) + 1;
    } else {
        int sf = get_lca(s, f);
        int st = get_lca(s, t);
        if (en[sf] < en[st] && ex[st] < ex[sf]) {
            return depth[f] - depth[sf] + depth[st] - depth[sf] + 1;
        } else {
            int tf = get_lca(t, f);
            if (is_anc(sf, tf)) {
                return depth[f] - depth[tf] + 1;
            } else {
                return depth[f] - depth[sf] + 1;
            }
        }
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n - 1; ++i) {
        int p;
        scanf("%d", &p);
        --p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    dfs(0, 0);
    for (int i = 0; i < q; ++i) {
        vector<pair<int, int>> a(3);
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &a[j].se);
            --a[j].se;
            a[j].fi = j;
        }
        int ans = 0;
        do {
            int s = a[0].se;
            int f = a[1].se;
            int t = a[2].se;
            ans = max(ans, get(s, f, t));
        } while (next_permutation(a.begin(), a.end()));
        printf("%d\n", ans);
    }
}
