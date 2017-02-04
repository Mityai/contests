#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <cmath>

typedef long long ll;

using namespace std;

vector<vector<int> > g, gt;
vector<int> tout_order, component;
vector<char> mark;

void dfs1(int v) {
    mark[v] = 1;

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (mark[u] == 0) {
            dfs1(u);
        }
    }

    tout_order.push_back(v);
}

void dfs2(int v) {
    mark[v] = 1;

    for (int i = 0; i < gt[v].size(); i++) {
        int u = gt[v][i];
        if (mark[u] == 0) {
            dfs2(u);
        }
    }

    component.push_back(v);
}

int main() {
    freopen("condense2.in", "r", stdin);
    freopen("condense2.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    g.resize(n);
    gt.resize(n);

    for (int i = 0; i < m; i++) {
        int b, e;
        scanf("%d%d", &b, &e);

        --b;
        --e;

        g[b].push_back(e);
        gt[e].push_back(b);
    }

    mark.assign(n, 0);
    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            dfs1(i);
        }
    }

    int comp_num = 1;
    vector<int> comp(n);

    mark.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int v = tout_order[n - 1 - i];
        if (mark[v] == 0) {
            dfs2(v);

            for (int j = 0; j < component.size(); j++) {
                comp[component[j]] = comp_num;
            }
            ++comp_num;

            component.clear();
        }
    }

    set<pair<int, int> > edges;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            int u = g[i][j];

            if (comp[i] != comp[u]) {
                edges.insert(make_pair(comp[i], comp[u]));
            }
        }
    }

    printf("%d\n", (int)edges.size());
}