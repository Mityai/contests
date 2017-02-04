#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

vector<vector<int> > g;
vector<int> p;
vector<char> col;
int cycle_st = -1, cycle_nd;

bool dfs(int v) {
    col[v] = 1;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (col[u] == 1) {
            cycle_st = u;
            cycle_nd = v;

            return true;
        } else if (col[u] == 0) {
            p[u] = v;
            if (dfs(u)) {
                return true;
            }
        }
    }

    col[v] = 2;

    return false;
}

int main() {
    freopen("cycle2.in", "r", stdin);
    freopen("cycle2.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    g.resize(n);
    p.resize(n);
    col.resize(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        --a;
        --b;

        g[a].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (col[i] == 0) {
            if (dfs(i)) {
                break;
            }
        }
    }

    if (cycle_st == -1) {
        printf("NO\n");
    } else {
        vector<int> ans;

        for (int i = cycle_nd; i != cycle_st; i = p[i]) {
            ans.push_back(i + 1);
        }
        ans.push_back(cycle_st + 1);

        printf("YES\n");
        for (int i = ans.size() - 1; i >= 0; i--) {
            printf("%d ", ans[i]);
        }
    }
}