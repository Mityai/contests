#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int K = 17;

vector<int> g[N];

int tin[N], tout[N], up[K][N], depth[N];
int timer = 0;

void go(int v, int p) {
    depth[v] = depth[p] + 1;
    up[0][v] = p;
    tin[v] = timer++;
    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
    tout[v] = timer++;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int getlca(int v, int u) {
    if (is_anc(v, u)) return v;
    if (is_anc(u, v)) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (!is_anc(up[i][v], u)) {
            v = up[i][v];
        }
    }
    return is_anc(v, u) ? v : up[0][v];
}

bool cmp(int a, int b) {
    return tin[a] < tin[b];
}

void answer(vector<int>& a) {
    sort(a.begin(), a.end(), cmp);

    int ans = depth[a[0]];
    for (int i = 1; i < a.size(); ++i) {
        int lca = getlca(a[i - 1], a[i]);
        ans += depth[a[i]] - depth[lca];
    }
    printf("%d\n", ans);
}

inline int readInt() {
    char c = getchar();
    while (c <= 32) c = getchar();
    int sgn = 1;
    if (c == '-') sgn = -1, c = getchar();
    int ret = 0;
    while ('0' <= c && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret * sgn;
}

int main() {
    freopen("genealogy.in", "r", stdin);
    freopen("genealogy.out", "w", stdout);

    int n = readInt();

    int s;
    for (int i = 0; i < n; ++i) {
        up[0][i] = readInt();
        if (--up[0][i] == -2) {
            up[0][i] = 0;
            s = i;
        } else {
            g[up[0][i]].push_back(i);
        }
    }

    go(s, s);
    for (int i = 1; i < K; ++i) {
        for (int v = 0; v < n; ++v) {
            up[i][v] = up[i - 1][up[i - 1][v]];
        }
    }

    int g = readInt();

    for (int i = 0; i < g; ++i) {
        int ki = readInt();
        vector<int> group(ki);
        for (int j = 0; j < ki; ++j) {
            group[j] = readInt() - 1;
        }
        answer(group);
    }
}
