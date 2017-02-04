#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1234567890;
const int N = 602;
const int M = 2 * N * (N + 2);
const int s = 0, t = N - 1;

int n, edgeID[N];
ll cost[N + 1][N + 1], phi[N];

int to[M], cap[M], flow[M];
ll weight[M];
vector<int> E[N];

int e = 0;
void addEdge(int v, int u, int c, ll w) {
    E[v].push_back(e);
    E[u].push_back(e ^ 1);
    to[e] = u;
    to[e ^ 1] = v;
    cap[e] = c;
    cap[e ^ 1] = 0;
    weight[e] = w;
    weight[e ^ 1] = -w;
    e += 2;
}

bool findShortestPath() {
    vector<ll> d(N, INF);
    d[s] = 0;

    vector<char> mark(N, false);
    
    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (mark[j] == false && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        if (d[v] == INF) break;
        mark[v] = true;

        for (int edge : E[v]) {
            if (flow[edge] == cap[edge]) continue;
            int u = to[edge];
            ll w = weight[edge];
            if (mark[u] == false && d[u] > d[v] + w + phi[v] - phi[u]) {
                d[u] = d[v] + w + phi[v] - phi[u];
                edgeID[u] = edge;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        phi[i] += d[i];
    }

    return d[t] != INF;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
#endif

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lld", &cost[i][j]);
        }
    }

    for (auto vec : E) {
        vec.reserve(2 * n);
    }

    for (int i = 1; i <= n; i++) {
        addEdge(s, i, 1, 0);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            addEdge(i, n + j, 1, cost[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        addEdge(n + i, t, 1, 0);
    }

    ll ans_dist = 0;
    while (findShortestPath()) {
        ll add_flow = INF;
        for (int v = t; v != s; v = to[edgeID[v] ^ 1]) {
            add_flow = min(add_flow, ll(cap[edgeID[v]] - flow[edgeID[v]]));
        }
        for (int v = t; v != s; v = to[edgeID[v] ^ 1]) {
            flow[edgeID[v]] += add_flow;
            flow[edgeID[v] ^ 1] -= add_flow;
            ans_dist += add_flow * weight[edgeID[v]];
        }
    }

    printf("%lld\n", ans_dist);
    for (int v = 1; v <= n; v++) {
        for (int edge : E[v]) {
            if (flow[edge] == cap[edge]) {
                printf("%d %d\n", v, to[edge] - n);
                break;
            }
        }
    }
}
