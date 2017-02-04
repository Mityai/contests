#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

using ll = long long;

const int N = 2e5;

int n;
vector<int> g[N];
int A[N], B[N], W[N], P[N];
int maxdel[N];
ll WE[N];
ll minweight[N], maxweight[N];

void no() {
    puts("-1");
    exit(0);
}

void go(int v, int id) {
    WE[v] = 0;
    minweight[v] = maxweight[v] = 0;
    for (int ei : g[v]) {
        int u = B[ei];
        int w = W[ei];
        int p = P[ei];

        go(u, ei);

        WE[v] += WE[u] + w;

        ll del = min(ll(maxdel[ei]), p - minweight[u]);
        ll neww = w - del;
        minweight[v] += minweight[u] + neww;
        maxweight[v] += maxweight[u] + w;
        if (id != -1) {
            maxweight[v] = min(maxweight[v], ll(P[id]));
        }
    }
    if (id != -1 && minweight[v] > P[id]) {
        no();
    }
}

void relax(int v, ll weight) {
    for (int ei : g[v]) {
        int u = B[ei];
        if (WE[u] > maxweight[u]) {
			weight -= WE[u] - maxweight[u];
        }
    }
    for (int ei : g[v]) {
        int u = B[ei];
        ll neww = min(weight, min(WE[u], maxweight[u]) - minweight[u]) + max(0ll, WE[u] - maxweight[u]);
        if (neww > 0) {
            weight -= neww - max(0ll, WE[u] - maxweight[u]);
            WE[v] -= neww;
            relax(u, neww);
        }
    }
    for (int ei : g[v]) {
        int u = B[ei];
        ll neww = min(weight, min(ll(min(W[ei] - 1, P[ei])), P[ei] - WE[u]));
        P[ei] -= neww;
        W[ei] -= neww;
        weight -= neww;
        WE[v] -= neww;
    }
}

int main() {
#if __APPLE__
    freopen("E.in", "r", stdin);
    freopen("E.out", "w", stdout);
#endif 

    scanf("%d", &n);

    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d%d%d", &A[i], &B[i], &W[i], &P[i]);
        --A[i], --B[i];
        g[A[i]].push_back(i);
        maxdel[i] = min(W[i] - 1, P[i]);
    }

    go(0, -1);
    relax(0, WE[0] - maxweight[0]);

    printf("%d\n", n);
    for (int i = 0; i < n - 1; ++i) {
        printf("%d %d %d %d\n", A[i] + 1, B[i] + 1, W[i], P[i]);
    }
}
