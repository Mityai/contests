// schieber-vishkin
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;

#ifdef LOCAL
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
    #define eprintf(...) 42;
#endif

const int MAXN = 100500;


vector <int> g[MAXN];
int up[18][MAXN];
int tin[MAXN];
int tout[MAXN];
int level[MAXN];
int T;

void dfs(int v, int d, int p) {
    tin[v] = T++;
    level[v] = d;
    up[0][v] = p;
    for (int i = 1; i < 18; i++) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int i = 0; i < (int)g[v].size(); i++) {
        dfs(g[v][i], d + 1, v);
    }
    tout[v] = T++;
}

inline bool isAns(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

inline int lca(int x, int y) {
    if (isAns(x, y) || isAns(y, x)) {
        return isAns(x, y) ? x : y;
    }
    for (int i = 17; i >= 0; i--) {
        if (!isAns(up[i][x], y)) {
            x = up[i][x];
        }
    }
    return up[0][x];
}

inline bool cmp(int u, int v) {
    return tin[u] < tin[v];
}

int main() {
    freopen("genealogy.in", "r", stdin);
#ifndef LOCAL
    freopen("genealogy.out", "w", stdout);
#endif
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            g[i].clear();
        }
        int root = -1;
        for (int i = 0; i < n; i++) {
            int p;
            scanf("%d", &p);
            if (p == -1) {
                root = i;
            } else {
                g[p - 1].push_back(i);
            }
        }
        T = 0;
        dfs(root, 0, root);
        int g;
        scanf("%d", &g);
        vector <int> group;
        while (g --> 0) {
            int k;
            scanf("%d", &k);
            group.resize(k);
            for (int i = 0; i < k; i++) {
                scanf("%d", &group[i]);
                --group[i];
            }
            sort(group.begin(), group.end(), cmp);
            int ans = level[group[0]] + 1;
            for (int i = 1; i < k; i++) {
                int tmp = lca(group[i - 1], group[i]);
                ans += level[group[i]] - level[tmp];
            }
            printf("%d\n", ans);
        }
        puts("");
    }
    return 0;
}
