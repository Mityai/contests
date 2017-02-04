#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);

    int n, g;
    scanf("%d%d", &n, &g);

    vector< set<int> > q(g);
    vector< vector<int> > ref(n);
    for (int i = 0; i < g; i++) {
        int s;
        scanf("%d", &s);

        for (int j = 0; j < s; j++) {
            int x;
            scanf("%d", &x);
            --x;
            ref[x].push_back(i);
            q[i].insert(x);
        }
    }

    int ans = 0;
    queue<int> qu;
    qu.push(0);

    bool used[n];
    memset(used, 0, sizeof used);
    used[0] = true;

    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();

        ans++;
        for (int u : ref[v]) {
            q[u].erase(v);
            if (q[u].size() == 1) {
                int w = *q[u].begin();
                if (!used[w]) {
                    qu.push(w);
                    used[w] = true;
                }
            }
        }
    }

    printf("%d\n", ans);
}
