#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
int cost[N], ans[N];
int fenw[2 * N];
int tin[N], tout[N];
int T = 0;

void dfs(int v) {
    tin[v] = T++;
    for (int u : g[v]) {
        dfs(u);
    }
    tout[v] = T++;
}

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

int sum(int l, int r) {
    int ret = sum(r);
    if (l > 0) {
        ret -= sum(l - 1);
    }
    return ret;
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &cost[i]);
    }

    for (int i = 1; i < n; ++i) {
        int par;
        scanf("%d", &par);
        g[par - 1].push_back(i);
    }

    dfs(0);

    vector<pair<int, int>> vert(n);
    for (int i = 0; i < n; ++i) {
        vert[i] = {cost[i], i};
    }
    sort(vert.rbegin(), vert.rend());

    for (int i = 0; i < n; ++i) {
        int v = vert[i].second;
        ans[v] = sum(tin[v], tout[v]);
        add(tin[v], 1);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
}
