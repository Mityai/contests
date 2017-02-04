#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <cmath>

typedef long long ll;

using namespace std;

vector<vector<int> > g;
vector<int> tin, l;
vector<char> mark;
set<int> ans;
int timer = 0;

void dfs(int v, int p = -1) {
    mark[v] = 1;

    tin[v] = timer++;
    l[v] = tin[v];

    int child = 0;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];

        if (u == p) {
            continue;
        }

        if (mark[u] == 0) {
            ++child;

            dfs(u, v);

            l[v] = min(l[v], l[u]);

            if (l[u] >= tin[v] && p != -1) {
                ans.insert(v);
            }
        } else if (mark[u] == 1) {
            l[v] = min(l[v], tin[u]);
        }
    }

    if (child > 1 && p == -1) {
        ans.insert(v);
    }

    mark[v] = 2;
}

int main() {
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    g.resize(n);
    tin.resize(n);
    l.resize(n);
    mark.resize(n, 0);

    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d%d", &b, &e);

        --b;
        --e;

        g[b].push_back(e);
        g[e].push_back(b);
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            dfs(i);
        }
    }

    printf("%d\n", (int)ans.size());
    for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        printf("%d\n", *it + 1);
    }
}