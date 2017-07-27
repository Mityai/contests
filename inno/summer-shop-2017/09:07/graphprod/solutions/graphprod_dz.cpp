#include <bits/stdc++.h>
using namespace std;

void go(int v, vector<int>& d, const vector<vector<int>>& g) {
    if (d[v] != -1) return;
    d[v] = 0;
    for (int u : g[v]) {
        go(u, d, g);
        if (
            d[v] = d[u] + 1;
        }
    }
}

int main() {
    vector<vector<int>> d(2);
    for (int t = 0; t < 2; ++t) {
        int n, m;
        scanf("%d%d", &n, &m);

        d[t].resize(n, -1);
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            g[a].push_back(b);
        }

        for (int i = 0; i < n; ++i) {
            if (d[t][i] == -1) {
                go(i, d[t], g);
            }
        }
    }

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        if (min(d[0][a], d[1][b]) & 1) {
            puts("first");
        } else {
            puts("second");
        }
    }
}
