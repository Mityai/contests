#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int depth[N];
int mindepth[N];
int col[N];
bool mark[N];
vector<pair<int, int>> g[N];

int colors = 0;

void findPoints(int v, int d = 0) {
    mark[v] = true;
    mindepth[v] = depth[v] = d;
    for (auto to : g[v]) {
        int u = to.first;
        int id = to.second;
        if (mark[u]) {
            mindepth[v] = min(mindepth[v], depth[u]);
        } else {
            findPoints(u, d + 1);
            mindepth[v] = min(mindepth[v], mindepth[u]);
        }
    }
}

void paint(int v, int c, int p = -1) {
    mark[v] = true;
    for (auto to : g[v]) {
        int u = to.first;
        int id = to.second;
        if (u == p) continue;
        if (!mark[u]) {
            if (mindepth[u] >= depth[v]) {
                col[id] = colors++;
                paint(u, col[id], v);
            } else {
                col[id] = c;
                paint(u, col[id], v);
            }
        } else if (depth[u] < depth[v]) {
            col[id] = c;
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    for (int v = 0; v < n; ++v) {
        if (!mark[v]) {
            findPoints(v);
        }
    }

    memset(col, -1, sizeof col);
    memset(mark, false, sizeof mark);
    for (int v = 0; v < n; ++v) {
        if (!mark[v]) {
            paint(v, colors++);
        }
    }

    vector<set<int>> pts(colors);
    vector<set<int>> ed(colors);
    for (int v = 0; v < n; ++v) {
        for (auto to : g[v]) {
            int u = to.first;
            int id = to.second;
            pts[col[id]].insert(u);
            pts[col[id]].insert(v);
            ed[col[id]].insert(id);
        }
    }

    set<int> ans;
    for (int i = 0; i < colors; ++i) {
        if (pts[i].size() == ed[i].size()) {
            ans.insert(ed[i].begin(), ed[i].end());
        }
    }

    printf("%d\n", static_cast<int>(ans.size()));
    for (int v : ans) {
        printf("%d ", v + 1);
    }
    putchar('\n');
}
