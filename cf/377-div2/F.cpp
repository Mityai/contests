#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 4e5;

int n, m;
vector<pair<int, int>> g[N];
vector<char> ori;
unordered_set<int> bridges;
vector<pair<int, int>> edges;

int depth[N], minlvl[N];
bool used[N];

void dfs(int v, int p) {
    used[v] = true;
    minlvl[v] = depth[v] = depth[p] + 1;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (u == p) continue;
        if (!used[u]) {
            dfs(u, v);
            minlvl[v] = min(minlvl[v], minlvl[u]);
        } else {
            minlvl[v] = min(minlvl[v], depth[u]);
        }
        if (minlvl[u] > depth[v]) {
            bridges.insert(id);
        }
    }
}

bool has_bridge(int id) {
    return bridges.find(id) != bridges.end();
}

int count(int v) {
    used[v] = true;
    int cnt = 1;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (has_bridge(id) || used[u]) continue;
        cnt += count(u);
    }
    return cnt;
}

void orcycle(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (has_bridge(id)) continue;
        if (ori[id] == false) {
            edges[id] = {v, u};
            ori[id] = true;
        }
        if (!used[u]) {
            orcycle(u);
        }
    }
}

void orother(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (ori[id] == false) {
            edges[id] = {u, v};
            ori[id] = true;
        }
        if (!used[u]) {
            orother(u);
        }
    }
}

int main() {
#if __APPLE__
    freopen("F.in", "r", stdin);
    freopen("F.out", "w", stdout);
#endif

    scanf("%d%d", &n, &m);

    ori.resize(m, false);
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        edges[i] = {a, b};
    }

    dfs(0, 0);

    memset(used, 0, sizeof used);
    int maxcnt = 0, root = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            int curcnt = count(i);
            if (maxcnt < curcnt) {
                maxcnt = curcnt;
                root = i;
            }
        }
    }

    memset(used, 0, sizeof used);
    orcycle(root);

    memset(used, 0, sizeof used);
    orother(root);

    printf("%d\n", maxcnt);
    for (auto p : edges) {
        printf("%d %d\n", p.fi + 1, p.se + 1);
    }
}
