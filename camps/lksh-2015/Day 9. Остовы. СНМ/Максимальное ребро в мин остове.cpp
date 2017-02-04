#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int N = 5e4;

int parent[N], ranks[N];

void initDSU(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranks[i] = 0;
    }
}

int root(int v) {
    return v == parent[v] ? v : parent[v] = root(parent[v]);
}

void join(int v, int u) {
    v = root(v);
    u = root(u);

    if (ranks[v] < ranks[u]) {
        swap(v, u);
    }

    parent[u] = v;

    if (ranks[v] == ranks[u]) {
        ranks[v]++;
    }
}

struct Edge {
    int u, v, w;
};

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("oil.in", "r", stdin);
    freopen("oil.out", "w", stdout);
#endif

    int n, k;
    scanf("%d%d", &n, &k);

    initDSU(n);

    vector<Edge> edges(k);
    for (int i = 0; i < k; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        --edges[i].u;
        --edges[i].v;
    }

    sort(edges.begin(), edges.end(),
        [] (Edge e1, Edge e2) {
            return e1.w < e2.w;
        });

    int ans = 0;
    for (int i = 0; i < k; i++) {
        if (root(edges[i].v) != root(edges[i].u)) {
            ans = edges[i].w;
            join(edges[i].v, edges[i].u);
        }
    }
    printf("%d\n", ans);
}
