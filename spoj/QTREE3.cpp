#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 1e5;

vector<int> g[N];
set< pair<int, int> > sa[N];

int pos[N], par[N], sz[N], no[N], top[N];
bool in[N];
int tc = 0;

void dfs(int v, int p) {
    par[v] = p;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            sz[v] += sz[u];
        }
    }
}

void go(int v, int p) {
    if (v == p || 2 * sz[v] <= sz[p]) {
        no[v] = tc++;
        top[no[v]] = v;
        pos[v] = 0;
    } else {
        no[v] = no[p];
        pos[v] = pos[p] + 1;
    }

    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

int get(int v) {
    int best = -2;
    while (true) {
        if (!sa[no[v]].empty()) {
            auto q = *sa[no[v]].begin();
            int cur = q.fi;
            if (cur <= pos[v]) {
                best = q.se;
            }
        }
        if (v == par[top[no[v]]]) break;
        v = par[top[no[v]]];
    }
    return best;
}

void add(int v) {
    sa[no[v]].insert({pos[v], v});
}

void del(int v) {
    sa[no[v]].erase({pos[v], v});
}

void solve() {
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);
    go(0, 0);

    for (int i = 0; i < q; i++) {
        int x, v;
        scanf("%d%d", &x, &v);
        --v;
        if (x == 0) {
            in[v] ^= 1;
            if (in[v]) add(v);
            else del(v);
        } else {
            printf("%d\n", get(v) + 1);
        }
    }
}

int main() {
#if __APPLE__
    freopen("QTREE3.in", "r", stdin);
    freopen("QTREE3.out", "w", stdout);
#endif

    solve();
}
