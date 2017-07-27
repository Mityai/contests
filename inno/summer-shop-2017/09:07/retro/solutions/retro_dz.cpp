#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("retro.in", "r", stdin);
    freopen("retro.out", "w", stdout);

    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        vector<vector<int>> g(n);
        vector<int> out(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a, --b;
            g[b].push_back(a);
            ++out[a];
        }
        queue<int> q;
        vector<int> win(n);
        for (int i = 0; i < n; ++i) {
            if (out[i] == 0) {
                win[i] = -1;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : g[v]) {
                --out[u];
                if (win[v] == -1) {
                    if (win[u] == 0) {
                        win[u] = 1;
                        q.push(u);
                    }
                } else {
                    if (out[u] == 0 && win[u] == 0) {
                        win[u] = -1;
                        q.push(u);
                    }
                }
            }
        }
        for (int b : win) {
            if (b == 1) {
                puts("FIRST");
            } else if (b == 0) {
                puts("DRAW");
            } else {
                puts("SECOND");
            }
        }
        puts("");
    }
}
