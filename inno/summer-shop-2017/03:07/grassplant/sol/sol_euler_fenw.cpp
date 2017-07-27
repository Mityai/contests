#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5;
const int K = 18;

vector<int> g[N];

int up[K][N];
int euler[2 * N], st[N], en[N];
int tin[N], tout[N];
int timer = 0;
int T = 0;

void dfs(int v, int p) {
    up[0][v] = p;
    for (int i = 1; i < K; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    st[v] = en[v] = timer;
    tin[v] = T++;
    euler[timer++] = v;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            en[v] = timer;
            euler[timer++] = v;
        }
    }
    tout[v] = T++;
}

int fenw[2 * N];

void add(int pos, int val) {
    for (int i = pos; i < 2 * N; i = (i | (i + 1))) {
        fenw[i] += val;
    }
}

int sum(int pos) {
    int ret = 0;
    for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
        ret += fenw[i];
    }
    return ret;
}

bool is_anc(int v, int u) {
    return tin[v] <= tin[u] && tout[u] <= tout[v];
}

int lca(int a, int b) {
    for (int i = K - 1; i >= 0; --i) {
        if (!is_anc(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return is_anc(a, b) ? a : up[0][a];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, 0);

    for (int i = 0; i < m; ++i) {
        char c;
        int a, b;
        scanf(" %c%d%d", &c, &a, &b);
        --a, --b;
        if (c == 'P') {
            add(st[a], 1);
            add(st[b], 1);
            add(st[lca(a, b)], -2);
        } else {
            if (is_anc(b, a)) swap(a, b);
            printf("%d\n", sum(en[b]) - (st[b] > 0 ? sum(st[b] - 1) : 0));
        }
    }
}
