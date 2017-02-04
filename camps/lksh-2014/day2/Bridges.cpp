#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <cmath>

typedef long long ll;

using namespace std;

const int inf = (2 << 29);

vector<vector<pair<int, int> > > g;
vector<int> tin, l;
vector<char> mark;
set<int> ans;
int timer = 0;

void dfs(int v, int id = -1) {
    mark[v] = 1;

    tin[v] = timer++;
    l[v] = tin[v];

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;
        int uid = g[v][i].second;

        if (id == uid) {
            continue;
        }

        if (mark[u] == 0) {
            dfs(u, uid);

            l[v] = min(l[v], l[u]);

        } else if (mark[u] == 1) {
            l[v] = min(l[v], tin[u]);
        }
    }

    if (l[v] >= tin[v] && id != -1) {
        ans.insert(id);
    }

    mark[v] = 2;
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);

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

        g[b].push_back(make_pair(e, i));
        g[e].push_back(make_pair(b, i));
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            dfs(i);
        }
    }

    printf("%d\n", (int)ans.size());
    for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        printf("%d ", *it + 1);
    }
}