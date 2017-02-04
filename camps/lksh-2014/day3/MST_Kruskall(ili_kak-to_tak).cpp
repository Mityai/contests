#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

typedef long long ll;

using namespace std;

struct Edge {
    int b, e, w;
};

bool cmp(Edge e1, Edge e2) {
    return e1.w < e2.w;
}

vector<int> par, ranks;

int root(int v) {
    if (v == par[v]) {
        return v;
    }

    return root(par[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);

    if (ranks[v] > ranks[u]) {
        swap(v, u);
    }

    par[v] = u;

    if (ranks[v] == ranks[u]) {
        ++ranks[u];
    }
}

int main() {
    //freopen("mst.in", "r", stdin);
    //freopen("mst.out", "w", stdout);

    int n, m;
    scanf("%d%d", &n, &m);

    par.resize(n);
    ranks.resize(n);

    for (int i = 0; i < n; i++) {
        par[i] = i;
    }

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].b, &edges[i].e, &edges[i].w);

        --edges[i].b;
        --edges[i].e;
    }

    sort(edges.begin(), edges.end(), cmp);

    ll ans = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (root(edges[i].b) != root(edges[i].e)) {
            unite(edges[i].b, edges[i].e);

            ans += edges[i].w;
        }
    }

    printf("%lld", ans);
}