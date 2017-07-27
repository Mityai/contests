#include <bits/stdc++.h>
using namespace std;

const int N = 222;

int n;
vector<int> g[N];
int match[N], p[N], base[N];
bool used[N], blossom[N];

void mark_path(int v, int b, int child) {
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = child;
        child = match[v];
        v = p[match[v]];
    }
}

int get_lca(int v, int u) {
    vector<char> mark(n, false);
    while (true) {
        v = base[v];
        mark[v] = true;
        if (match[v] == -1) break;
        v = p[match[v]];
    }
    while (true) {
        u = base[u];
        if (mark[u]) return u;
        u = p[match[u]];
    }
}

int find_path(int root) {
    memset(used, 0, n * sizeof(used[0]));
    memset(p, -1, n * sizeof(p[0]));
    for (int i = 0; i < n; ++i) {
        base[i] = i;
    }

    queue<int> q;
    q.push(root);
    used[root] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
            if (base[u] == base[v] || match[v] == u) continue;
            if (u == root || (match[u] != -1 && p[match[u]] != -1)) {
                int curbase = get_lca(v, u);
                memset(blossom, false, n * sizeof(blossom[0]));
                mark_path(v, curbase, u);
                mark_path(u, curbase, v);
                for (int i = 0; i < n; ++i) {
                    if (blossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            q.push(i);
                        }
                    }
                }
            } else {
                if (p[u] == -1) {
                    p[u] = v;
                    if (match[u] == -1) {
                        return u;
                    }
                    u = match[u];
                    used[u] = true;
                    q.push(u);
                }
            }
        }
    }
    return -1;
}

int main() {
    //freopen("1099.in", "r", stdin); freopen("1099.out", "w", stdout);

    scanf("%d", &n);

    int a, b;
    while (scanf("%d%d", &a, &b) == 2) {
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    memset(match, -1, sizeof match);
    for (int v = 0; v < n; ++v) {
        if (match[v] == -1) {
            for (int u : g[v]) {
                if (match[u] == -1) {
                    match[u] = v;
                    match[v] = u;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            int v = find_path(i);
            while (v != -1) {
                int pv = p[v], ppv = match[pv];
                match[v] = pv, match[pv] = v;
                v = ppv;
            }
        }
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        if (i < match[i]) {
            ans.push_back({i, match[i]});
        }
    }

    printf("%d\n", 2 * int(ans.size()));
    for (auto& v : ans) {
        printf("%d %d\n", v.first + 1, v.second + 1);
    }
}
