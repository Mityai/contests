#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[b].push_back(a);
        ++deg[a];
    }

    set<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) {
            q.insert(i);
        }
    }

    vector<int> ans(n);
    int cur = n;
    while (!q.empty()) {
        int v = *--q.end();
        q.erase(--q.end());
        ans[v] = cur--;
        for (int u : g[v]) {
            if (--deg[u] == 0) {
                q.insert(u);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    puts("");
}
