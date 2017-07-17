#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 1e5;

int n, m, q;
vector<int> g[N];
int depth[N], len[N];
int col[N], sz[N];
bool used[N];
double comp[N];

void paint(int v, int c) {
    ++sz[c];
    col[v] = c;
    for (int u : g[v]) {
        if (col[u] == -1) {
            paint(u, c);
        }
    }
}

void calc_depth(int v, int p = -1) {
    used[v] = true;
    for (int u : g[v]) {
        if (u != p) {
            calc_depth(u, v);
            depth[v] = max(depth[v], depth[u] + 1);
        }
    }
}

void calc(int v, int p = -1, int up_depth = 0) {
    len[v] = max(up_depth, depth[v]);

    set<pair<int, int>> ds;
    for (int u : g[v]) {
        if (u != p) {
            ds.insert({depth[u], u});
        }
    }

    for (int u : g[v]) {
        if (u != p) {
            int cur_depth = up_depth + 1;
            auto it = --ds.end();
            if (it->se == u) {
                if (ds.size() >= 2) {
                    --it;
                    cur_depth = max(cur_depth, it->fi + 2);
                }
            } else {
                cur_depth = max(cur_depth, it->fi + 2);
            }
            calc(u, v, cur_depth);
        }
    }
}

int main() {
#if __APPLE__
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
#endif

    scanf("%d%d%d", &n, &m, &q);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    memset(col, -1, n * sizeof(col[0]));
    for (int i = 0, c = 0; i < n; ++i) {
        if (col[i] == -1) {
            paint(i, c++);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            calc_depth(i);
            calc(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        comp[col[i]] += len[i] * 1.0 / sz[col[i]];
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;

        if (col[a] == col[b]) {
            puts("-1");
        } else {
            double ans = comp[col[a]] + 1.0 + comp[col[b]];
            printf("%.10lf\n", ans);
        }
    }
}
