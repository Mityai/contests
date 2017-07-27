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

int plog[4 * MAXN];

vector <int> g[MAXN];
int tin[MAXN];
int label[MAXN];
int size[MAXN];
int level[MAXN];
int ascend[MAXN];
int head[MAXN];
int par[MAXN];
int T;

void dfs(int v, int d, int p) {
    par[v] = p;
    size[v] = 1;
    level[v] = d;
    tin[v] = ++T;
    for (int i = 0; i < (int)g[v].size(); i++) {
        int to = g[v][i];
        dfs(to, d + 1, v);
        size[v] += size[to];
    }
    int j = plog[(tin[v] - 1) ^ (tin[v] + size[v] - 1)];
    label[v] = ((tin[v] + size[v] - 1) >> j) << j;
}

void dfs(int v, int par) {
    if (par == -1 || label[v] != label[par]) {
        head[label[v]] = v;
    }
    if (par != -1) {
        int j = plog[label[v] - (label[v] & (label[v] - 1))];
        ascend[v] = ascend[par] + (label[v] != label[par] ? (1 << j) : 0);
    }
    for (int i = 0; i < (int)g[v].size(); i++) {
        dfs(g[v][i], v);
    }
}

inline int find(int x, int labelZ, int j) {
    if (label[x] == labelZ) {
        return x;
    }
    int k = plog[ascend[x] & ((1 << j) - 1)];
    int labelW = (((label[x] >> (k + 1)) << 1) | 1) << k;
    return par[head[labelW]];
}

inline int lca(int x, int y) {
    if (label[x] == label[y]) {
        return level[x] < level[y] ? x : y;
    }
    int i = plog[label[x] ^ label[y]];
    int common = ((ascend[x] & ascend[y]) >> i) << i;
    int j = plog[common - (common & (common - 1))];
    int labelZ = (((label[x] >> (j + 1)) << 1) | 1) << j;
    int xx = find(x, labelZ, j);
    int yy = find(y, labelZ, j);
    return level[xx] < level[yy] ? xx : yy;
}

inline bool cmp(int u, int v) {
    return tin[u] < tin[v];
}

int main() {
    freopen("genealogy.in", "r", stdin);
#ifndef LOCAL
    freopen("genealogy.out", "w", stdout);
#endif
    plog[1] = 0;
    for (int i = 2; i < 4 * MAXN; i++) {
        plog[i] = plog[i >> 1] + 1;
    }
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
        dfs(root, 0, -1);
        ascend[root] = 1 << plog[n];
        dfs(root, -1);
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
