#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

typedef long long ll;

using namespace std;

int st = -1;
vector<vector<int> > g;
vector<char> c;
vector<int> ans;

bool dfs(int v) {
    c[v] = 1;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (c[u] == 0) {
            if (dfs(u)) return true;
        } else if (c[u] == 1) {
            st = 0;
            return true;
        }
    }

    c[v] = 2;

    ans.push_back(v);

    return false;
}

int main() {
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    c.resize(n, 0);
    g.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        --a, --b;

        g[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (!c[i]) {
            dfs(i);
        }
    }

    if (st == -1) {
        for (int i = n - 1; i >= 0; i--) {
            printf("%d ", ans[i] + 1);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
}