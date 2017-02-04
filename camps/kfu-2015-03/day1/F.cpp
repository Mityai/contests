#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 5e3;

int n, m;
vector< pair<int, int> > g[N];
set<int> bridges;
int col[N], depth[N], mind[N];
bool used[N];

void dfs(int v, int p) {
    used[v] = true;
    depth[v] = mind[v] = depth[p] + 1;
    for (auto to : g[v]) {
        int u = to.fi;
        if (u != p) {
            if (used[u]) {
                mind[v] = min(mind[v], depth[u]);
            } else {
                dfs(u, v);
                mind[v] = min(mind[v], mind[u]);
                if (depth[v] < mind[u]) bridges.insert(to.se);
            }
        }
    }
}

void go(int v, int c) {
    col[v] = c;
    used[v] = true;
    for (auto to : g[v]) {
        int u = to.fi, id = to.se;
        if (!used[u] && bridges.find(id) == bridges.end()) {
            go(u, c);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    vector< pair<int, int> > edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        edges[i] = {a, b};
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    dfs(0, 0);

    memset(used, 0, sizeof used);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            go(i, cnt++);
        }
    }

    int deg[cnt];
    memset(deg, 0, sizeof deg);

    for (int i = 0; i < m; i++) {
        int a = edges[i].fi, b = edges[i].se;
        if (col[a] != col[b]) {
            deg[col[a]]++, deg[col[b]]++;
        }
    }

    int ans = 0;
    for (int i = 0; i < cnt; i++) {
        ans += (deg[i] == 1);
    }

    printf("%d\n", max(0, ans - 1));
}
