#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 3e5;

int mark[N];
vector< vector<int> > g;

bool dfs(int v) {
    mark[v] = 1;
    bool ok = false;
    for (int u : g[v]) {
        if (mark[u] == 1) return true;
        if (mark[u] == 0) ok |= dfs(u);
    }
    mark[v] = 2;
    return ok;
}

void solve() {
    int n;
    scanf("%d", &n);

    map<int, int> all;
    vector< vector<int> > e(n);
    for (int i = 0; i < n; i++) {
        int l;
        scanf("%d", &l);
        
        e[i].resize(l);
        for (int j = 0; j < l; j++) {
            scanf("%d", &e[i][j]);
            all[e[i][j]] = 0;
        }
    }

    int C = 0;
    for (auto &x : all) {
        x.se = C++;
    }

    for (auto &x : e) {
        for (auto &y : x) {
            y = all[y];
        }
    }

    memset(mark, 0, C * sizeof(mark[0]));

    g.clear();

    g.resize(C);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < (int)e[i].size(); j++) {
            int x = e[i][j], y = e[i][j - 1];
            g[y].push_back(x);
        }
    }
    bool ok = false;
    for (int i = 0; i < C; i++) {
        if (mark[i] == 0) {
            ok |= dfs(i);
        }
        if (ok) {
            puts("No");
            return;
        }
    }
    puts("Yes");
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        solve();
    }
}
