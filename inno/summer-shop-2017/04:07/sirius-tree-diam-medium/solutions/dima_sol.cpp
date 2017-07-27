#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

vector<int> g[N];
int dist[N];

void go(int v, int p) {
    dist[v] = dist[p] + 1;
    for (int u : g[v]) {
        if (u != p) {
            go(u, v);
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    go(0, 0);
    int v = 0;
    for (int i = 1; i < n; ++i) {
        if (dist[v] < dist[i]) {
            v = i;
        }
    }

    memset(dist, 0, n * sizeof(dist[0]));
    go(v, v);

    v = 0;
    for (int i = 1; i < n; ++i) {
        if (dist[v] < dist[i]) {
            v = i;
        }
    }

    printf("%d\n", dist[v] - 1);
}
