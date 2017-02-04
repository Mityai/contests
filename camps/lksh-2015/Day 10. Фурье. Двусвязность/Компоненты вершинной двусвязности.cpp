#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 2e4;
const int M = 2e5;

vector< pair<int, int> > g[N];
int depth[N], mindepth[N];
bool mark[N], is[N];
int col[M];

int colors = 0;

void findPoints(int v, int d = 0) {
    mark[v] = true;
    mindepth[v] = depth[v] = d;
    int childs = 0;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        if (mark[u]) {
            mindepth[v] = min(mindepth[v], depth[u]);
        } else {
            findPoints(u, d + 1);
            childs++;
            mindepth[v] = min(mindepth[v], mindepth[u]);
            if (mindepth[u] >= depth[v]) {
                is[v] = true;
                col[id] = colors++;
            }
        }
    }
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    return col[a.se] > col[b.se];
}

void dfs(int v, int c = -1) {
    mark[v] = true;
    for (auto to : g[v]) {
        int u = to.fi;
        int id = to.se;
        assert(col[id] != -1 || c != -1);
        if (!mark[u]) {
            if (col[id] != -1) {
                dfs(u, col[id]);
            } else if (c != -1) {
                col[id] = c;
                dfs(u, c);
            }
        } else if (c != -1 && col[id] == -1) {
            col[id] = c;
        }
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
#endif

    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    memset(col, -1, sizeof col);
    for (int s = 0; s < n; s++) {
        if (!mark[s]) {
            findPoints(s);
        }
    }

    memset(mark, false, sizeof mark);
    for (int s = 0; s < n; s++) {
        if (!mark[s] && is[s]) {
            dfs(s);
        }
    }

    printf("%d\n", colors);
    for (int i = 0; i < m; i++) {
        printf("%d ", col[i] + 1);
    }
}
